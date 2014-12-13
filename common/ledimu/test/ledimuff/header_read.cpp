#include <memory>

#include "gtest/gtest.h"

#define SD_EMU_H
#define LEDIMU_FILENAME "data/test.prog"
#include "ledimuff.h"

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

	ASSERT_TRUE(ledimufile.Load(LEDIMU_FILENAME));
}

TEST(LoadTest, invalid_filename)
{
	std::unique_ptr<ImuRunner> runner;
	LedImuFile ledimufile(runner);

	ASSERT_FALSE(ledimufile.Load("blahblah"));	
}