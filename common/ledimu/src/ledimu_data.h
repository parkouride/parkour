#pragma once

#include <cstdint>

struct LedImuHeader
{
	char start_marker[4];
	uint8_t state_count;
	uint16_t state_name_mapping_position;
	uint16_t state_decision_position;
	char end_marker[4];
};

struct LedImuData
{
	LedImuHeader* header;
};