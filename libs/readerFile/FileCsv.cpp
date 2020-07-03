#include "FileCsv.h"

namespace smartDescriptor {
    namespace readerFile {
        FileCsv::FileCsv(FileParameters & fileParameters):
                m_file(std::ifstream(fileParameters.getFilenameInput())) {
        }

        bool FileCsv::getLineFile(std::string &line) {
            return std::getline(m_file, line) ? true : false;
        }
    }
}