#!/bin/sh

bin/premake4 gmake && \
  (cd build && make) && \
  simulator/LedSimulator.app/Contents/MacOS/LedSimulator
