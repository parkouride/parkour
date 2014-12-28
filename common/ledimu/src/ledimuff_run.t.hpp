#ifdef IN_LEDIMUFILECLASS

#define IF_ERROR(x, y) if (!x.WasSuccess()) { return y; }

void push(uint8_t typecode_i, Stack &stack, uint8_t *storage) {
    std::unique_ptr<StackEntry> entry;
    
    TypeCodes typecode = static_cast<TypeCodes>(typecode_i);
    switch(typecode) {
        case TypeCodes::BYTE:
            m_file.ReadByte(storage); // TODO: Proper Error Handling
            entry = ByteEntry::Create(storage[0]);
            stack.push(std::move(entry));
            break;
            
        case TypeCodes::SHORT:
            m_file.ReadShort(reinterpret_cast<uint16_t*>(storage));
            entry = ShortEntry::Create(
                                       (reinterpret_cast<uint16_t*>(storage))[0]);
            std::cout << "X" << entry->GetShort() << std::endl;
            stack.push(std::move(entry));
            break;
            
        case TypeCodes::COLOR:
            m_file.ReadByteArray(storage, 3);
            entry = ColorEntry::Create(Color {storage});
            stack.push(std::move(entry));
            break;
            
        case TypeCodes::UNKNOWN:
        default:
            // TODO: Error Handling
            break;
    }
}

bool goto_state(int state_number)
{
    uint16_t file_position = m_header.state_position[state_number];
    
    // Seek to beginning of state
    std::cout << 1 << std::endl;
    RET_IF_FAILED(m_file.Seek(file_position), false)
    
    return true;
}

int run_state()
{
    bool done = false;
    uint8_t return_state = -1;
    uint8_t storage[16];
    Stack stack;
    std::unique_ptr<StackEntry> entry;
    
    while(!done)
    {
        m_file.ReadByte(storage);
        IF_ERROR(m_file, -1);
        
        switch(storage[0]) {
            case 0x00: break; // NOP
                
            case 0x01: // PUSH
                m_file.ReadByte(&storage[1]); // Typecode // TODO: Proper Error Handling
                push(storage[1], stack, storage);
                break;
                
            case 0x10: // SET ALL
                entry = std::move(stack.top());
                if (entry->GetType() == TypeCodes::COLOR)
                {
                    m_runner.set_all(entry->GetColor());
                }
                stack.pop();
                break;
                
            case 0x11: // DELAY
                entry = std::move(stack.top());
                // Assert typecode == SHORT
                if (entry->GetType() == TypeCodes::SHORT)
                {
                    m_runner.delay(entry->GetShort());
                } else {
                    std::cout << "Failed to delay" << std::endl;
                }
                stack.pop();
                break;
                
            case 0xFE:
                std::cout << "Received Next State" << std::endl;
                entry = std::move(stack.top());
                if (entry->GetType() == TypeCodes::BYTE)
                {
                    return_state = entry->GetByte();
                    std::cout << "Next State: " << (int)return_state << std::endl;
                }
                stack.pop();
                break;
                
            case 0xFF:  // End of State, Done
                m_runner.commit();
                done = true;
                break;
                
            default:
                std::cout << "Unknown Opcode:" << std::hex << (int)storage[0] << std::endl;
        }
    }
    
    return return_state;
}

#endif // IN_LEDIMUFILECLASS