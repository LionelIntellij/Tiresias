#ifndef BUFFER_COLUMN_H
#define BUFFER_COLUMN_H

#include <string>
#include <deque>
#include <iostream>


namespace smartDescriptor
{
    namespace buffer
    {
        template<class Type>
        class Column
        {
        private:
            size_t m_numberMaxElement;
            size_t m_numberElement;
            std::deque<Type> m_data;
            std::deque<size_t> m_index;

            //Methods
            void isInDomain(const size_t index) const;

        public:
            Column(const size_t numberMaxElement) : m_numberMaxElement(numberMaxElement), m_numberElement(0)
            {
            }

            void fill(const Type &field, const size_t index);

            void popFront();

            void popBack();

            const Type &get(const size_t index) const;

            size_t getFlags(const size_t index);

            const Type &getEnd() const;

            size_t getSize() const
            {
                return m_numberElement;
            }
        };

#include "Column.tpp"

}}
#endif

