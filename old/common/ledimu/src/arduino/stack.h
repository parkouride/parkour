#pragma once

#include "types_arduino.h"

#ifndef STACK_SIZE
#define STACK_SIZE 20
#endif // STACK_SIZE

namespace ledvm {

class _Stack {

public:
    _Stack() : m_stack {nullptr}, m_top {-1} {
    }
    /*****
     * returns the top of the stack, but does not transfer ownership
     */
    StackEntry_ptr top() {
        if (m_top < 0)
            return nullptr;

        return m_stack[m_top];
    }

    /*****
     * adds an entry to the top of the stack, taking ownership
     */
    bool push(StackEntry_ptr entry) {
        if (m_top == STACK_SIZE)
            return false;

        m_stack[++m_top] = entry;
        return true;
    }

    /*****
     * pop removes and free the top of the stack
     */
    void pop() {
        StackEntry_ptr tmp = m_stack[m_top--];
        delete tmp;
    }

private:
    StackEntry_ptr[STACK_SIZE] m_stack;
    int m_top;
}

} // namespace ledvm
