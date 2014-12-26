#include "stack.h"

using namespace ledvm;

std::unique_ptr<StackEntry> ByteEntry::Create(uint8_t value) {
	return std::unique_ptr<StackEntry>(
		static_cast<StackEntry *>(new ByteEntry(value))
		);
}

std::unique_ptr<StackEntry> ShortEntry::Create(uint16_t value) {
	return std::unique_ptr<StackEntry>(
		static_cast<StackEntry *>(new ShortEntry(value))
		);
}

std::unique_ptr<StackEntry> ColorEntry::Create(ledvm::Color value) {
	return std::unique_ptr<StackEntry>(
		static_cast<StackEntry *>(new ColorEntry(value))
		);
}