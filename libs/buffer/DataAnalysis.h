#ifndef BUFFER_DATA_ANALYSIS_H
#define BUFFER_DATA_ANALYSIS_H

#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include "Column.h"
#include "ExtractedNGrams.h"

namespace smartDescriptor
{
    namespace buffer
    {
        struct Connect
        {
            Connect(size_t indexField, size_t index) : indexField(indexField), index(index) {}
            size_t indexField;
            size_t index;
        };

        class DataAnalysis
        {
            public:
            DataAnalysis(size_t numberField, size_t numberLine);

            void updateFieldSize(size_t indexField, size_t size);

            void fillBuffer(size_t indexField, size_t index,  const std::string &field);

            void setConnection();

            const std::string get(size_t indexField, size_t index) const ;

            const std::string &getEnd( size_t indexField) const;

            size_t getNumberField() const
            {
                return m_numberField;
            }

            size_t getSize( size_t indexField)const;

            size_t getMaxFieldSize( size_t indexField);

            void getSplitBlank( size_t indexField,  size_t index, std::vector<std::string> &words);

            const std::vector<Connect> &getConnection( size_t flags);

            void  getFlagsConnection(std::vector<size_t> & flagsConnection );

            private:
            size_t m_numberField;
            std::vector<Column<std::string>> m_buffer;
            std::vector<size_t> m_maxSizeField;
            std::vector<smartDescriptor::nGrams::ExtractedNGrams> m_nGrams;
            std::unordered_map<size_t, std::vector<Connect>> m_connections;

            //Methods
            void isInDomain( size_t indexField) const;
        };
    }
}

#endif