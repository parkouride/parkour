#include "ledimuff.h"

LedImuFile::LedImuFile(std::unique_ptr<ImuRunner> &runner) : m_runner(std::move(runner))
{
}

bool LedImuFile::Load()
{
    return Load(LEDIMU_FILENAME);
}

bool LedImuFile::Load(const char *filename)
{
    return false;
}

#ifndef LEDIMU_READONLY
#include "_ledimuff_write.cpp"
#endif // LEDIMU_READONLY
