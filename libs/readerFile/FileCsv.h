#ifndef READER_FILE_CSV_H
#define READER_FILE_CSV_H
#include "FileParameters.h"
#include "Utils.h"
#include <fstream>

namespace smartDescriptor {

    namespace readerFile {

        class FileCsv {
        private:
            std::ifstream  m_file ;

        public:
            FileCsv(FileParameters & fileParameters);

            ~FileCsv() { m_file.close(); }

            bool getLineFile(std::string &line);
        };
    }
}

#endif