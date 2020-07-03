#ifndef ANALYSIS_DETECT_PHONE_H
#define ANALYSIS_DETECT_PHONE_H

#include <vector>
#include <string>
#include "regex"
#include "DataAnalysis.h"
#include "Utils.h"
#include "Descriptor.h"

namespace smartDescriptor {
    namespace detection {

        class DetectPhone {
        public:

            explicit DetectPhone( double threshold, const buffer::DataAnalysis &dataAnalysis);

            void decisionPhone(std::vector<smartDescriptor::DescriptorField> &descriptor, std::vector<bool> &toCheck);

            void getStatistics(std::string &statictics);


        private:

            //attributs
            buffer::DataAnalysis m_dataAnalysis;
            double m_threshold;
            size_t m_numberField;
            std::regex m_isFixedPhone;
            std::regex m_isMobilePhone;
            std::vector<double> m_likelihoodMobile;
            std::vector<double> m_likelihoodFixed;
            std::vector<double> m_unlikelihood;


            //methods

            void buildLikelihood(const std::vector<bool> &toCheck);

            void chooseFields(std::vector<FieldFlags> &fields, std::vector<size_t> &indexFields);
        };
    }
}

#endif