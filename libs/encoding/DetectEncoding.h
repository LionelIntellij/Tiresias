#include "Column.h"
#include <vector>

typedef std::vector<unsigned char>  bytes;

namespace smartDescriptor{
    namespace encoding{
     class EncodingAnalysis{
     public:

         EncodingAnalysis(const size_t numberField){

         };

         void fill(const size_t indexField ,size_t flags);

         void get(const size_t indexField);

     private:
         //std::vector<Column<std::string>> data;

         std::vector<bytes> m_data;

     };

    }
}