#include "SearchHeader.h"


namespace smartDescriptor
{
    namespace header
    {
        SearchHeader::SearchHeader(const double threshold, const Header &header,
                                   const smartDescriptor::buffer::DataAnalysis &dataAnalysis) : m_dataAnalysis(
                dataAnalysis), m_header(header), m_threshold(threshold), m_numberField(m_dataAnalysis.getNumberField())
        {
            m_foundHeader = true;
        }

        bool SearchHeader::hasHeader()
        {
            hasSameSize();
            if (m_foundHeader)
            {
                std::vector<FeaturesData> featuresHeader;
                std::vector<FeaturesData> featuresData;
                headerAnalysis(featuresHeader);
                dataAnalysis(featuresData);
                voteHasHeader(featuresHeader, featuresData);
                m_foundHeader = (m_isHeader - m_isNotHeader) > 0;
            }
            return m_foundHeader;
        }


        void SearchHeader::hasSameSize()
        {
            if (m_header.getSize() != m_numberField)
            {
                m_foundHeader = false;
            }

            if (m_foundHeader)
            {
                for (size_t indexField = 0; indexField < m_numberField; ++indexField)
                {
                    if (m_header.get(indexField).empty())
                    {
                        m_foundHeader = false;
                    }
                }
            }
        }


        size_t SearchHeader::wordAnalysis(const std::string &word, FeaturesData &featureWord)
        {
            size_t sizeField = 0;
            size_t sizeDigit = 0;
            bool hasEmail = false;
            for (const char characterWord :word)
            {
                if (isdigit(characterWord))
                {
                    sizeDigit++;
                }
                if (characterWord == '@')
                {
                    hasEmail = true;
                }
                sizeField++;
            }
            if (sizeDigit > 0)
            {
                featureWord.hasDigit++;
                if (sizeDigit == sizeField)
                {
                    featureWord.isNumeric++;
                }
                if (hasEmail)
                {
                    featureWord.hasEmail++;
                }
            }
            return sizeField;
        }


        void SearchHeader::dataAnalysis(std::vector<FeaturesData> &featuresData)
        {
            size_t sizeField = 0;
            std::unordered_map<size_t, size_t> sizeColumns;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                FeaturesData featureData;
                featureData.numberLine = m_dataAnalysis.getSize(indexField);
                for (size_t index = 0; index < featureData.numberLine; ++index)
                {
                    sizeField = wordAnalysis(m_dataAnalysis.get(indexField, index), featureData);
                    if (sizeField > 0)
                    {
                        sizeColumns[sizeField]++;
                    }
                }
                setSizeColumn(sizeColumns, featureData);
                sizeColumns.clear();
                featuresData.push_back(featureData);
            }
        }


        void SearchHeader::setSizeColumn(const std::unordered_map<size_t, size_t> &sizeColumn,
                                    FeaturesData &featuresData)
        {
            size_t instanceSizeMax = 0;
            size_t sizeField = 0;
            for (const auto &instanceColumn : sizeColumn)
            {
                if (instanceSizeMax < instanceColumn.second)
                {
                    instanceSizeMax = instanceColumn.second;
                    sizeField = instanceColumn.first;
                }
            }
            if (instanceSizeMax / ((double)featuresData.numberLine) > m_threshold)
            {
                featuresData.size = sizeField;
            }
            else
            {
                featuresData.size = 0;
            }
        }

        void SearchHeader::vote(bool condition)
        {
            if (condition)
            {
                m_isNotHeader++;
            }
            else
            {
                m_isHeader++;
            }
        }

        void SearchHeader::voteHasHeader(const std::vector<FeaturesData> &featuresHeader,
                                         const std::vector<FeaturesData> &featuresData)
        {
            for (size_t idColumn = 0; idColumn < m_numberField; ++idColumn)
            {
                if (featuresData[idColumn].size != 0)
                {
                    vote(featuresData[idColumn].size == featuresHeader[idColumn].size);
                }
                if (featuresData[idColumn].isNumeric / ((double)featuresData[idColumn].numberLine) > m_threshold)
                {
                    vote(featuresHeader[idColumn].isNumeric > 0);
                }
                if (featuresData[idColumn].hasDigit / ((double)featuresData[idColumn].numberLine) > m_threshold)
                {
                    vote(featuresHeader[idColumn].hasDigit > 0);
                }
                if (featuresData[idColumn].hasEmail / ((double)featuresData[idColumn].numberLine) > m_threshold)
                {
                    vote(featuresHeader[idColumn].hasEmail > 0);
                }
            }
        }

        void SearchHeader::headerAnalysis(std::vector<FeaturesData> &featuresHeader)
        {
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                FeaturesData feature;
                feature.size = wordAnalysis(m_header.get(indexField), feature);
                feature.numberLine = 1;
                featuresHeader.push_back(feature);
            }
        }

        void SearchHeader::getStatistics(std::string &statistics)
        {
            statistics = "-------------- Search Header ----------------\n";
            statistics += "has header : " + std::to_string(m_isHeader) + " \n";
            statistics += "has not header : " + std::to_string(m_isNotHeader) + " \n";
        }
    }
}