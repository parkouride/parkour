#pragma once
#define LEDIMUFF_H

#include <memory>
#include "imurunner.h"

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

typedef struct LedImuData LedImuData_t;
typedef struct LedImuStateAllocationEntry LedImuStateAllocationEntry_t;
typedef struct LedImuStateAllocationTable LedImuStateAllocationTable_t;

class ImuRunner;

class LedImuFile
{
public:
  LedImuFile(std::unique_ptr<ImuRunner> & runner);
  ~LedImuFile();

  bool Load();
  bool Load(const char *filename);

  int RunState(int state_number);

#ifndef LEDIMU_READONLY
  bool Write(LedImuData_t&);
  bool Write(const char *filename, LedImuData_t&);
#endif // LEDIMU_READONY

private:
  SDFILE(m_file);
  std::unique_ptr<ImuRunner> m_runner;

};
