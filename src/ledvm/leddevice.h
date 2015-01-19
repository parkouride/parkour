#pragma once

namespace ledvm {

    class ILedDevice {
        public:
            virtual const char* GetName() = 0;
            virtual bool Update() = 0;
            virtual float Get() = 0;
    };
    using ILedDevice_p = ILedDevice*;
}
