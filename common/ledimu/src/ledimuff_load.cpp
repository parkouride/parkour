#include <memory>

#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"

using namespace ledvm;

int LedImuFile::RequiredPixelCountFor(const char* filename)
{
	std::ifstream datafile{filename};
	if (!datafile)
	{
		return -1;
	}

	datafile.seekg(5); // Skip PARK and State count
	uint8_t retval;
	datafile.read(reinterpret_cast<char *>(&retval), 1);
	std::cout << static_cast<int>(retval) << std::endl;

	return static_cast<int>(retval);
}


LedImuFileError LedImuFile::Load()
{
    return Load(LEDIMU_FILENAME);
}

LedImuFileError LedImuFile::Load(const char *filename)
{
	LedImuFileError retval = LedImuFileError::success;
	m_file = std::unique_ptr<ByteStream>(new ByteStream(filename));
	if (!m_file->WasSuccess()) {
		return LedImuFileError::file_not_found;
	}
	CHECK_ERROR(read_header());

	return retval;
}

inline LedImuFileError LedImuFile::read_header()
{
	LedImuFileError retval;

	CHECK_ERROR(read_magic_marker(m_header.start_marker, "PARK")) // TODO: Proper Error Handling
	CHECK_ERROR(m_file->ReadByte(&m_header.state_count)) // TODO: Proper Error Handling

	if (GetNumberStates() <= 0)
	{
		return LedImuFileError::no_states_specified;
	}
	m_header.state_position.reset(new uint16_t[m_header.state_count]);

	CHECK_ERROR(m_file->ReadByte(&m_header.required_pixel_count)) // TODO:: Proper Error Handling
	if (m_header.required_pixel_count > m_pixel_count)
	{
		return LedImuFileError::not_enough_pixels;
	}

	CHECK_ERROR(m_file->ReadShort(&m_header.state_name_mapping_position))
	CHECK_ERROR(m_file->ReadShort(&m_header.state_decision_position))
	CHECK_ERROR(m_file->ReadShortArray(m_header.state_position.get(), m_header.state_count))
	CHECK_ERROR(read_magic_marker(m_header.end_marker, "HEND"))

	loaded = true;
	return LedImuFileError::success;
}

LedImuFileError LedImuFile::read_magic_marker(char *buffer, const char marker[4])
{
	m_file->ReadCharArray(buffer, 4);
	if (!m_file->WasSuccess())
	{
		return LedImuFileError::invalid_file;
	}

	if (strncmp(buffer, marker, 4))
	{
		return LedImuFileError::invalid_file;
	}

	return LedImuFileError::success;
}

