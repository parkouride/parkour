#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"
#include <iostream>
#include <iomanip>

#define RET_NULL_IF_FAILED(x) if (!*x) { return nullptr; }

using namespace ledvm;

LedImuFile::LedImuFile(std::shared_ptr<ImuRunner> &runner, uint8_t pixel_count)
    : m_runner(runner),
      m_pixel_count(pixel_count)
{
}



LedImuFile::~LedImuFile()
{
}



uint8_uptra LedImuFile::get_state(int state_number)
{
	uint16_t file_position = m_header.state_position[state_number];
	uint16_t state_size;

	// Seek to beginning of state
	m_file->seekg(file_position, m_file->beg);
	RET_NULL_IF_FAILED(m_file)

	// Read the length of the state
	read<uint16_t>(&state_size);
	RET_NULL_IF_FAILED(m_file)

	auto retval = new uint8_t[state_size];
	m_file->read(reinterpret_cast<char *>(retval), state_size);
	RET_NULL_IF_FAILED(m_file)

	return uint8_uptra(retval);
}

std::unique_ptr<char[]> LedImuFile::GetStateName(int state_number)
{
	uint8_t string_length;
	// Seek to the beginning of state name mapping
	m_file->seekg(m_header.state_name_mapping_position);
	RET_NULL_IF_FAILED(m_file)

	read(&string_length);
	while(state_number > 0 && *m_file) {
		m_file->seekg(string_length, m_file->cur);
		--state_number;
		read(&string_length);
	}

	if (state_number > 0) {
		return nullptr;
	}

	auto retval = new char[string_length+1] {0};
	m_file->read(retval, string_length);

	return std::unique_ptr<char[]>(retval);
}
