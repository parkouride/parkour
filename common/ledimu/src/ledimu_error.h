#pragma once

#define CHECK_ERROR(x) if ((retval=x) != 0) { return retval; }
#define CHECK_ERROR_NULL(x) if (x != 0) { return nullptr; }

typedef enum LedImuFileErrorEnum
{
  success = 0,
  file_not_found,
  invalid_file,
  no_states_specified,
  not_enough_pixels
} LedImuFileError;