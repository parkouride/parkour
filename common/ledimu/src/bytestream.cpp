#include "bytestream.h"

ByteStream::ByteStream(const char *filename) 
{
	m_stream.reset(new std::ifstream(filename));
}


template <typename T>
void ByteStream::read(T* storage, int count)
{
	m_stream->read(reinterpret_cast<char *>(storage), sizeof(T) * count);
}

template <typename T>
T ByteStream::read()
{
	T storage;
	
	read<T>(&storage, 1);

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

bool ByteStream::ReadShort(uint16_t *storage)
{
	uint16_t tmp;

	tmp = read<uint16_t>();
	if (!*m_stream) {
		return false;
	}

	*storage = tmp;
	return true;
}

bool ByteStream::ReadByteArray(uint8_t *storage, int count)
{
	read<uint8_t>(storage, count);

	return WasSuccess();
}

bool ByteStream::ReadShortArray(uint16_t *storage, int count)
{
	read<uint16_t>(storage, count);

	return WasSuccess();
}


bool ByteStream::ReadCharArray(char *str, int len)
{
	read<char>(str, len);

	return WasSuccess();
}

bool ByteStream::Seek(int position)
{
	m_stream->seekg(position, m_stream->beg);

	return WasSuccess();
}

bool ByteStream::Skip(int bytes)
{
	m_stream->seekg(bytes, m_stream->cur);

	return WasSuccess();
}

bool ByteStream::WasSuccess()
{
	return static_cast<bool>(*m_stream);
}