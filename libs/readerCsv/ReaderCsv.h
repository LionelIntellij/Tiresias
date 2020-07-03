#ifndef READER_CSV_H
#define READER_CSV_H

#include "Utils.h"
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>
#include "FileParameters.h"
#include "Header.h"
#include <iostream>


namespace smartDescriptor {

    namespace readerCsv {

        struct ParamFile {
            ParamFile() : delimiter(';'), numberLine(0), numberField(0), escape('\\'), quote('\"') {
            }
            char delimiter;
            size_t numberLine;
            size_t numberField;
            bool carriage = false;
            char escape = '\\';
            char quote = '\"';
        };

        typedef boost::tokenizer<boost::escaped_list_separator<char> > Tokenizer;

        template<class FileType>
        class ReaderCsv {
        public:
            ReaderCsv(const ParamFile &paramFile, FileType *file);

            bool getRecord(size_t &offset, std::vector<std::string> &record);

            void getStatistics(std::string &statistics);

        private:

            size_t m_offset;
            FileType * m_file = nullptr;
            size_t m_numberField;
            size_t m_numberLine;
            std::vector<size_t> m_sizeToRejected;
            std::vector<size_t> m_indexToRejected;
            boost::escaped_list_separator<char> m_els;

            //Methods
            void get(std::string &line, std::vector<std::string> &record);
        };

#include "ReaderCsv.tpp"

    }
}
#endif
