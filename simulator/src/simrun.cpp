#include <memory>
#include <chrono>
#include <thread>

#include "cinder/Color.h"
#include "ledimu_data.h"
#include "simrun.h"

std::unique_ptr<ci::Color8u> convert_color(const ledvm::Color& rhs)
{
  return std::unique_ptr<ci::Color8u>(new ci::Color8u(rhs.red, rhs.green, rhs.blue));
}

  ledvm::ImuRunner &SimulationRunner::operator=(ledvm::ImuRunner && o)
  {
    return o;
  }

  void SimulationRunner::commit()
  {
    // No commit for simulation
  }

  void SimulationRunner::set_pixel(const uint8_t position, const ledvm::Color& color)
  {
    // assert position < m_pixel_count
    m_leds[position].set_color(convert_color(color));
  }

  void SimulationRunner::delay(const uint16_t milliseconds)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  }

  void SimulationRunner::draw(int start_position)
  {
    for(int i=0; i<m_pixel_count; ++i)
    {
      m_leds[i].draw(start_position + i * step);
    }
  }