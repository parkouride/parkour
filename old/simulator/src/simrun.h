#include "imurunner.h"
#include "led.h"


class SimulationRunner : public ledvm::ImuRunner
{
public:
  SimulationRunner(int count)
    : ledvm::ImuRunner(count), 
      m_leds(new Led[count])
    {}
  virtual ledvm::ImuRunner &operator=(ImuRunner && o);
  virtual void commit();
  virtual void set_pixel(const uint8_t position, const ledvm::Color& color);
  virtual void delay(const uint16_t milliseconds);
  void draw(int start_position);

  virtual ~SimulationRunner() {};

private:
  std::unique_ptr<Led[]> m_leds;
};
