#include <AnalysisHeader.h>

namespace smartDescriptor
{
    namespace header
    {

        Header::Header(const std::vector<std::string> &headers) : m_header(headers)
        {
            std::string digitType;
            std::string lettersType;
            size_t size = headers.size();
            m_digit = std::vector<long int>(size,0);
            m_letters = std::vector<std::string>(size);
            for (size_t indexField = 0; indexField < size; ++indexField)
            {
                setHeader(m_header[indexField],digitType,lettersType);
                if (!lettersType.empty())
                {
                    m_letters[indexField] = lettersType;
                }
                if (!digitType.empty())
                {
                    m_digit[indexField] = std::stol(digitType);
                }
                digitType.clear();
                lettersType.clear();
            }
        }

        void Header::setHeader(const std::string &word, std::string &digitType, std::string &lettersType)
        {
            std::locale loc;
            lettersType.clear();
            digitType.clear();
            for (auto character : word)
            {
                if (isdigit(character))
                {
                    digitType.push_back(character);
                }
                if (isalpha(character))
                {
                    lettersType.push_back(std::tolower(character, loc));
                }
            }
        }

        long int Header::getDigit(const size_t indexField)
        {
            return m_digit[indexField];
        }

        const std::string &Header::getField(const size_t indexField)
        {
            return m_letters[indexField];
        }

        size_t Header::getSize()
        {
            return m_header.size();
        }

        const std::string &Header::get(const size_t indexField)
        {
            return m_header[indexField];
        }
    }
}