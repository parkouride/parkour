#pragma once
#include <stack>
#include <memory>
#include "ledimu_data.h"

#define STACK_SIZE 32

namespace ledvm {

typedef enum {
	UNKNOWN = 0xFF,
	BYTE = 0x01,
	SHORT = 0x02,
	COLOR = 0x03
} TypeCodes;

class StackEntry
{
public:
	StackEntry() : m_type(TypeCodes::UNKNOWN) { }
	StackEntry(TypeCodes type) : m_type(type) { }
	virtual ~StackEntry() {}
	TypeCodes GetType() { return m_type; }

	virtual uint8_t GetByte() { return 0; /* Error */ }
	virtual uint16_t GetShort() { return 0; /* Error */ }
	virtual std::unique_ptr<Color> GetColor() { return nullptr; }

private:
	TypeCodes m_type;
};

class ByteEntry : public StackEntry
{
public:
	ByteEntry() : StackEntry(TypeCodes::BYTE), m_value(0) {}
	ByteEntry(uint8_t value) : StackEntry(TypeCodes::BYTE), m_value(value) {}

	uint8_t GetByte() { return m_value; }

private:
	uint8_t m_value;
};

class ShortEntry : public StackEntry
{
public:
	ShortEntry() : StackEntry(TypeCodes::SHORT), m_value(0) {}
	ShortEntry(uint16_t value) : StackEntry(TypeCodes::SHORT), m_value(value) {}

	uint16_t GetShort() { return m_value; }

private:
	uint16_t m_value;
};

class ColorEntry : public StackEntry
{
public:
	ColorEntry() : StackEntry(TypeCodes::COLOR), m_value(nullptr) {}
	ColorEntry(std::unique_ptr<Color> value) : StackEntry(TypeCodes::COLOR), m_value(std::move(value)) {}

	std::unique_ptr<Color> GetColor() { return std::move(m_value); }

private:
	std::unique_ptr<Color> m_value;
};

template<typename T>
std::unique_ptr<StackEntry> create_stack_entry(TypeCodes typecode, T value) {
	switch(typecode) {
		case TypeCodes::BYTE:
			return std::unique_ptr<StackEntry>(
				static_cast<StackEntry *>(new ByteEntry(static_cast<uint8_t>(value)))
				);
			break;
		case TypeCodes::SHORT:
			return std::unique_ptr<StackEntry>(
				static_cast<StackEntry *>(new ShortEntry(static_cast<uint16_t>(value)))
				);
			break;
		case TypeCodes::COLOR:
			break;
		case TypeCodes::UNKNOWN:
		default:
			break;
	}

	return nullptr;
}

class Stack : public std::stack<std::unique_ptr<StackEntry> >
{

};

} // namespace ledvm
