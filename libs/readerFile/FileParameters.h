#ifndef READER_FILE_PARAMETERS_H
#define READER_FILE_PARAMETERS_H

#include <string>
#include <deque>
#include "Params.h"
#include "Utils.h"

namespace smartDescriptor
{
    namespace readerFile
    {
        class FileParameters
        {
        public:
            explicit FileParameters(const std::string &filenameInput);

            const std::string &getFilenameInput() const;

            Extension getExtension() const;

            Archive getArchive() const;

            Compressed getCompressed() const;

        private:
            //Attributs
            std::string m_filenameInput;
            Extension m_extension;
            Compressed m_compressed;
            Archive m_archive;


            //Methods
            void setArchive(const std::deque<std::string> &extensions);

            void setExtension(const std::deque<std::string> &extensions);

            void setCompressed(const std::deque<std::string> &extensions);

            void setUpper(std::deque<std::string> &extensions);
        };
    }
}
#endif