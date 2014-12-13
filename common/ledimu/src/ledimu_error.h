#pragma once

typedef enum LedImuFileErrorEnum
{
  success = 0,
  file_not_found,
  invalid_file,
  no_states_specified
} LedImuFileError;