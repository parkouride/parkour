#include "ledimuff.h"

LedImuFile::LedImuFile(std::unique_ptr<ImuRunner> &runner) : m_runner(std::move(runner))
{
}

bool LedImuFile::Load()
{
    return Load(LEDIMU_FILENAME);
}

bool LedImuFile::Load(const char *filename)
{
#ifdef SD_H
#endif // SD_H

#ifdef SD_EMU_H
	std::filebuf buffer;

	if (buffer.open(filename, std::ios::in | std::ios::binary))
	{
		m_file = std::unique_ptr<STREAM_TYPE>(new STREAM_TYPE(&buffer));
		return true;
	}
	
	return false;
#endif // SD_EMU_H
}

LedImuFile::~LedImuFile()
{
}

int LedImuFile::RunState(int state_number)
{
	return 0;
}

#ifndef LEDIMU_READONLY
#include "_ledimuff_write.cpp"
#endif // LEDIMU_READONLY
