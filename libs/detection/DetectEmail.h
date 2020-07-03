#ifndef ANALYSIS_DETECT_EMAIL_H
#define ANALYSIS_DETECT_EMAIL_H

#include <string>
#include <vector>
#include <string>
#include <regex>
#include "DataAnalysis.h"
#include "Utils.h"
#include "Descriptor.h"



namespace smartDescriptor {
    namespace detection {
        class DetectEmail {

        public:
            DetectEmail(double threshold, const buffer::DataAnalysis &dataAnalysis);

            void decisionEmail(std::vector<smartDescriptor::DescriptorField> &descriptor, std::vector<bool> &toCheck);

            void getStatistics(std::string & statistics);
        private:

            //attributes
            double m_threshold;
            buffer::DataAnalysis m_dataAnalysis;
            size_t m_numberField;
            std::vector<double> m_likelihood;
            std::vector<double> m_unlikelihood;
            std::regex m_isEmail;

            //methods
            void buildLikelihood(const std::vector<bool> &toCheck);

            void chooseEmail(const std::vector<bool> &toCheck, std::vector<size_t> &indexFields);
        };
    }
}

#endif