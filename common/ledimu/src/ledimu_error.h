#pragma once

// #define CHECK_ERROR(x) if ((retval=x) != 0) { return retval; }
// #define CHECK_ERROR_NULL(x) if (x != 0) { return nullptr; }
#define CHECK_ERROR(x) x;
#define CHECK_ERROR_NULL(x) x

typedef enum LedImuFileErrorEnum
{
  unknown_error = -1,
  success = 0,
  file_not_found,
  invalid_file,
  no_states_specified,
  not_enough_pixels,
} LedImuFileError;