#ifndef READER_FILE_CSV_BINARY_H
#define READER_FILE_CSV_BINARY_H

#include "FileParameters.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

namespace smartDescriptor {
    namespace readerFile {
        class FileCsvBinary {
        private:
            FILE *m_file;
            size_t m_fileSize;
            size_t m_offset;

        public:
            explicit FileCsvBinary(const FileParameters &fileParameters);

            ~FileCsvBinary() { fclose(m_file); }

             bool getBlockData(size_t & bufferSize, unsigned char **buffer);

            size_t getFileSize(){return m_fileSize;};
        };
    }
}

#endif