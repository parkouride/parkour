#pragma once

#include <fstream>

class ByteStream
{
public:
	ByteStream(const char* filename);

	bool ReadByte(uint8_t *onebyte);
	bool ReadShort(uint16_t *twobyte);

private:
	template <typename T>
	T read();

	std::unique_ptr<std::ifstream> m_stream;
};