#pragma once
#ifndef MY_STACK_H
#define MY_STACK_H

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
	virtual Color GetColor() { return nullptr; }

private:
	TypeCodes m_type;
};

class ByteEntry : public StackEntry
{
public:
	ByteEntry() : StackEntry(TypeCodes::BYTE), m_value(0) {}
	ByteEntry(uint8_t value) : StackEntry(TypeCodes::BYTE), m_value(value) {}

	uint8_t GetByte() { return m_value; }
	static std::unique_ptr<StackEntry> Create(uint8_t value);

private:
	uint8_t m_value;
};

class ShortEntry : public StackEntry
{
public:
	ShortEntry() : StackEntry(TypeCodes::SHORT), m_value(0) {}
	ShortEntry(uint16_t value) : StackEntry(TypeCodes::SHORT), m_value(value) {}

	uint16_t GetShort() { return m_value; }
	static std::unique_ptr<StackEntry> Create(uint16_t value);

private:
	uint16_t m_value;
};

class ColorEntry : public StackEntry
{
public:
	ColorEntry() : StackEntry(TypeCodes::COLOR), m_value(nullptr) {}
	ColorEntry(Color value) : StackEntry(TypeCodes::COLOR), m_value(value) {}

	Color GetColor() { return m_value; }
	static std::unique_ptr<StackEntry> Create(Color value);

private:
	Color m_value;
};

class Stack : public std::stack<std::unique_ptr<StackEntry> >
{

};

} // namespace ledvm

#endif // MY_STACK_H
