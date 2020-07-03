#ifndef ANALYSIS_DETECT_ZIPCODE_H
#define ANALYSIS_DETECT_ZIPCODE_H
#include <regex>
#include "Utils.h"
#include "Params.h"
#include "DataAnalysis.h"
#include "Descriptor.h"


namespace smartDescriptor {
    namespace detection {

        struct FeaturesZipCode {
            explicit FeaturesZipCode(size_t indexField);
            size_t indexField;
            int hasDifferentDigit;
            int hasDifferentZip;
            int hasOtherWord;
            int endByNull;
        };

        class DetectZipCode {
        public:
            explicit DetectZipCode(double threshold, const buffer::DataAnalysis &dataAnalysis);

            void decisionZipCode(std::vector<smartDescriptor::DescriptorField> &descriptor, std::vector<bool> &toCheck);

            void getStatistics(std::string &statistics);

        private:
            //attributs
            double m_threshold;
            buffer::DataAnalysis m_dataAnalysis;
            size_t m_numberField;
            std::vector<double> m_unlikelihood;
            std::vector<double> m_likelihood;
            std::regex m_isZipCode;

            //methods
            void chooseField(const std::vector<size_t> &checkIndex, std::vector<size_t> &indexFields);

            void computeLikelihood(const std::vector<FeaturesZipCode> &featuresZipCode);

            void setFeatures(const std::vector<size_t> &position, std::vector<FeaturesZipCode> &features);

            void buildLikelihood(const std::vector<bool> &toCheck, std::vector<size_t> &indexFields);

            int hasDifferentDigit(std::string::const_iterator begin, std::string::const_iterator end);

            void hasZipCode(std::vector<std::string>::const_iterator begin,
                            std::vector<std::string>::const_iterator end,
                            std::string &zipCode);
        };
    }
}

#endif