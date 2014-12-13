#pragma once
#define LEDIMUFF_H

#include <memory>
#include "ledimu_error.h"

#ifndef LEDIMU_FILENAME
#define LEDIMU_FILENAME "ledimu.prog"
#endif // LEDIMU_FILENAME

#ifdef SD_H
 #define SDFILE(name) File name
#else // SD_H
 #ifdef SD_EMU_H 
 #include <iostream>
 #include <fstream>
 #ifdef LEDIMU_READONLY
  #define STREAM_TYPE std::istream
 #else
  #define STREAM_TYPE std::iostream
 #endif // LEDIMU_READONLY
#define SDFILE(name) std::unique_ptr<STREAM_TYPE> name

 #else // SD_EMU_H
  #error "You must include a SD File library before including ledimuff.h"
 #endif // SD_EMU_H
#endif // SD_H

struct LedImuHeader;
typedef struct LedImuData LedImuData_t;
typedef struct LedImuStateAllocationEntry LedImuStateAllocationEntry_t;
typedef struct LedImuStateAllocationTable LedImuStateAllocationTable_t;
class ImuRunner;


class LedImuFile
{
public:
  LedImuFile(std::unique_ptr<ImuRunner> & runner);
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

private:
  SDFILE(m_file);
  std::unique_ptr<ImuRunner> m_runner;
  struct LedImuHeader m_header;

  LedImuFileError read_header();
  LedImuFileError read_magic_marker(char *buffer, const char marker[4]);
  template<typename T>
  LedImuFileError read(T *buffer);
};
