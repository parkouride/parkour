#pragma once

class ImuRunner
{
public:
  ImuRunner() {}
  // Some functions for doing things when a byte is received
  ImuRunner(ImuRunner const &) = delete;
  ImuRunner(ImuRunner && o);
  ImuRunner &operator=(ImuRunner const &) = delete;
  virtual ImuRunner &operator=(ImuRunner && o) = 0;
  virtual void commit() = 0;
};
