#ifndef READER_FILE_ARCHIVE_H
#define READER_FILE_ARCHIVE_H

#include "FileParameters.h"
#include <sstream>
#include <fstream>
#include <archive.h>
#include "Utils.h"
#include <deque>
#include <archive_entry.h>

namespace smartDescriptor
{
    namespace readerFile
    {

        class FileArchive
        {
            public:
            explicit FileArchive(const FileParameters &fileParameters);

            bool getLineFile(std::string &line);

            private:
            //attribut
            const void *m_data = nullptr;
            struct archive *m_archiveFile = nullptr;
            struct archive_entry *m_entry = nullptr;
            std::deque<std::string> m_buffer;
            size_t m_size;
            size_t m_sizeBuffer = 0;
            la_int64_t m_offset;

            //Methods
            bool getBlockFile();

            void setArchive(Archive archive);

            void setFilter(Compressed compressed);


        };
    }
}
#endif