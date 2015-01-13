#pragma once

namespace ledvm {
    // Forward decl
    class StackEntry;
    class _Stack;

    using StackEntry_ptr = StackEntry*;
    using StackEntry_raw = StackEntry*;
    using Stack_t = _Stack;
    
    template <typename T>
    StackEntry_ptr StackEntryFactory(T* value) {
        return static_cast<StackEntry_raw>(value);
    }

    class _Stack {
    };
} // ledvm
