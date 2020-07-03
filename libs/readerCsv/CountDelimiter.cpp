#include "CountDelimiter.h"

namespace smartDescriptor {
    namespace readerCsv {
        void CountDelimiter::updateInstance() {
            if (m_instance.find(m_instanceDelimiter) != m_instance.end()) {
                m_instance.at(m_instanceDelimiter)++;
            } else {
                m_instance.insert(std::make_pair(m_instanceDelimiter, 1));
            }
            m_instanceDelimiter = 0;
        }


        void CountDelimiter::getStatisticsDelimiter(StatisticsDelimiter &statisticsDelimiter) {
            int sumInstanceLine = 0;
            int instanceLine = 0;
            size_t instanceDelimiter = 0;

            for (const auto &instance :m_instance) {
                sumInstanceLine += instance.second;
                if (instance.second > instanceLine) {
                    instanceLine = instance.second;
                    instanceDelimiter = instance.first;
                }
            }
            statisticsDelimiter.delimiter = m_delimiter;
            statisticsDelimiter.instanceDelimiter = instanceDelimiter;
            statisticsDelimiter.instanceLine = 2 * instanceLine - sumInstanceLine;
        }

        void CountDelimiter::getStatistics(std::string &statistics) {
            statistics += "\" " + m_delimiter + " \" : ";
            for (auto instance : m_instance) {
                statistics += "[ " + std::to_string(instance.first) + " : " + std::to_string(instance.second) + "  ] ";
            }
            statistics += "\n";
        }

        CountDelimiter::CountDelimiter(const std::string &delimiter) : m_delimiter(delimiter),
                                                                 m_instanceDelimiter(0),
                                                                 m_betweenQuote(0) {}
    }
}