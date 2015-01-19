#pragma once

#include "leddevice.h"

#define X_AXIS 'X', 1
#define Y_AXIS 'Y', 2
#define Z_AXIS 'Z', 3

namespace simulator {

    class CSVFile {};

    template <char NAME, int INDEX>
    class AccelAxisDevice : public ledvm::ILedDevice {
        public:
            AccelAxisDevice(const CSVFile* const logfile);
            virtual const char GetName();
            virtual bool Update();
            virtual float Get();

        private:
            const CSVFile* m_logfile;
            float m_value;
    };

    template <char NAME, int INDEX>
    AccelAxisDevice<NAME, INDEX>::AccelAxisDevice(const CSVFile* const logfile)
        : m_logfile (logfile)
        , m_value (0)
    {
    }

    template <char NAME, int INDEX>
    const char AccelAxisDevice<NAME, INDEX>::GetName()
    {
        return NAME;
    }

    template <char NAME, int INDEX>
    bool AccelAxisDevice<NAME, INDEX>::Update()
    {
        return true;
    }


    template <char NAME, int INDEX>
    float AccelAxisDevice<NAME, INDEX>::Get()
    {
        return m_value;
    }

    using AccelXDevice = AccelAxisDevice<X_AXIS>;
    using AccelYDevice = AccelAxisDevice<Y_AXIS>;
    using AccelZDevice = AccelAxisDevice<Z_AXIS>;
}
