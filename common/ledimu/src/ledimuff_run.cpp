#include "imurunner.h"
#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"
#include "stack.h"

#define IF_ERROR(x, y) if (!x->WasSuccess()) { return y; }

using namespace ledvm;

void LedImuFile::push(uint8_t typecode_i, Stack &stack, uint8_t *storage) {
	std::unique_ptr<StackEntry> entry;

	TypeCodes typecode = static_cast<TypeCodes>(typecode_i);
	switch(typecode) {
		case TypeCodes::BYTE:
			m_file->ReadByte(storage); // TODO: Proper Error Handling
			entry = ByteEntry::Create(storage[0]);
			stack.push(std::move(entry));
			break;

		case TypeCodes::SHORT:
			m_file->ReadShort(reinterpret_cast<uint16_t*>(storage));
			entry = ShortEntry::Create(
				(reinterpret_cast<uint16_t*>(storage))[0]);
			std::cout << "X" << entry->GetShort() << std::endl;
			stack.push(std::move(entry));
			break;

		case TypeCodes::COLOR:
			m_file->ReadByteArray(storage, 3);
			entry = ColorEntry::Create(Color {storage});
			stack.push(std::move(entry));
			break;

		case TypeCodes::UNKNOWN:
		default:
			// TODO: Error Handling
			break;
	}
}

int LedImuFile::run_state()
{
	bool done = false;
	uint8_t return_state = 0;
	uint8_t storage[16];
	Stack stack;
	std::unique_ptr<StackEntry> entry;

	while(!done)
	{
		m_file->ReadByte(storage);
		std::cout << "Read:" << std::hex << (int)storage[0] << std::endl;
		IF_ERROR(m_file, -1);

		switch(storage[0]) {
			case 0x00: break; // NOP

			case 0x01: // PUSH
				m_file->ReadByte(&storage[1]); // Typecode // TODO: Proper Error Handling
				push(storage[1], stack, storage);
				break;

			case 0x10: // SET ALL
				entry = std::move(stack.top());
				if (entry->GetType() == TypeCodes::COLOR)
				{
					m_runner->set_all(entry->GetColor());
				}
				stack.pop();
				break;

			case 0x11: // DELAY
				entry = std::move(stack.top());
				// Assert typecode == SHORT
				if (entry->GetType() == TypeCodes::SHORT)
				{
					m_runner->delay(entry->GetShort());
				} else {
					std::cout << "Failed to delay" << std::endl;
				}
				stack.pop();
				break;

			case 0xFF:  // End of State, Done
				m_runner->commit();
				done = true;
				break;

			default:
				std::cout << "Unknown Opcode:" << std::hex << (int)storage[0] << std::endl;
		}
	}

	return return_state;
}

int LedImuFile::RunState(int state_number)
{
	if (state_number < 0 || state_number > m_header.state_count)
	{
		std::cout << "State out of range: " << state_number << " -> " << m_header.state_count << std::endl;
		return -2;
	}

	bool found_state = goto_state(state_number);
	if (!found_state)
	{
		std::cout << "State Unknown: " << state_number << std::endl;
		return -1;
	}

	int retval = run_state();
	return retval <= 0 ? state_number : retval;
}