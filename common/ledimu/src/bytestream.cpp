#include "bytestream.h"

ByteStream::ByteStream(const char *filename) 
{
	m_stream.reset(new std::ifstream(filename));
}


template <typename T>
T ByteStream::read()
{
	T storage;
	m_stream->read(reinterpret_cast<char *>(&storage), sizeof(T));

	return storage;
}

bool ByteStream::ReadByte(uint8_t *storage)
{
	uint8_t tmp;

	tmp = read<uint8_t>();
	if (!*m_stream) {
		return false;
	}

	*storage = tmp;
	return true;
}