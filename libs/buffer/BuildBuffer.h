#ifndef BUILD_BUFFER_INCLUDED
#define BUILD_BUFFER_INCLUDED

#include <string>
#include <vector>
#include <deque>
#include "FileParameters.h"
#include "Params.h"
#include "Utils.h"
#include "ReaderCsv.h"
#include "DataAnalysis.h"

namespace smartDescriptor {
    namespace buffer {

        class BuildBuffer {
        public:
            BuildBuffer(size_t minimumLine, const smartDescriptor::readerCsv::ParamFile &paramFile);

            DataAnalysis &getDataAnalysis(smartDescriptor::readerFile::FileParameters &fileParameters);


            bool hasHeader();

            const smartDescriptor::header::Header &getHeader();

        private:
            //attributes

            std::unique_ptr<DataAnalysis> m_dataAnalysis = nullptr;
            std::unique_ptr<smartDescriptor::header::Header> m_header = nullptr;
            smartDescriptor::readerCsv::ParamFile m_paramFile;
            std::vector<Column<std::string>> m_buffer;
            std::vector<size_t> m_instance;
            size_t m_index;
            size_t m_modulo;


            //Methods
            template<typename FileType>
            void getRecord(FileType *file) {
                smartDescriptor::readerCsv::ReaderCsv<FileType> reader(m_paramFile, file);
                std::vector<std::string> record;;
                if (reader.getRecord(m_index, record)) {
                    if (m_index == 1 &&
                        m_paramFile.numberLine > 1) {
                        m_header = std::unique_ptr<smartDescriptor::header::Header>(
                                new smartDescriptor::header::Header(record));
                    } else {
                        computeSize(record);
                    }
                }
                while (reader.getRecord(m_index, record)) {
                    computeSize(record);
                }
            }

            size_t setModulo(size_t numberTotalLine, size_t minimumLine);

            void computeSize(const std::vector<std::string> &lineSplit);

            void getStatistics(std::string &statistics);

            void fillDataAnalysis();
        };
    }
}
#endif
