#include "stack.h"

using namespace ledvm;

StackEntry_ptr ByteEntry::Create(uint8_t value) {
	return StackEntryFactory<ByteEntry>(new ByteEntry(value));
}

StackEntry_ptr ShortEntry::Create(uint16_t value) {
	return StackEntryFactory<ShortEntry>(new ShortEntry(value));
}

std::unique_ptr<StackEntry> ColorEntry::Create(ledvm::Color value) {
	return StackEntryFactory<ColorEntry>(new ColorEntry(value));
}
