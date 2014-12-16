#include "imurunner.h"
#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"

#define IF_ERROR(x, y) if (!*x) { return y; }

int LedImuFile::run_state(uint8_t *buffer)
{
	bool done = false;
	uint8_t return_state = 0;
	uint8_t storage[16];
	// Need a stack, probably global for performance?

	while(!done)
	{
		read<uint8_t>(storage);
		IF_ERROR(m_file, -1);

		switch(storage[0]) {
			case 0xFF:  // End of State, Done
				m_runner->commit();
				done = true;
			case 0xFE:  // Transition STATE[1]
				read(&return_state);
			    break;
			case 0x00:  // NOP
				break;
			case 0x01:  // SetAll R[1] G[1] B[1]
				read_arguments<uint8_t>(storage, 3);
				m_runner->set_all(storage);
				break;
			case 0x02:  // Delay MILLISECOND[2]
				read_arguments<uint16_t>(reinterpret_cast<uint16_t*>(storage), 1);
				m_runner->delay(storage[0]);
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