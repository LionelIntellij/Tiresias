#ifndef ANALYSIS_DETECT_NAME_H
#define ANALYSIS_DETECT_NAME_H

#include <vector>
#include <string>
#include "regex"
#include "DataAnalysis.h"
#include "Utils.h"
#include "Descriptor.h"

namespace smartDescriptor
{
    namespace detection
    {

        class DetectName
        {
        public:

            explicit DetectName( double threshold, const buffer::DataAnalysis &dataAnalysis);

            void decisionName(std::vector<smartDescriptor::DescriptorField> &descriptor, std::vector<bool> &toCheck);

            void getStatistic(std::string & statistics);

        private:


        };
    }
}