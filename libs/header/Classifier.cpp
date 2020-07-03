#include  "Classifier.h"

namespace smartDescriptor {
    namespace header {

        Classifier::Classifier(const FieldFlags field) : m_field(field) {

        }

        void Classifier::fill(const std::string &field) {
            if (m_classifier.find(field) == m_classifier.end()) {
                m_classifier.insert(std::make_pair(field, 0));
            }
        }

        void Classifier::match(Header &header) {
            m_position.clear();
            for (size_t indexField = 0; indexField < header.getSize(); ++indexField) {
                if (m_classifier.find(header.getField(indexField)) != m_classifier.end()) {
                    m_position.push_back(indexField);
                }
            }
        }

        FieldFlags Classifier::getField() {
            return m_field;
        }

        const std::vector<size_t> &Classifier::getPosition() {
            return m_position;
        }

    }
}