#include <memory>

#include "gtest/gtest.h"

#define SD_EMU_H
#define LEDIMU_FILENAME "data/test.prog"
#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"

class MockRunner : public ImuRunner
{
	virtual ImuRunner &operator=(ImuRunner && o ) {
		return *this;
	}
};

TEST(LoadTest, default_filename)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner);

	ASSERT_EQ(ledimufile.Load(LEDIMU_FILENAME), LedImuFileError::success);
}

TEST(LoadTest, invalid_filename)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner);

	ASSERT_EQ(ledimufile.Load("blahblah"), LedImuFileError::file_not_found);	
}

TEST(LoadTest, invalid_magic_marker)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner);

	ASSERT_EQ(ledimufile.Load("data/invalid_marker.prog"), LedImuFileError::invalid_file);
}