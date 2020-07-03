#ifndef HEADER_HEADER_H
#define HEADER_HEADER_H

#include <string>
#include <vector>

namespace smartDescriptor {
    namespace header {
        class Header {

        public:
            explicit Header(const std::vector<std::string> &header);

            long int getDigit(size_t indexField);

            const std::string &getField(size_t indexField);

            size_t getSize();

            const std::string &get(size_t indexField);

        private:
            std::vector<std::string> m_header;
            std::vector<long int> m_digit;
            std::vector<std::string> m_letters;

            //methods
            void setHeader(const std::string & word , std::string & digitType , std::string & lettersType);
        };
    }
}
#endif