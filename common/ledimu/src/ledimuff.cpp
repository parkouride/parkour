#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"
#include <iostream>


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

	if (buffer.open(filename, std::ios::in | std::ios::binary))
	{
		m_file = std::unique_ptr<STREAM_TYPE>(new STREAM_TYPE(&buffer));
		return read_header();
	}

	return LedImuFileError::file_not_found;
#endif // SD_EMU_H
}

LedImuFile::~LedImuFile()
{
}

int LedImuFile::RunState(int state_number)
{
	return 0;
}

LedImuFileError LedImuFile::read_header()
{
	m_file->read(m_header.start_marker, 4);
	if (!*m_file)
	{
		return LedImuFileError::invalid_file;
	}

	if (strncmp(m_header.start_marker, "PARK", 4))
	{
		return LedImuFileError::invalid_file;
	}

	return LedImuFileError::success;
}

#ifndef LEDIMU_READONLY
#include "_ledimuff_write.cpp"
#endif // LEDIMU_READONLY
