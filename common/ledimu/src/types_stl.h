#pragma once

#include <memory>
#include <stack>
#include <cstdint>

namespace ledvm {
    // Forward decl
    class StackEntry;
    
    using StackEntry_ptr = std::unique_ptr<StackEntry>;
    using StackEntry_raw = StackEntry*;
    using Stack_t = std::stack<StackEntry_ptr>;
    
    template <typename T>
    StackEntry_ptr StackEntryFactory(T* value) {
        return StackEntry_ptr(
            static_cast<StackEntry_raw>(value)
        );
    };

    using uint16_arr = std::unique_ptr<uint16_t[]>;

} // ledvm
