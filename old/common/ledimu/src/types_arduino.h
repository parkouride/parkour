#pragma once

namespace ledvm {
    // Forward decl
    class StackEntry;

    using StackEntry_ptr = StackEntry*;
    using StackEntry_raw = StackEntry*;
    
    template <typename T>
    StackEntry_ptr StackEntryFactory(T* value) {
        return static_cast<StackEntry_raw>(value);
    }

#include "arduino/stack.h"
    using Stack_t = _Stack;

    using uint16_arr = uint16_t*;

} // ledvm

// Debugging
#ifdef DEBUG
#define LOG(x) Serial.println(x)
#else
#define LOG(x)
#endif
