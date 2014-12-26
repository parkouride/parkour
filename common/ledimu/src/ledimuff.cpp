#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"
#include <iostream>
#include <iomanip>

#define RET_NULL_IF_FAILED(x) if (!x->WasSuccess()) { return nullptr; }
#define RET_NULL_IF_FAIL(x) if (!(x)) { return nullptr; }

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
	RET_NULL_IF_FAIL(m_file->Seek(file_position))

	// Read the length of the state
	RET_NULL_IF_FAIL(m_file->ReadShort(&state_size))

	auto retval = new uint8_t[state_size];
	RET_NULL_IF_FAIL(m_file->ReadByteArray(retval, state_size))

	return uint8_uptra(retval);
}

std::unique_ptr<char[]> LedImuFile::GetStateName(int state_number)
{
	uint8_t string_length;
	// Seek to the beginning of state name mapping
	RET_NULL_IF_FAIL(m_file->Seek(m_header.state_name_mapping_position))
	RET_NULL_IF_FAIL(m_file->ReadByte(&string_length))

	while(state_number > 0 && m_file->WasSuccess()) {
		m_file->Skip(string_length);
		--state_number;
		m_file->ReadByte(&string_length);
	}

	if (state_number > 0) {
		return nullptr;
	}

	auto retval = new char[string_length+1] {0};
	m_file->ReadCharArray(retval, string_length);

	return std::unique_ptr<char[]>(retval);
}
