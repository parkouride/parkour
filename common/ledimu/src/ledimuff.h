#pragma once
#define LEDIMUFF_H

#include <memory>
#include "ledimu_error.h"

#ifndef LEDIMU_FILENAME
#define LEDIMU_FILENAME "ledimu.prog"
#endif // LEDIMU_FILENAME

#include <iostream>
#include <fstream>
#include <tuple>

struct LedImuHeader;
typedef struct LedImuData LedImuData_t;
typedef struct LedImuStateAllocationEntry LedImuStateAllocationEntry_t;
typedef struct LedImuStateAllocationTable LedImuStateAllocationTable_t;
class ImuRunner;

using uint8_uptra = std::unique_ptr<uint8_t[]>;

class LedImuFile
{
public:
  LedImuFile(std::unique_ptr<ImuRunner> & runner, uint8_t pixel_count);
  ~LedImuFile();

  LedImuFileError Load();
  LedImuFileError Load(const char *filename);

  int RunState(int state_number);

#ifndef LEDIMU_READONLY
  bool Write(LedImuData_t&);
  bool Write(const char *filename, LedImuData_t&);
#endif // LEDIMU_READONY

  uint8_t GetNumberStates() { return m_header.state_count; }
  uint16_t GetNamePosition() { return m_header.state_name_mapping_position; }
  uint16_t GetDecisionPosition() { return m_header.state_decision_position; }
  std::unique_ptr<char[]> GetStateName(int state_number);

private:
  std::unique_ptr<std::ifstream> m_file;
  std::unique_ptr<ImuRunner> m_runner;
  int m_pixel_count;
  struct LedImuHeader m_header;
  bool loaded = false;

  LedImuFileError read_header();
  LedImuFileError read_magic_marker(char *buffer, const char marker[4]);
  
  template<typename T>
  LedImuFileError read(T *buffer);

  template<typename T>
  LedImuFileError read_array(std::unique_ptr<T[]> &buffer, int count);

  template<typename T>
  LedImuFileError read_arguments(T* buffer, int count);

  uint8_uptra get_state(int state_number); // Implicit move?
  int run_state(uint8_t *buffer);
};