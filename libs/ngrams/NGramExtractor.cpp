#include "ExtractedNGrams.h"
#include "NGramExtractor.h"
#include <iostream>

namespace smartDescriptor
{
    namespace nGrams
    {

        void NGramExtractor::extractLetters(const std::string &text, std::vector<std::string> &alphabeticWords)
        {
            std::string isAlphabetic;
            for (const char &character :text)
            {
                if (std::isalpha(character))
                {
                    isAlphabetic.push_back(character);
                }
                else
                {
                    if (!isAlphabetic.empty())
                    {
                        alphabeticWords.push_back(isAlphabetic);
                    }
                    isAlphabetic.clear();
                }
            }
        }

        void NGramExtractor::getGrams(const std::string &word)
        {
            std::string::const_iterator iteratorStart = word.begin();
            std::string::const_iterator iteratorEnd = iteratorStart + m_numberGrams;
            while (iteratorEnd != word.end() + 1)
            {
                m_grams.emplace_back(iteratorStart, iteratorEnd);
                iteratorStart++;
                iteratorEnd++;
            }
        }

        void NGramExtractor::extract(const std::string &text)
        {
            std::vector<std::string> alphabeticWords;
            extractLetters(text, alphabeticWords);
            for (const std::string &word :alphabeticWords)
            {
                if (word.size() > m_numberGrams)
                {
                    getGrams(word);
                }
            }
        }

        ExtractedNGrams NGramExtractor::getExtractedNGrams()
        {
            ExtractedNGrams extractedNGrams(m_grams);
            return extractedNGrams;
        }
    }
}