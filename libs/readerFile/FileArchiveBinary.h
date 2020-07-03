#ifndef READER_FILE_ARCHIVE_BINARY_H
#define READER_FILE_ARCHIVE_BINARY_H

#include "FileParameters.h"
#include "Utils.h"
#include <archive.h>
#include <archive_entry.h>


namespace smartDescriptor
{

    namespace readerFile
    {

        class FileArchiveBinary
        {

        public:
            explicit FileArchiveBinary(const FileParameters &fileParameters);

            bool getBlockData(size_t &bufferSize, unsigned char **buffer);

            size_t getFileSize()
            {
                return m_fileSize;
            };


        private:
            //attributs
            struct archive *m_archiveFile = nullptr;
            struct archive_entry *m_entry = nullptr;
            size_t m_fileSize;
            la_int64_t m_offset;

            //Methods
            void setArchive(Archive archive);

            void setFilter(Compressed compressed);
        };
    }
}
#endif