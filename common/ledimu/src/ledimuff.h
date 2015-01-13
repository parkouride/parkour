#pragma once
#define LEDIMUFF_H
#ifdef ARDUINO
#include <arduino.h>
#endif // ARDUINO

#include <memory>
#include "ledimu_error.h"

#ifndef LEDIMU_FILENAME
#define LEDIMU_FILENAME "ledimu.prog"
#endif // LEDIMU_FILENAME

#include <iostream>
#include <fstream>
#include <tuple>

#include "ledimu_data.h"
#include "ledimu_error.h"
#include "imurunner.h"
#include "stack.h"

namespace ledvm {

#define RET_NULL_IF_FAILED(x) if (!x->WasSuccess()) { return nullptr; }
#define RET_NULL_IF_FAIL(x) if (!(x)) { return nullptr; }
#define RET_IF_FAILED(x, y) if (!(x)) { return y; }
    
    typedef struct LedImuData LedImuData_t;
    typedef struct LedImuStateAllocationEntry LedImuStateAllocationEntry_t;
    typedef struct LedImuStateAllocationTable LedImuStateAllocationTable_t;
    
    using uint8_uptra = std::unique_ptr<uint8_t[]>;
    
    template <class T, class R>
    class LedImuFile
    {
#define IN_LEDIMUFILECLASS
    public:
        LedImuFile(const uint8_t pixel_count, const char *filename)
        : m_file{filename},
        m_runner{pixel_count},
        m_pixel_count(pixel_count) {}
        ~LedImuFile() {}
        
        uint8_t GetNumberStates() { return m_header.state_count; }
        uint16_t GetNamePosition() { return m_header.state_name_mapping_position; }
        uint16_t GetDecisionPosition() { return m_header.state_decision_position; }
        R* GetRunner() { return &m_runner; }
        
#include "ledimuff_static.t.hpp"
#include "ledimuff_public.t.hpp"
        
    private:
        T m_file;
        R m_runner;
        int m_pixel_count;
        struct LedImuHeader m_header;
        bool loaded = false;
        
#include "ledimuff_load.t.hpp"
#include "ledimuff_run.t.hpp"
        
#undef IN_LEDIMUFILECLASS
    };
    
} // namespace ledvm
