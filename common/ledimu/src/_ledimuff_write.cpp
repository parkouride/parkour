// Included from ledimuff.cpp

bool LedImuFile::Write(const char *filename, LedImuData_t& data)
{
	return false;
}

bool LedImuFile::Write(LedImuData_t& data)
{
	return Write(LEDIMU_FILENAME, data);
}