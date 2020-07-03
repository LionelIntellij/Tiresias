#include "Column.h"
#include <vector>


namespace smartDescriptor
{
    namespace encoding
    {
        typedef std::vector<unsigned char> Bytes;

        class EncodingAnalysis
        {
        public:
            EncodingAnalysis(size_t numberField, size_t numberLine);

            void fill(size_t indexField, size_t indexLine,
                      size_t  indexSpecial, size_t sizeSpecial ,const Bytes &bytes);


        private:
            std::vector<smartDescriptor::buffer::Column<Bytes>> m_data;
            std::vector<smartDescriptor::buffer::Column<size_t>> m_index;
            size_t m_numberField;
        };
    }
}