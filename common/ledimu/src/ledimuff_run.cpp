#include "ledimu_data.h"
#include "ledimuff.h"
#include "ledimu_error.h"

int LedImuFile::run_state(uint8_t *buffer)
{
	return 0;
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

	return run_state(code.get());
}