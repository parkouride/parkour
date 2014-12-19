#pragma once
#include <stack>
#include <memory>
#include "ledimu_data.h"

#define STACK_SIZE 32;

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
	TypeCodes get_type() { return m_type; }

	uint8_t getByte() { return 0; /* Error */ }
	uint16_t getShort() { return 0; /* Error */ }
	std::unique_ptr<Color> getColor() { return nullptr; }

private:
	TypeCodes m_type;
};

class ByteEntry : public StackEntry
{
public:
	ByteEntry() : StackEntry(TypeCodes::BYTE), m_value(0) {}
	ByteEntry(uint8_t value) : StackEntry(TypeCodes::BYTE), m_value(value) {}

	uint8_t getByte() { return m_value; }

private:
	uint8_t m_value;
};

class ShortEntry : public StackEntry
{
public:
	ShortEntry() : StackEntry(TypeCodes::SHORT), m_value(0) {}
	ShortEntry(uint16_t value) : StackEntry(TypeCodes::SHORT), m_value(value) {}

	uint16_t getShort() { return m_value; }

private:
	uint16_t m_value;
};

class ColorEntry : public StackEntry
{
public:
	ColorEntry() : StackEntry(TypeCodes::COLOR), m_value(nullptr) {}
	ColorEntry(std::unique_ptr<Color> value) : StackEntry(TypeCodes::COLOR), m_value(std::move(value)) {}

	std::unique_ptr<Color> getColor() { return std::move(m_value); }

private:
	std::unique_ptr<Color> m_value;
};

class Stack : public std::stack<std::unique_ptr<StackEntry>>
{

};