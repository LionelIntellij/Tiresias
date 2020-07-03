#include "DetectZipCode.h"


namespace smartDescriptor
{
    namespace detection
    {

        DetectZipCode::DetectZipCode(const double threshold, const buffer::DataAnalysis &dataAnalysis) : m_threshold(
                threshold), m_dataAnalysis(dataAnalysis), m_numberField(dataAnalysis.getNumberField())
        {
            m_likelihood = std::vector<double>(m_numberField, 0.0);
            m_unlikelihood = std::vector<double>(m_numberField, 0.0);
            m_isZipCode =std::regex("[0-9]{5}");
        }


        void DetectZipCode::buildLikelihood(const std::vector<bool> &toCheck, std::vector<size_t> &indexFields)
        {
            std::vector<size_t> checkIndex;
            std::vector<std::string> words;
            std::string zipCode;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                if (toCheck[indexField])
                {
                    for (size_t index = 0; index < m_dataAnalysis.getSize(indexField); ++index)
                    {
                        m_dataAnalysis.getSplitBlank(indexField, index, words);
                        hasZipCode(words.begin(), words.end(), zipCode);
                        if (!zipCode.empty())
                        {
                            m_likelihood[indexField]++;
                        }
                        if (zipCode.empty() || (!zipCode.empty() && words.size() > 1))
                        {
                            m_unlikelihood[indexField]++;
                        }
                    }
                    if (m_dataAnalysis.getSize(indexField) > 0)
                    {
                        m_likelihood[indexField] = m_likelihood[indexField] /(double) m_dataAnalysis.getSize(indexField);
                        m_unlikelihood[indexField] = m_unlikelihood[indexField] / (double)m_dataAnalysis.getSize(indexField);
                        checkIndex.push_back(indexField);
                    }
                }
            }
            chooseField(checkIndex, indexFields);
        }


        void DetectZipCode::decisionZipCode(std::vector<smartDescriptor::DescriptorField> &descriptor,
                                            std::vector<bool> &toCheck)
        {
            std::vector<size_t> indexFields;
            std::vector<FeaturesZipCode> features;
            buildLikelihood(toCheck, indexFields);
            setFeatures(indexFields, features);
            for (const size_t indexField :indexFields)
            {
                toCheck[indexField] = false;
            }
            if (!indexFields.empty())
            {
                computeLikelihood(features);
                std::vector<size_t> indexZipCode;
                chooseField(indexFields, indexZipCode);
                for (const size_t indexField :indexZipCode)
                {
                    smartDescriptor::DescriptorField descriptorZipCode(indexField, ZIPCODE);
                    descriptorZipCode.likelihood = m_likelihood[indexField];
                    descriptorZipCode.unlikelihood = m_unlikelihood[indexField];
                    descriptor.push_back(descriptorZipCode);
                }
            }
        }


        void DetectZipCode::computeLikelihood(const std::vector<FeaturesZipCode> &features)
        {
            double likelihood = 0;
            size_t size;
            for (const FeaturesZipCode &featuresZipCode : features)
            {
                size = m_dataAnalysis.getSize(featuresZipCode.indexField);
                likelihood = 2. / 6 * m_likelihood[featuresZipCode.indexField];
                likelihood += 2. / 6 * (featuresZipCode.hasDifferentDigit / (double)size);
                likelihood += 1. / 6 * (featuresZipCode.endByNull / (double)size);
                likelihood += 1. / 6 * (featuresZipCode.hasDifferentZip / (double)size);
                m_likelihood[featuresZipCode.indexField] = likelihood;
            }
        }

        void DetectZipCode::setFeatures(const std::vector<size_t> &indexFields, std::vector<FeaturesZipCode> &features)
        {
            std::string zipCode;
            std::string oldZipCode;
            std::vector<std::string> words;
            for (const size_t indexField :indexFields)
            {
                FeaturesZipCode featuresZipCode(indexField);
                for (size_t index = 0; index < m_dataAnalysis.getSize(indexField); ++index)
                {
                    m_dataAnalysis.getSplitBlank(indexField, index, words);
                    hasZipCode(words.begin(), words.end(), zipCode);
                    featuresZipCode.hasDifferentDigit += hasDifferentDigit(zipCode.begin(), zipCode.end());
                    if (*(zipCode.end()-1) == '0')
                    {
                        featuresZipCode.endByNull++;
                    }
                    if (zipCode != oldZipCode)
                    {
                        featuresZipCode.hasDifferentZip++;
                    }
                    features.push_back(featuresZipCode);
                    oldZipCode = zipCode;
                }
            }
        }


        void DetectZipCode::hasZipCode(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end,
                                       std::string &zipCode)
        {
            zipCode.clear();
            while (begin != end)
            {
                if (std::regex_match(*begin, m_isZipCode))
                {
                    zipCode = *begin;
                    begin = end;
                }
                else
                {
                    begin++;
                }
            }
        }

        int DetectZipCode::hasDifferentDigit(std::string::const_iterator begin, std::string::const_iterator end)
        {
            int hasDifferent = 0;
            while (begin + 1 != end)
            {
                if ((*begin) != *(begin + 1))
                {
                    begin = end-1;
                    hasDifferent++;
                }
                else
                {
                    begin++;
                }
            }
            return hasDifferent;
        }

        void DetectZipCode::chooseField(const std::vector<size_t> &checkIndex, std::vector<size_t> &indexFields)
        {
            double consistency = 1.0;
            while (consistency > m_threshold && indexFields.empty())
            {
                for (const size_t indexField :checkIndex)
                {
                    if (m_likelihood[indexField] > consistency)
                    {
                        indexFields.push_back(indexField);
                    }
                }
                consistency -= 0.01;
            }
        }

        void DetectZipCode::getStatistics(std::string &statistics)
        {
            statistics = "- Statistics detection zipCode -\n";
            std::string statisticsInstance = "| index |    stats zipCode    |\n";
            boost::format format("|   %2d  |       %.2f        |\n");
            size_t index;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                index = indexField + 1;
                if (m_likelihood[indexField] > 0.0)
                {
                    format % index % m_likelihood[indexField];
                    statisticsInstance += format.str();
                }
            }
            if (!statisticsInstance.empty())
            {
                statistics += statisticsInstance;
            }
            else
            {
                statistics += "          Email no Found        ";
            }
        }

        FeaturesZipCode::FeaturesZipCode(size_t indexField) : indexField(indexField), hasDifferentDigit(
                0), hasDifferentZip(0), hasOtherWord(0), endByNull(0)
        {
        }


    }
}
