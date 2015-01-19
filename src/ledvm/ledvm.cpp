#include "ledvm.h"
#include "leddevice.h"

#ifndef MAX_DEVICES
#define MAX_DEVICES 3
#endif

#if MAX_DEVICES > 255
#error "Unable to support more than 255 devices"
#endif

namespace ledvm {

    template <typename IO>
    class LedVmFile;

    template <typename IO, typename CTRL>
    class LedVmBase : public ILedVM {
        public:
            LedVmBase() : m_device_count{0} {}
            virtual ILedVM_p Load(const char *filename);
            virtual bool Update();
            virtual int8_t RequiredLeds();
            virtual ILedVM_p Attach(const ILedDevice_p device);

        private:
            ILedDevice_p m_devices[MAX_DEVICES];
            int8_t m_device_count;
    };

    template <typename IO, typename CTRL>
    ILedVM_p LedVmBase<IO, CTRL>::Load(const char *filename) {
        return this;
    }

    template <typename IO, typename CTRL>
    bool LedVmBase<IO, CTRL>::Update() {
        return true;
    }

    template <typename IO, typename CTRL>
    int8_t LedVmBase<IO, CTRL>::RequiredLeds() {
        return 8;
    }

    template <typename IO, typename CTRL>
    ILedVM_p LedVmBase<IO, CTRL>::Attach(const ILedDevice_p device) {
        if (m_device_count >= MAX_DEVICES) {
            return this;
        }

        m_devices[++m_device_count] = device;

        return this;
    }
}
