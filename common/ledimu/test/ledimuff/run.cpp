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

	virtual void commit() {

	}
};

TEST(RunTest, get_state_no_change)
{
	std::unique_ptr<ImuRunner> runner;
	runner.reset(new MockRunner());
	LedImuFile ledimufile(runner, 2);
    ledimufile.Load(LEDIMU_FILENAME);
    ASSERT_EQ(ledimufile.RunState(0), 0);
}
