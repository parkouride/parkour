#pragma once
#define LEDIMUFF_H

#include <memory>
#include "imurunner.h"

#ifndef LEDIMU_FILENAME
#define LEDIMU_FILENAME "ledimu.prog"
#endif // LEDIMU_FILENAME

#ifdef SD_H
 #define SDFILE File
 #define SDOPENREAD(filename) SD.open(filename)
 #define SDOPENWRITE(filename) SD.open(filename, FILE_WRITE)
 #define SDOPENAPPEND(filename) SD.open(filename, FILE_WRITE)
#else // SD_H
 #ifdef SD_EMU_H 
 #include <stdio.h>
 #define SDFILE FILE*
 #define SDOPENREAD(filename) fopen(filename, "r")
 #define SDOPENWRITE(filename) fopen(filename, "w")
 #define SDOPENAPPEND(filename) fopen(filename, "a")
 #else // SD_EMU_H
  #error "You must include a SD File library before including ledimuff.h"
 #endif // SD_EMU_H
#endif // SD_H

#ifndef LEDIMU_READONLY
// #include "ledimu_data.h"
typedef struct LedImuHeader LedImuHeader_t;
typedef LedImuHeader_t* LedImuHeader_ptr;

typedef struct LedImuStateAllocationEntry LedImuStateAllocationEntry_t;
typedef LedImuStateAllocationEntry_t* LedImuStateAllocationEntry_ptr;

typedef struct LedImuStateAllocationTable LedImuStateAllocationTable_t;
typedef LedImuStateAllocationTable_t* LedIumStateAllocationTable_ptr;
#endif // LEDIMU_READONY

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
  bool Write(LedImuHeader_t);
  bool Write(char *filename);
#endif // LEDIMU_READONY

private:
  SDFILE m_file;
  std::unique_ptr<ImuRunner> m_runner;

};
