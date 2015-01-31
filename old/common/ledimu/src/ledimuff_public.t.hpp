#ifdef IN_LEDIMUFILECLASS

LedImuFileError Load() {
    LedImuFileError retval = LedImuFileError::success;
    if (!m_file.WasSuccess()) {
        return LedImuFileError::file_not_found;
    }
    CHECK_ERROR(read_header());
    
    return retval;
    
};

std::unique_ptr<char[]> GetStateName(int state_number)
{
    uint8_t string_length;
    // Seek to the beginning of state name mapping
    RET_NULL_IF_FAIL(m_file.Seek(m_header.state_name_mapping_position))
    RET_NULL_IF_FAIL(m_file.ReadByte(&string_length))
    
    while(state_number > 0 && m_file.WasSuccess()) {
        m_file.Skip(string_length);
        --state_number;
        m_file.ReadByte(&string_length);
    }
    
    if (state_number > 0) {
        return nullptr;
    }
    
    auto retval = new char[string_length+1] {0};
    m_file.ReadCharArray(retval, string_length);
    
    return std::unique_ptr<char[]>(retval);
}

int RunState(int state_number) {
    if (state_number < 0 || state_number > m_header.state_count)
    {
        LOG("State out of range: " << state_number << " -> " << (int)m_header.state_count);
        return -2;
    }
    
    bool found_state = goto_state(state_number);
    if (!found_state)
    {
        LOG("State Unknown: " << state_number);
        return -1;
    }
    
    return run_state();
}

#endif // IN_LEDIMUFILECLASS
