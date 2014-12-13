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
	LedImuFile ledimufile(runner, 2);

	ASSERT_EQ(ledimufile.Load(LEDIMU_FILENAME), LedImuFileError::success);
}

TEST(LoadTest, invalid_filename)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 2);

	ASSERT_EQ(ledimufile.Load("blahblah"), LedImuFileError::file_not_found);	
}

TEST(LoadTest, invalid_magic_marker)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 2);

	ASSERT_EQ(ledimufile.Load("data/invalid_marker.prog"), LedImuFileError::invalid_file);
}

TEST(LoadTest, pixel_check_enough_pixels)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 2);

	ASSERT_EQ(ledimufile.Load(LEDIMU_FILENAME), LedImuFileError::success);	
}

TEST(LoadTest, pixel_check_not_enough_pixels)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 1);

	ASSERT_EQ(ledimufile.Load(LEDIMU_FILENAME), LedImuFileError::not_enough_pixels);	
}

TEST(HeaderDataTest, state_name_first)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 2);

	ledimufile.Load(LEDIMU_FILENAME);
	ASSERT_STREQ("Test", ledimufile.GetStateName(0).get());
}

TEST(HeaderDataTest, state_name_second)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner, 2);

	ledimufile.Load(LEDIMU_FILENAME);
	ASSERT_STREQ("Test2", ledimufile.GetStateName(1).get());
}
