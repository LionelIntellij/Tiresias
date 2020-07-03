#include <Descriptor.h>
#include "DetectPhone.h"
#include <boost/format.hpp>

namespace smartDescriptor
{
    namespace detection
    {
        DetectPhone::DetectPhone(const double threshold, const buffer::DataAnalysis &dataAnalysis) : m_dataAnalysis(
                dataAnalysis), m_threshold(threshold), m_numberField(dataAnalysis.getNumberField())
        {
            m_likelihoodMobile = std::vector<double>(m_numberField, 0.0);
            m_likelihoodFixed = std::vector<double>(m_numberField, 0.0);
            m_unlikelihood = std::vector<double>(m_numberField, 0.0);
            m_isFixedPhone = std::regex(R"(^(0|\\+33)([1-5]|9)[0-9]{8}$)");
            m_isMobilePhone = std::regex(R"(^(0|\\+33)(6|7)[0-9]{8}$)");
        }

        void DetectPhone::buildLikelihood(const std::vector<bool> &toCheck)
        {
            size_t size = 0;
            std::string word;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                if (toCheck[indexField])
                {
                    size = m_dataAnalysis.getSize(indexField);
                    for (size_t index = 0; index < size; ++index)
                    {
                        word = m_dataAnalysis.get(indexField, index);
                        if (std::regex_match(word, m_isFixedPhone))
                        {
                            m_likelihoodFixed[indexField]++;
                        }
                        else if (std::regex_match(word, m_isMobilePhone))
                        {
                            m_likelihoodMobile[indexField]++;
                        }
                        else
                        {
                            m_unlikelihood[indexField]++;
                        }
                    }
                }
                if (size > 0)
                {
                    m_likelihoodFixed[indexField] /= (double)size;
                    m_likelihoodMobile[indexField] /= (double)size;
                    m_unlikelihood[indexField] /= (double)size;
                }
            }
        }

        void DetectPhone::decisionPhone(std::vector<smartDescriptor::DescriptorField> &descriptor,
                                        std::vector<bool> &toCheck)
        {
            std::vector<size_t> indexFields;
            std::vector<FieldFlags> fields;

            FieldFlags fieldFlags;
            buildLikelihood(toCheck);
            size_t indexField = 0;
            chooseFields(fields, indexFields);
            for (unsigned long index : indexFields)
            {
                indexField = index;
                fieldFlags = fields[indexField];
                smartDescriptor::DescriptorField descriptorPhone(indexField, fieldFlags);
                if (fieldFlags == PHONE)
                {
                    descriptorPhone.likelihood = m_likelihoodMobile[indexField] + m_likelihoodFixed[indexField];
                }
                else if (fieldFlags == PHONE_FIX)
                {
                    descriptorPhone.likelihood = m_likelihoodFixed[indexField];
                }
                else
                {
                    descriptorPhone.likelihood = m_likelihoodMobile[indexField];
                }
                toCheck[indexField] = false;
                descriptor.push_back(descriptorPhone);
            }

        }

        void DetectPhone::chooseFields(std::vector<FieldFlags> &fields, std::vector<size_t> &indexFields)
        {
            double consistency = 1.0;
            while (consistency >= m_threshold && indexFields.empty())
            {
                for (size_t indexField = 0; indexField < m_numberField; ++indexField)
                {
                    if (m_likelihoodMobile[indexField] + m_likelihoodFixed[indexField] > consistency)
                    {
                        indexFields.push_back(indexField);
                        if (m_likelihoodFixed[indexField] == 0.0)
                        {
                            fields.push_back(PHONE_MOB);
                        }
                        else if (m_likelihoodMobile[indexField] == 0.0)
                        {
                            fields.push_back(PHONE_FIX);
                        }
                        else
                        {
                            fields.push_back(PHONE);
                        }
                    }
                }
                consistency -= 0.01;
            }
        }

        void DetectPhone::getStatistics(std::string &statistics)
        {
            statistics = "----------- Statistics detection phones ----------\n";
            std::string statisticsInstance = "|  index | stats fixed phone | stats mobile phone|\n";
            boost::format format("|   %2d   |       %.2f        |       %.2f        |\n");
            size_t index;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                index = indexField + 1;
                if (m_likelihoodMobile[indexField] > 0.0 || m_likelihoodFixed[indexField] > 0.0)
                {
                    format % index % m_likelihoodFixed[indexField] % m_likelihoodMobile[indexField];
                    statisticsInstance += format.str();
                }
            }
            if (!statisticsInstance.empty())
            {
                statistics += statisticsInstance;
            }
            else
            {
                statistics += "Phone no Found";
            }
        }
    }
}