#ifndef READER_ANALYSIS_DELIMITER_INCLUDED
#define READER_ANALYSIS_DELIMITER_INCLUDED

#include <string>
#include <vector>
#include "Params.h"
#include "CountDelimiter.h"

namespace smartDescriptor {
    namespace readerCsv {

        const std::unordered_map<std::string, unsigned char> delimiterBytes{ // NOLINT
                {";",  0x3B},
                {"|",  0x7C},
                {",",  0x2C},
                {"\t", 0x09}
        };

        class AnalysisDelimiter {
        public:
            explicit AnalysisDelimiter(const ParamsDelimiter &paramsDelimiter);

            void setDelimiter(StatisticsDelimiter &result);

            void computeStatistics(size_t size ,const unsigned char *buffer);

            void getStatistics(std::string &statistics);


        private:
            //attributs
            double m_threshold;
            size_t m_numberLine;
            std::unordered_map<unsigned char, CountDelimiter> m_statistics;
            std::vector<StatisticsDelimiter> m_statisticsResult;

            //methods
            void analysisStatistics();

            size_t getResult(std::vector<StatisticsDelimiter> &statDelimiters);

        };
    }
}

#endif