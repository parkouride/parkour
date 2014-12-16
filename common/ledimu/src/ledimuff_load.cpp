#include <memory>

#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"



LedImuFileError LedImuFile::Load()
{
    return Load(LEDIMU_FILENAME);
}

LedImuFileError LedImuFile::Load(const char *filename)
{
	LedImuFileError retval = LedImuFileError::success;
	m_file = std::unique_ptr<std::ifstream>(new std::ifstream(filename));
	if (!*m_file) {
		return LedImuFileError::file_not_found;
	}
	CHECK_ERROR(read_header());

	return retval;
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
	CHECK_ERROR(read(&m_header.required_pixel_count))
	if (m_header.required_pixel_count > m_pixel_count)
	{
		return LedImuFileError::not_enough_pixels;
	}

	CHECK_ERROR(read(&m_header.state_name_mapping_position))
	CHECK_ERROR(read(&m_header.state_decision_position))
	CHECK_ERROR(read_array<uint16_t>(m_header.state_position,
		m_header.state_count));
	CHECK_ERROR(read_magic_marker(m_header.end_marker, "HEND"))

	loaded = true;
	return LedImuFileError::success;
}

LedImuFileError LedImuFile::read_magic_marker(char *buffer, const char marker[4])
{
	m_file->read(buffer, 4);
	if (!*m_file)
	{
		return LedImuFileError::invalid_file;
	}

	if (strncmp(buffer, marker, 4))
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

template<typename T>
LedImuFileError LedImuFile::read_array(std::unique_ptr<T[]> &buffer, int count)
{
	buffer.reset(new T[count]);
	m_file->read(reinterpret_cast<char *>(buffer.get()),
		count * sizeof(T));

	return LedImuFileError::success;
}

template<typename T>
LedImuFileError LedImuFile::read_arguments(T* buffer, int count)
{
	m_file->read(reinterpret_cast<char *>(buffer), count);

	if (!*m_file)
	{
		return LedImuFileError::unknown_error;
	}

	return LedImuFileError::success;
}

template LedImuFileError LedImuFile::read_arguments<uint8_t>(uint8_t* buffer, int count);
template LedImuFileError LedImuFile::read_arguments<uint16_t>(uint16_t* buffer, int count);
