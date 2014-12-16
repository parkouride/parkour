#pragma once

#include <cstdint>

struct Color_t;
typedef struct Color_t Color; 

class ImuRunner
{
public:
  ImuRunner(uint8_t pixel_count) : m_pixel_count(pixel_count) {};
  // Some functions for doing things when a byte is received
  ImuRunner(ImuRunner const &) = delete;
  ImuRunner(ImuRunner && o);
  ImuRunner &operator=(ImuRunner const &) = delete;
  virtual ImuRunner &operator=(ImuRunner && o) = 0;
  virtual void commit() = 0;
  virtual void set_pixel(const uint8_t position, const Color& color) = 0;
  virtual void delay(const uint16_t milliseconds);
  virtual void set_all(const Color& color);

  virtual ~ImuRunner() {};
private:
  uint8_t m_pixel_count;
};
