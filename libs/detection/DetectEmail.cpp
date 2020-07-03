#include "DetectEmail.h"
#include <boost/format.hpp>
#include <regex>

namespace smartDescriptor
{
    namespace detection
    {

        DetectEmail::DetectEmail(const double threshold, const buffer::DataAnalysis &dataAnalysis) : m_threshold(
                threshold), m_dataAnalysis(dataAnalysis), m_numberField(m_dataAnalysis.getNumberField())
        {
            m_likelihood = std::vector<double>(m_numberField, 0.0);
            m_unlikelihood = std::vector<double>(m_numberField, 0.0);
            m_isEmail = std::regex(R"((\w+)((\.|_)?(\w*))+@(\w+)(\.(\w+))+)");
        }

        void DetectEmail::buildLikelihood(const std::vector<bool> &toCheck)
        {
            size_t size;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                if (toCheck[indexField])
                {
                    size = m_dataAnalysis.getSize(indexField);
                    for (size_t index = 0; index < size; ++index)
                    {
                        if (std::regex_match(m_dataAnalysis.get(indexField, index), m_isEmail))
                        {
                            m_likelihood[indexField]++;
                        }
                        else
                        {
                            m_unlikelihood[indexField]++;
                        }
                    }
                    if (size > 0)
                    {
                        m_likelihood[indexField] /=(double)size;
                        m_unlikelihood[indexField] /=(double)size;
                    }
                }
            }
        }

        void DetectEmail::decisionEmail(std::vector<smartDescriptor::DescriptorField> &descriptor,
                                        std::vector<bool> &toCheck)
        {

            buildLikelihood(toCheck);
            std::vector<size_t> indexFields;
            chooseEmail(toCheck, indexFields);
            for (const size_t indexField : indexFields)
            {
                smartDescriptor::DescriptorField descriptorField(indexField, EMAIL);
                descriptorField.likelihood = m_likelihood[indexField];
                descriptorField.unlikelihood = m_unlikelihood[indexField];
                descriptor.push_back(descriptorField);
            }

        }

        void DetectEmail::chooseEmail(const std::vector<bool> &toCheck, std::vector<size_t> &indexFields)
        {
            double consistency = 1.0;
            while (consistency >= m_threshold && indexFields.empty())
            {
                for (size_t indexField = 0; indexField < m_numberField; ++indexField)
                {
                    if (toCheck[indexField])
                    {
                        if (m_likelihood[indexField] > consistency)
                        {
                            indexFields.push_back(indexField);
                        }
                    }
                }
                consistency -= 0.01;
            }
        }

        void DetectEmail::getStatistics(std::string &statistics)
        {
            statistics = "- Statistics detection email -\n";
            std::string statisticsInstance = "| index |    stats email    |\n";
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

    }
}