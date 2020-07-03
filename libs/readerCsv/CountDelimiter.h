#include <unordered_map>
#include <string>

namespace smartDescriptor {


    namespace readerCsv {

        struct StatisticsDelimiter {
            StatisticsDelimiter &operator=(const StatisticsDelimiter & statisticsDelimiter)= default;

            StatisticsDelimiter():instanceDelimiter(0),
                                  instanceLine(0){}

            size_t instanceDelimiter;
            int instanceLine;
            std::string delimiter;
        };


        class CountDelimiter {

        public:

            explicit CountDelimiter(const std::string &delimiter);

            inline void increment() {
                m_instanceDelimiter++;
                m_betweenQuote++;
            }

            inline void initializeQuote() {
                m_betweenQuote = 0;
            }

            inline void updateQuote() {
                m_instanceDelimiter -= m_betweenQuote;
                m_betweenQuote = 0;
            }

            void updateInstance();

            void getStatisticsDelimiter(StatisticsDelimiter &statisticsDelimiter);

            void getStatistics(std::string &statistics);


        private :
            std::string m_delimiter;
            size_t m_instanceDelimiter;
            int m_betweenQuote;
            std::unordered_map<size_t , int> m_instance;
        };
    }
}