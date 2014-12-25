#include "imurunner.h"
#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"
#include "stack.h"

#define IF_ERROR(x, y) if (!*x) { return y; }

using namespace ledvm;

void LedImuFile::push(uint8_t typecode_i, Stack &stack, uint8_t *storage) {
	std::unique_ptr<StackEntry> entry;
	TypeCodes typecode = static_cast<TypeCodes>(typecode_i);
	switch(typecode) {
		case TypeCodes::BYTE:
			read<uint8_t>(storage);
			entry = create_stack_entry<uint8_t>(typecode, storage[0]);
			stack.push(std::move(entry));
			break;
		case TypeCodes::SHORT:
			// read<uint16_t>(storage);
			// entry = create_stack_entry<uint16_t>(typecode,
			// 	(reinterpret_cast<uint16_t*>(storage))[0]);
			// stack.push(entry);
			break;
		case TypeCodes::COLOR:
			break;
		case TypeCodes::UNKNOWN:
		default:
			// TODO: Error Handling
			break;
	}
}

int LedImuFile::run_state(uint8_t *buffer)
{
	bool done = false;
	uint8_t return_state = 0;
	uint8_t storage[16];
	Stack stack;

	while(!done)
	{
		read<uint8_t>(storage);
		IF_ERROR(m_file, -1);

		switch(storage[0]) {
			case 0x00: break; // NOP

			case 0x01: // PUSH
				read<uint8_t>(&storage[1]); // Typecode
				push(storage[1], stack, storage);
				break;

			case 0xFF:  // End of State, Done
				m_runner->commit();
				done = true;
				break;
		}
	}

	return return_state;
}

int LedImuFile::RunState(int state_number)
{
	if (state_number < 0 || state_number > m_header.state_count)
	{
		return -2;
	}

	uint8_uptra code = get_state(state_number);
	if (code == nullptr)
	{
		return -1;
	}

	int retval = run_state(code.get());
	return retval <= 0 ? state_number : retval;
}