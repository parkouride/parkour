#pragma once

#include <fstream>

namespace simulator {

    class CSVFile {
        public:
           CSVFile(const char* filename);
           ~CSVFile();
    
           template <typename T>
           T Get(int index);
    
           bool Next();
           void Reset();
    
        private:
           std::ifstream m_file;
           std::string m_line; 

    };

    template<> float CSVFile::Get<float>(int index);
    template<> int CSVFile::Get<int>(int index);
    template<> std::string CSVFile::Get<std::string>(int index);

}
