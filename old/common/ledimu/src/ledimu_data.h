#pragma once

#include "types.h"

namespace ledvm {

struct LedImuHeader
{
	char start_marker[4];
	uint8_t state_count;
	uint8_t required_pixel_count;
	uint16_t vm_version;
	uint16_t requirements;
	uint16_t state_name_mapping_position;
	uint16_t state_decision_position;

	// number of shorts = state_count
	uint16_arr state_position;
	char end_marker[4];
};

struct LedImuData
{
	LedImuHeader* header;
};

} // namespace ledvm
