#ifndef READER_FILE_BZLIB_BINARY_H
#define READER_FILE_BZLIB_BINARY_H

#include <string>
#include "bzlib.h"
#include "Utils.h"

namespace smartDescriptor{

    namespace readerFile{

         class FileBzLibBinary
         {

         public:
              explicit FileBzLibBinary(const std::string & filenameInput);

             ~FileBzLibBinary() ;

             bool getBlockData(size_t & bufferSize, unsigned char **buffer);

             size_t getFileSize(){return m_fileSize;}
         private:
             size_t m_fileSize;
             BZFILE *m_file;
             FILE * m_fileCompressed;
             int m_bzError;
         };
    }
}


#endif