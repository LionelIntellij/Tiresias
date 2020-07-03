#ifndef HEADER_SEARCH_HEADER_H
#define HEADER_SEARCH_HEADER_H

#include <map>
#include <vector>
#include <string>
#include "Params.h"
#include "Header.h"
#include "DataAnalysis.h"
#include "Column.h"

namespace smartDescriptor
{
    namespace header
    {

        struct FeaturesData
        {
            size_t numberLine = 0;
            int hasDigit = 0;
            int isNumeric = 0;
            int hasEmail = 0;
            size_t size = 0;
        };

        class SearchHeader
        {
        public:
            SearchHeader(double threshold, const Header &header,
                         const smartDescriptor::buffer::DataAnalysis &dataAnalysis);

            bool hasHeader();

            void getStatistics(std::string &statistics);

        private:

            //attributs
            smartDescriptor::buffer::DataAnalysis m_dataAnalysis;
            Header m_header;
            double m_threshold;
            size_t m_numberField;
            int m_isHeader = 0;
            int m_isNotHeader = 0;
            bool m_foundHeader;


            //Methods
            size_t wordAnalysis(const std::string &word, FeaturesData &featureWord);

            void hasSameSize();

            void dataAnalysis(std::vector<FeaturesData> &featuresData);

            void setSizeColumn(const std::unordered_map<size_t, size_t> &sizeColumn, FeaturesData &featuresData);

            void voteHasHeader(const std::vector<FeaturesData> &featuresHeader,
                               const std::vector<FeaturesData> &featuresData);

            void vote(bool condition);

            void headerAnalysis(std::vector<FeaturesData> &featuresHeader);
        };
    }
}
#endif