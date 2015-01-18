#pragma once

#include <fstream>

class ByteStream
{
public:
	ByteStream(const char* filename);

	bool ReadByte(uint8_t *onebyte);
	bool ReadShort(uint16_t *twobyte);

	bool ReadByteArray(uint8_t *bytes, int count);
	bool ReadShortArray(uint16_t *bytes, int count);
	bool ReadCharArray(char *str, int len);
	bool Seek(int position);
	bool Skip(int bytes);

	bool WasSuccess();

private:
	template <typename T>
    T read();

	template <typename T>
	void read(T* storage, int count);

	std::unique_ptr<std::ifstream> m_stream;
};