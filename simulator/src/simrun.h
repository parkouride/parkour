#include "imurunner.h"
#include "led.h"


class SimulationRunner : public ledvm::ImuRunner
{
public:
  virtual ledvm::ImuRunner &operator=(ImuRunner && o);
  virtual void commit();
  virtual void set_pixel(const uint8_t position, const ledvm::Color& color);
  virtual void delay(const uint16_t milliseconds);
  void draw(int pixel, int position);

  int pixel_count() { return m_pixel_count; }

  virtual ~SimulationRunner() {};
};
