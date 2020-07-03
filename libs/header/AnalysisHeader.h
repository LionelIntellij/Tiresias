#ifndef HEADER_ANALYSIS_HEADER_H
#define HEADER_ANALYSIS_HEADER_H


#include "Header.h"
#include "Classifier.h"

namespace smartDescriptor {
    namespace header {

        struct DescriptorHeader {
            DescriptorHeader(FieldFlags field, size_t position, int instance = 0) :
                    field(field), position(position), instance(instance) {}

            FieldFlags field;
            size_t position;
            int instance;
        };

        class AnalysisHeader {

        public:
            AnalysisHeader(const Header &header, const std::vector<FieldFlags> &fieldsFlags);

            void decisionHeader(std::vector<DescriptorHeader> &descriptor);

            const std::vector<FieldFlags> &getFieldNoFound();

            void getStatistics(std::string &statistics);

        private:
            //attribut
            Header m_header;
            size_t m_numberField;
            std::vector<Classifier> m_classifierHeader;
            std::vector<FieldFlags> m_fieldNoFound;
            std::vector<DescriptorHeader> m_descriptor;

            //methods
            void multiField(Classifier &classifier, std::vector<DescriptorHeader> &descriptor);

            void affectFieldDigit(FieldFlags fieldFlags,
                                  const std::vector<size_t> &HasDigit,
                                  int numberField, std::vector<DescriptorHeader> &descriptor);

        };
    }
}
#endif // ANALYSE_HEADER_H
