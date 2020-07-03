#include "EncodingAnalysis.h"

namespace smartDescriptor
{
    namespace encoding
    {

        EncodingAnalysis::EncodingAnalysis(const size_t numberField, const size_t numberLine) : m_numberField(numberField)
        {
            smartDescriptor::buffer::Column<Bytes> column(numberLine);
            m_data = std::vector<smartDescriptor::buffer::Column<Bytes>>(numberField, column);
        }

        void EncodingAnalysis::fill(size_t indexField, size_t indexLine, size_t indexSpecial, size_t sizeSpecial,
                                    const Bytes &bytes)
        {
            m_data[indexField].fill(bytes, indexLine);
            m_index[indexField].fill(indexSpecial, sizeSpecial);
        }


    }
}