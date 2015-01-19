#include "csvfile.h"

namespace simulator {

CSVFile::CSVFile(const char *filename)
    : m_file(filename)
    , m_line("")
{
}

CSVFile::~CSVFile() {
    m_file.close();
}

template <typename T>
T CSVFile::Get(int index) {
    T retval;
    size_t position = 0;
    bool done = false;

    while (!done) {
        size_t found = m_line.find_first_of(',', position);
        if (found == std::string::npos) {
            done = true;
            retval = 0;
        }
        --index;
        if (index == 0) {
            done = true;
            m_file >> retval;
        }
    }

    return retval;
}


bool CSVFile::Next() {
    std::string tmp;
    std::getline(m_file, tmp);
    if (m_file.fail()) {
        return false;
    }

    m_line = tmp;

    return true;
}

void CSVFile::Reset() {
    m_file.seekg(0, m_file.beg);
}

}
