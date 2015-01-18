#pragma once

#ifdef ARDUINO
#include "arduino.h"
#else
#include <cstdint>
#endif

namespace ledvm {

    /******************
     * External classes
     ******************/
    class ILedDevice;
    using ILedDevice_p = ILedDevice*;

    /******************
     * Interface for the LedVM system
     ******************/

    class ILedVM;
    using ILedVM_p = ILedVM*;

    class ILedVM {
        public:

            /******
             * Load the VM from a filename.
             *
             * Returns a pointer to the same object for chaining
             */
            virtual ILedVM_p Load(const char* filename) = 0;

            /******
             * Runs one start in the VM
             *
             * Returns true if successful, or false if error
             */
            virtual bool Update() = 0;

            /*******
             * Returns the number of leds required for the currently loaded VM, or -1 if not available
             */
            virtual int8_t RequiredLeds() = 0;

            /*******
             * Attaches a device to the vm for attaching input devices
             *
             * Returns this for chaining
             */
            virtual ILedVM_p Attach(const ILedDevice_p device) = 0;
    };
}
