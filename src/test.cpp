// #include "ledvm/ledvm.h"
#include "version.h"
#include "devices/logged_accel.h"
#include "csvfile.h"

#include <iostream>

int main() {
    simulator::CSVFile csv("");
    csv.Next();

    std::cout << "LedVM Version: " << LEDVM_VERSION_STR << std::endl;

    ledvm::ILedDevice_p device = new simulator::AccelZDevice(&csv);
    std::cout << "Added Device: " << device->GetName() << std::endl;

    return 0;
}
