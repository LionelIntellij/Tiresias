#ifndef HEADER_CLASSIFIER_H
#define HEADER_CLASSIFIER_H

#include <string>
#include "Utils.h"
#include <vector>
#include <unordered_map>
#include <Header.h>

namespace smartDescriptor {
    namespace header {
        class Classifier {


        public:
            explicit Classifier(const FieldFlags field);

            void fill(const std::string &field);

            void match(Header &header);

            FieldFlags getField();

            const std::vector<size_t> &getPosition();

        private:
            FieldFlags m_field;
            std::unordered_map<std::string, int> m_classifier;
            std::vector<size_t> m_position;
        };
    }
}

#endif