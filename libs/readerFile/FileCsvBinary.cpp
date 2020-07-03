#include "FileCsvBinary.h"
#include <algorithm>

namespace smartDescriptor {
    namespace readerFile {
        FileCsvBinary::FileCsvBinary(const smartDescriptor::readerFile::FileParameters &fileParameters) {
            m_file = fopen(fileParameters.getFilenameInput().c_str(), "rb");
            fseek(m_file, 0, SEEK_END);
            m_fileSize = (size_t)ftell(m_file);
            m_offset = m_fileSize;
            fseek(m_file, 0, SEEK_SET);
        }


        bool FileCsvBinary::getBlockData(size_t &bufferSize, unsigned char **buffer) {
            if (m_offset == 0) {
                return false;
            } else {
                bufferSize = std::min<size_t>(BUFFER_SIZE, m_offset);
                *buffer = new unsigned char[bufferSize];
                fread(*buffer, bufferSize, 1, m_file);
                m_offset -= bufferSize;
                return true;
            }
        }
    }
}