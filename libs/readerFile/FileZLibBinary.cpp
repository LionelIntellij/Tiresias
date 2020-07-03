#include "FileZLibBinary.h"
#include <algorithm>
#include <iostream>

namespace smartDescriptor {
    namespace readerFile {

        FileZLibBinary::FileZLibBinary(const std::string &filenameInput):m_fileSize(0) {
            m_file = gzopen(filenameInput.c_str(), "rb");

            if (m_file == nullptr) {
                std::cerr << "Error: Failed to gzopen " << filenameInput << std::endl;
                exit(0);
            }
        }


        bool FileZLibBinary::getBlockData(size_t &bufferSize, unsigned char **buffer) {

            *buffer = new unsigned char[BUFFER_SIZE];
            int numberRead = gzread(m_file, *buffer, BUFFER_SIZE);
            bufferSize = (size_t) numberRead;
            m_fileSize += numberRead;
            return numberRead != 0;
        }
    }
}