#pragma once

struct LedImuHeaderStatic
{
	uint8_t start_marker[4];
	uint8_t state_count;
	uint16_t state_name_mapping_position;
	uint16_t state_decision_position;
	uint8_t end_marker[4];
};

struct LedImuData
{
	LedImuHeaderStatic* header;
};