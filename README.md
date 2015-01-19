parkour
=======

** I'M REWRITING THE LIBRARY TO CLEAN UP THE API AND MAKE IT BETTER, this will let it work better onthe arduino, and taking into account the things I learned
from the first draft of the library.**

**This is a work in progress, nothing works yet**

A programmable LED controller + IDE. By virtualizing the control of the leds, we can program the controller by swapping out
sd cards or just renaming files on the card.

**Why is it named parkour?** I named the project parkour because that's what I'm going to be doing while wearing the devices that I'm making.  I'm going to be light painting with my body when this system is finished.

hardware
--------

Details coming soon, but you need at least, [arduino](https://www.sparkfun.com/products/11113),
[sd card reader](https://www.adafruit.com/products/254), and [leds](https://www.adafruit.com/products/1426)

My hardware setup also includes an [IMU](https://www.adafruit.com/products/1604) for adding interactivity to the device.

ide
---

Details coming soon

simulator
---------

The simulator runs using cinder to visualize the LED programs being run.  (eventually) You can feed
recorded IMU data to test how your leds will react to the motion that was recorded.

Here are some sample videos:

[![Simple On and Off states](http://img.youtube.com/vi/aTuiwGLYea4/0.jpg)](https://www.youtube.com/watch?v=aTuiwGLYea4)

firmware
--------

Details coming soon

compiler + intermediate language
--------------------------------

The IDE generates an intermediate language representation of the program before passing the code off to the compiler.
The compiler builds the binary files for the controller, which are added to the sd card.

The compiler is written in python using pyparsing to generate the binary data from the IL representation which is a small
language which is close to an assembly language with block designators.

common library
--------------

A set of C++ classes that run on both the arduino and in the IDE.  This allows us to feed the binary file into the real
device and a simulation running in the ide so you can see exactly how your light patterns will react.
