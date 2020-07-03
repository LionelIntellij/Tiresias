#include <iostream>
#include "DataAnalysis.h"
#include "Column.h"

namespace smartDescriptor
{
    namespace buffer
    {
        DataAnalysis::DataAnalysis(const size_t numberField, const size_t numberLine) : m_numberField(numberField)
        {
            Column<std::string> column(numberLine);
            m_buffer = std::vector<Column<std::string>>(m_numberField, column);
            m_maxSizeField = std::vector<size_t>(numberField, 0);
        }

        void DataAnalysis::updateFieldSize(const size_t indexField, const size_t size)
        {
            isInDomain(indexField);
            if (m_maxSizeField[indexField] < size)
            {
                m_maxSizeField[indexField] = size;
            }
        }

        size_t DataAnalysis::getSize(size_t indexField)const
        {
            isInDomain(indexField);
            return m_buffer[indexField].getSize();
        }

        const std::string DataAnalysis::get(const size_t indexField, const size_t index) const
        {
            isInDomain(indexField);
            return m_buffer[indexField].get(index);
        };

        const std::string &DataAnalysis::getEnd(const size_t indexField) const
        {
            isInDomain(indexField);
            return m_buffer[indexField].getEnd();
        }

        size_t DataAnalysis::getMaxFieldSize(const size_t indexField)
        {
            isInDomain(indexField);
            return m_maxSizeField[indexField];
        }


        void DataAnalysis::fillBuffer(const size_t indexField, const size_t flags, const std::string &field)
        {
            isInDomain(indexField);
            std::string word;
            if (field.size() > 2)
            {
                std::string::const_iterator iteratorCharacter = field.begin() + 1;
                word.push_back(static_cast<char>(*field.begin()));
                while (iteratorCharacter + 1 != field.end())
                {
                    if (!(std::isspace(*iteratorCharacter) && std::isdigit(*(iteratorCharacter - 1)) &&
                          std::isdigit(*(iteratorCharacter + 1))))
                    {
                        word.push_back(static_cast<char>(std::tolower(*iteratorCharacter)));
                    }
                    iteratorCharacter++;
                }
                word.push_back(static_cast<char>(std::tolower(*iteratorCharacter)));
            }
            else
            {
                for(const char character : field )
                {
                    word.push_back(static_cast<char>(std::tolower(character)));
                }
            }
            m_buffer[indexField].fill(word, flags);
        }

        void DataAnalysis::isInDomain(const size_t indexField) const
        {
            if (indexField > m_numberField)
            {
                std::cerr << "index : " << indexField << " field number : " << m_numberField << std::endl;
                throw std::range_error("index out in range");
            }
        }

        void DataAnalysis::setConnection()
        {
            size_t indexLine;
            for (size_t indexField = 0; indexField < m_numberField; ++indexField)
            {
                size_t numberLine = m_buffer[indexField].getSize();
                for (size_t index = 0; index < numberLine; ++index)
                {
                    indexLine = m_buffer[indexField].getFlags(index);
                    if (m_connections.find(indexLine) != m_connections.end())
                    {
                        Connect connect(indexField, index);
                        m_connections.at(indexLine).push_back(connect);
                    }
                    else
                    {
                        Connect connect(index, indexField);
                        std::vector<Connect> Connection;
                        Connection.push_back(connect);
                        m_connections.insert(std::make_pair(indexLine, Connection));
                    }
                }
            }
        }

        void DataAnalysis::getSplitBlank(const size_t indexField, const size_t index, std::vector<std::string> &words)
        {
            isInDomain(indexField);
            words.clear();
            std::string word;
            for (const char &character : m_buffer[indexField].get(index))
            {
                if (isblank(character))
                {
                    if (!word.empty())
                    {
                        words.push_back(word);
                    }
                    word.clear();
                }
                else
                {
                    word.push_back(character);
                }
            }
            if (!word.empty())
            {
                words.push_back(word);
            }
        }


        const std::vector<Connect> &DataAnalysis::getConnection(const size_t flags)
        {
            if ((m_connections.find(flags) == m_connections.end()))
            {
                throw std::out_of_range("flags is unknown");
            }
            else
            {
                return m_connections.at(flags);
            }
        }

        void DataAnalysis::getFlagsConnection(std::vector<size_t> &flagsConnection)
        {
            for (const auto &connection :m_connections)
            {
                flagsConnection.push_back(connection.first);
            }
        }

        /*
        void DataAnalysis::extractGrams()
        {

        }*/

    }
}