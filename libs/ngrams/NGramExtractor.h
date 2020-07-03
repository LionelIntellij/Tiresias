#ifndef NGRAM_EXTRACTOR_H
#define NGRAM_EXTRACTOR_H

#include <string>
#include <vector>
#include "ExtractedNGrams.h"

namespace smartDescriptor {
    namespace nGrams {

        class NGramExtractor {
        private:
            //attribute
            const unsigned int m_numberGrams;
            std::vector<std::string> m_grams;

            //methods
            void extractLetters(const std::string &text,  std::vector<std::string> & alphabeticsWords);
            void getGrams(const std::string & word);

        public:
            explicit NGramExtractor(const unsigned int numberGrams) : m_numberGrams(numberGrams) {}

            void extract(const std::string &text);

            ExtractedNGrams getExtractedNGrams();

        };
    }
}
#endif