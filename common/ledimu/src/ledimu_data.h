#pragma once

#include <cstdint>
#include <memory>

struct LedImuHeader
{
	char start_marker[4];
	uint8_t state_count;
	uint16_t state_name_mapping_position;
	uint16_t state_decision_position;

	// number of shorts = state_count
	std::unique_ptr<uint16_t[]> state_position;
	char end_marker[4];
};

struct LedImuData
{
	LedImuHeader* header;
};