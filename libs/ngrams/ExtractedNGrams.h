#ifndef EXTRACTED_NGRAMS_H
#define EXTRACTED_NGRAMS_H
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>

namespace smartDescriptor {
    namespace nGrams {

        class NormalDist {
        private:
            std::default_random_engine m_generator;
            std::normal_distribution<double> m_distribution;
        public:
            NormalDist(double mean, double stdev): m_distribution(mean, stdev){}
            double get() {
                return m_distribution(m_generator);
            }
        };

        class UniformIntDist {
        private:
            std::default_random_engine m_generator;
            std::uniform_int_distribution<size_t> m_distribution;
        public:
            UniformIntDist(size_t startPosition, size_t endPosition): m_distribution(startPosition, endPosition){}
            size_t get() {
                return m_distribution(m_generator);
            }
        };

        class ExtractedNGrams {
            std::vector<std::string> m_grams;
            UniformIntDist m_gramsDist;
        public:
            ExtractedNGrams(const std::vector<std::string> &grams) : m_grams(grams),
                m_gramsDist(0, m_grams.size() - 1){}

            std::string randomGram() {
                return m_grams[m_gramsDist.get()];
            }
        };
    }
}
#endif