#include "Column.h"
#include <exception>

template<class Type>
void Column<Type>::fill(const Type &field, const size_t index) {
    if (m_numberElement > m_numberMaxElement) {
        m_data.pop_front();
    } else {
        m_numberElement++;
    }
    m_data.push_back(field);
    m_index.push_back(index);
}

template<class Type>
void Column<Type>::popFront() {
    if (m_data.empty()) {
        throw std::out_of_range("empty stack");
    }
    m_index.pop_front();
    m_data.pop_front();
    m_numberElement--;
}

template<class Type>
void Column<Type>::popBack() {
    if (m_data.empty()) {
        throw std::out_of_range("empty stack");
    }
    m_index.pop_back();
    m_data.pop_back();
    m_numberElement--;
}

template<class Type>
const Type &Column<Type>::get(const size_t index) const {
    isInDomain(index);
    return m_data[index];
}

template<class Type>
const Type &Column<Type>::getEnd() const {
    if (m_data.empty()) {
        throw std::out_of_range("empty stack");
    }
    return *(m_data.end() - 1);
}

template<class Type>
size_t Column<Type>::getFlags(const size_t index){
    isInDomain(index);
    return m_index[index];
}

template<class Type>
void Column<Type>::isInDomain(const size_t index) const {
    {
        if (index > m_numberElement) {
            std::cerr << "index : " << index << " max element : " << m_numberElement << std::endl;
            throw std::range_error("index out in range");
        }
    }
}
