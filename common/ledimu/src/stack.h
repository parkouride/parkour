#pragma once

#define STACK_SIZE 32;

class Stack {
public:

	Stack() : m_head(0) { }

	template<typename T>
	T pop() {
		if (m_head == 0) {
			// Empty Stack do something
			return 0;
		}

		return cast<T>(&m_stack[--m_head])->GetValue();
	}

	tempate<typename T>
	void push() {
		if ( m_head == STACK_SIZE ) {
			// Full Stack do something
		}

		m_stack[m_head++] = // TODO: Figure out how to manage memory here
	}

private:
	class StackEntry {
	};

	template<typename T>
	class RealStackEntry : public StackEntry {
	public:
		RealStackEntry(T entry) : m_entry(entry) { }
		T GetValue() { return m_entry; }
	private:
		const T m_entry;
	};

	template<typename T>
	RealStackEntry<T>* cast(StackEntry *entry) {
		return static_cast<RealStackEntry<T>*>(entry);
	}

	StackEntry m_stack[STACK_SIZE];
	uint8_t m_head;
};