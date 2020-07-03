#include "FileBzLibBinary.h"
#include <iostream>

namespace smartDescriptor {

    namespace readerFile {

        FileBzLibBinary::FileBzLibBinary(const std::string &filenameInput) : m_fileSize(0) {
            m_fileCompressed = fopen(filenameInput.c_str(), "r+b");
            m_file = BZ2_bzReadOpen(&m_bzError, m_fileCompressed, 0, 0, nullptr, 0);

            if (m_bzError != BZ_OK) {
                std::cerr << " file bzlib not open " << filenameInput << std::endl;
                exit(0);
            }
        }

        bool FileBzLibBinary::getBlockData(size_t &bufferSize, unsigned char **buffer) {
            if (m_bzError != BZ_STREAM_END && m_bzError == BZ_OK) {
                *buffer = new unsigned char[BUFFER_SIZE];
                int nbrBytes = BZ2_bzRead(&m_bzError, m_file, *buffer, BUFFER_SIZE);
                bufferSize = (size_t) nbrBytes;
                m_fileSize += nbrBytes;
                return true;
            }
            return false;
        }

        FileBzLibBinary::~FileBzLibBinary() {
            BZ2_bzReadClose(&m_bzError, m_file);
            if (m_bzError != BZ_OK) {
                std::cerr << "file not close" << std::endl;
                exit(0);
            }
            fclose(m_fileCompressed);
        }
    }
}