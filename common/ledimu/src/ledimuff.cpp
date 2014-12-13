#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"
#include <iostream>

#define CHECK_ERROR(x) if ((retval=x) != 0) { return retval; }

LedImuFile::LedImuFile(std::unique_ptr<ImuRunner> &runner) : m_runner(std::move(runner))
{
}

LedImuFileError LedImuFile::Load()
{
    return Load(LEDIMU_FILENAME);
}

LedImuFileError LedImuFile::Load(const char *filename)
{
#ifdef SD_H
#endif // SD_H

#ifdef SD_EMU_H
	std::filebuf buffer;
	LedImuFileError retval;

	if (!buffer.open(filename, std::ios::in | std::ios::binary))
	{
		return LedImuFileError::file_not_found;
	}

	m_file = std::unique_ptr<STREAM_TYPE>(new STREAM_TYPE(&buffer));
	CHECK_ERROR(read_header());

	return retval;

#endif // SD_EMU_H
}

inline LedImuFileError LedImuFile::read_header()
{
	LedImuFileError retval;
	CHECK_ERROR(read_magic_marker(m_header.start_marker, "PARK"))
	CHECK_ERROR(read(&m_header.state_count))

	if (GetNumberStates() <= 0)
	{
		return LedImuFileError::no_states_specified;
	}

	CHECK_ERROR(read(&m_header.state_name_mapping_position))
	CHECK_ERROR(read(&m_header.state_decision_position))

	return LedImuFileError::success;
}

LedImuFile::~LedImuFile()
{
}

int LedImuFile::RunState(int state_number)
{
	return 0;
}

LedImuFileError LedImuFile::read_magic_marker(char *buffer, const char marker[4])
{
	m_file->read(buffer, 4);
	if (!*m_file)
	{
		return LedImuFileError::invalid_file;
	}

	if (strncmp(m_header.start_marker, marker, 4))
	{
		return LedImuFileError::invalid_file;
	}

	return LedImuFileError::success;
}

template<typename T>
LedImuFileError LedImuFile::read(T *buffer)
{
	m_file->read(reinterpret_cast<char *>(buffer), sizeof(T));
	if (!*m_file)
	{
		return LedImuFileError::invalid_file;
	}

	return LedImuFileError::success;
}

#ifndef LEDIMU_READONLY
#include "_ledimuff_write.cpp"
#endif // LEDIMU_READONLY
