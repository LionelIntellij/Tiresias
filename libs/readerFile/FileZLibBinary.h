#ifndef READER_FILE_ZLIB_BINARY_H
#define READER_FILE_ZLIB_BINARY_H

#include <zlib.h>
#include "Utils.h"

namespace smartDescriptor {

    namespace readerFile {

        class FileZLibBinary {

        public:
            explicit FileZLibBinary(const std::string & filenameInput);

            ~FileZLibBinary(){gzclose(m_file);};


            bool getBlockData(size_t & bufferSize, unsigned char **buffer);

            size_t getFileSize(){return m_fileSize;};

        private:
            size_t m_fileSize;
            gzFile m_file;
        };
    }
}
#endif