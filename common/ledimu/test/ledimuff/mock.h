
#include "ledimu_data.h"
#include "ledimuff.h"
#include "imurunner.h"

class MockRunner : public ImuRunner
{
public:
	MockRunner() : ImuRunner(2) {}

	virtual ImuRunner &operator=(ImuRunner && o ) {
		return *this;
	}

	virtual void commit() {

	}

	virtual void set_pixel(const uint8_t pixel, const Color& color) {

	}

	virtual void delay(const uint16_t milliseconds) {
		
	}
};
