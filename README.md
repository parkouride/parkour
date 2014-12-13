Parkour Motion Tracking
=======================

It's not really only for parkour, but the idea is an [IMU](), [Arduino Pro Mini](),
and some [Neopixels]() to turn my body into a lightshow based on my motions.

There is a small bytecode processor that reads from an SD card, and processes it based on the
motion that is coming in. 

There is also a tool that writes the bytecode file to the SD card.  It's written in Openframeworks
and is available in the compiler directory.

bytecode documentation
----------------------

+---------+-----------+-------------+
| op code | arguments | description |
+---------+-----------+-------------+