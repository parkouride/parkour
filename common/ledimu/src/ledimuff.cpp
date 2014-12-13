#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"
#include <iostream>
#include <iomanip>


LedImuFile::LedImuFile(std::unique_ptr<ImuRunner> &runner, uint8_t pixel_count)
    : m_runner(std::move(runner)),
      m_pixel_count(pixel_count)
{
}



LedImuFile::~LedImuFile()
{
}

int LedImuFile::RunState(int state_number)
{
	if (state_number < 0 || state_number > m_header.state_count)
	{
		return -2;
	}

	std::unique_ptr<uint8_t[]> code = get_state(state_number);
	if (code == nullptr)
	{
		return -1;
	}

	return 0;
}

std::unique_ptr<uint8_t[]> LedImuFile::get_state(int state_number)
{
	if (!m_file->fail())
	{
		m_file->clear();
	}

	uint16_t file_position = m_header.state_position[state_number];
	uint16_t state_size;

	// Seek to beginning of state
	m_file->seekg(file_position, m_file->beg);
	if (!*m_file) { std::cout << "seek failed" << std::endl; return nullptr; }

	// Read the length of the state
	m_file->read(reinterpret_cast<char *>(&state_size), 2);
	if (!*m_file) { return nullptr; }

	auto retval = new uint8_t[state_size];
	m_file->read(reinterpret_cast<char *>(retval), state_size);
	if (!*m_file) { return nullptr; }

	return std::unique_ptr<uint8_t[]>(retval);
}


#ifndef LEDIMU_READONLY
#include "_ledimuff_write.cpp"
#endif // LEDIMU_READONLY
