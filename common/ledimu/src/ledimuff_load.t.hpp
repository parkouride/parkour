#ifdef IN_LEDIMUFILECLASS
inline LedImuFileError read_header()
{

	CHECK_ERROR(read_magic_marker(m_header.start_marker, "PARK")) // TODO: Proper Error Handling
	CHECK_ERROR(m_file.ReadByte(&m_header.state_count)) // TODO: Proper Error Handling

	if (GetNumberStates() <= 0)
	{
		return LedImuFileError::no_states_specified;
	}
	m_header.state_position.reset(new uint16_t[m_header.state_count]);

	CHECK_ERROR(m_file.ReadByte(&m_header.required_pixel_count)) // TODO:: Proper Error Handling
	if (m_header.required_pixel_count > m_pixel_count)
	{
		return LedImuFileError::not_enough_pixels;
	}

	CHECK_ERROR(m_file.ReadShort(&m_header.vm_version))
	CHECK_ERROR(m_file.ReadShort(&m_header.requirements))
	CHECK_ERROR(m_file.ReadShort(&m_header.state_name_mapping_position))
	CHECK_ERROR(m_file.ReadShort(&m_header.state_decision_position))
	CHECK_ERROR(m_file.ReadShortArray(m_header.state_position.get(), m_header.state_count))
	CHECK_ERROR(read_magic_marker(m_header.end_marker, "HEND"))

	loaded = true;
	return LedImuFileError::success;
}

LedImuFileError read_magic_marker(char *buffer, const char marker[4])
{
	m_file.ReadCharArray(buffer, 4);
	if (!m_file.WasSuccess())
	{
		return LedImuFileError::invalid_file;
	}

	if (strncmp(buffer, marker, 4))
	{
		return LedImuFileError::invalid_file;
	}

	return LedImuFileError::success;
}

#endif // IN_LEDIMUFILECLASS