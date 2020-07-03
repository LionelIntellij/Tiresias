#include "AnalysisDelimiter.h"
#include <iostream>
#include <unordered_map>

namespace smartDescriptor
{
    namespace readerCsv
    {
        AnalysisDelimiter::AnalysisDelimiter(const ParamsDelimiter &paramsDelimiter) : m_threshold(
                paramsDelimiter.threshold), m_numberLine(0)
        {

            for (const std::string &delimiter : paramsDelimiter.delimiters)
            {
                if (delimiterBytes.find(delimiter) != delimiterBytes.end())
                {
                    CountDelimiter statistic(delimiter);
                    m_statistics.insert(std::make_pair(delimiterBytes.at(delimiter), statistic));
                }
                else
                {
                    std::cerr << "unknown delimiter" << std::endl;
                    throw;
                }
            }
        }


        void AnalysisDelimiter::computeStatistics(const size_t size,const  unsigned char *buffer)
        {
            unsigned char character;
            bool quote = false;
            for (size_t index = 0; index < size; ++index)
            {
                character = buffer[index];
                if (character == 0x22)
                {
                    if (quote)
                    {
                        quote = false;
                        for (auto &statistic : m_statistics)
                        {
                            statistic.second.updateQuote();
                        }
                    }
                    else
                    {
                        quote = true;
                        for (auto &statistic : m_statistics)
                        {
                            statistic.second.initializeQuote();
                        }
                    }
                }
                if (m_statistics.find(character) != m_statistics.end())
                {
                    m_statistics.at(character).increment();
                }
                if (character == 0x0a || index == size - 1)
                {
                    for (auto &statistic : m_statistics)
                    {
                        statistic.second.updateInstance();
                    }
                    m_numberLine++;
                }
            }
        }


        void AnalysisDelimiter::analysisStatistics()
        {
            StatisticsDelimiter statisticsDelimiter;
            for (auto &instance : m_statistics)
            {
                StatisticsDelimiter statistic;
                instance.second.getStatisticsDelimiter(statistic);
                if (statistic.instanceLine != 0 && statistic.instanceDelimiter != 0)
                {
                    m_statisticsResult.push_back(statistic);
                }
            }
        }


        size_t AnalysisDelimiter::getResult(std::vector<StatisticsDelimiter> &statisticsResult)
        {
            size_t statDelimiterSize = 0;
            double consistency = 0.9;
            while ((statDelimiterSize == 0) && (consistency >= m_threshold))
            {
                for (const StatisticsDelimiter &statistic : m_statisticsResult)
                {
                    if ((float) statistic.instanceLine / m_numberLine > consistency)
                    {
                        statisticsResult.push_back(statistic);
                        statDelimiterSize++;
                    }
                }
                consistency -= 0.01;
            }
            return statDelimiterSize;
        }


        void AnalysisDelimiter::setDelimiter(StatisticsDelimiter &result)
        {
            analysisStatistics();
            std::vector<StatisticsDelimiter> statisticsDelimiters;
            size_t statDelimiterSize = getResult(statisticsDelimiters);
            if (statDelimiterSize == 0)
            {
                std::string statistics;
                getStatistics(statistics);
                std::cerr << statistics << std::endl;
                throw std::runtime_error("delimiters not found");
            }
            else
            {

                for (const StatisticsDelimiter &statisticsResult : m_statisticsResult)
                {
                    if (statisticsResult.instanceLine > result.instanceLine ||
                        (statisticsResult.instanceLine == result.instanceLine &&
                         statisticsResult.instanceDelimiter > result.instanceDelimiter))
                    {
                        result = statisticsResult;
                    }
                }
            }
        }


        void AnalysisDelimiter::getStatistics(std::string &statistics)
        {
            if (!m_statisticsResult.empty())
            {
                statistics = "------------ statistics delimiters --------------\n";
                statistics += "delimiter : probability\n";
                for (const StatisticsDelimiter &statDelimiter : m_statisticsResult)
                {
                    statistics += " \" " + statDelimiter.delimiter + " \" : " +
                                  std::to_string(statDelimiter.instanceLine / (double) m_numberLine) + "\n";
                }
            }
            else
            {
                std::cerr << "delimiters not found" << std::endl;
            }
            statistics += "delimiter : [instance delimiter : number line ]\n";

            for (auto &statisticsDelimiter : m_statistics)
            {
                statisticsDelimiter.second.getStatistics(statistics);
            }
        }
    }
}