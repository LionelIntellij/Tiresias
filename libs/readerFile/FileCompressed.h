#ifndef READER_FILE_COMPRESSED_H
#define READER_FILE_COMPRESSED_H

#include "FileParameters.h"
#include "Utils.h"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace smartDescriptor {

    namespace readerFile {

        class FileCompressed {

        public:
            FileCompressed(FileParameters &fileParamters);

            ~FileCompressed() { m_fileCompressed->close();}

            bool getLineFile(std::string &line);

        private:
            std::ifstream *m_fileCompressed = nullptr;
            boost::iostreams::filtering_istream m_file;
        };
    }
}
#endif