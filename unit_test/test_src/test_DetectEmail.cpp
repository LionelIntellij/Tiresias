#include "DataAnalysis.h"
#include <vector>
#include "BuildBuffer.h"
#include <iostream>
#include "module.h"
#include "DetectEmail.h"

BOOST_AUTO_TEST_SUITE(test_DetectEmail)

    BOOST_AUTO_TEST_CASE(test_DetectEmail_true)
    {
        double threshold = 0.8;
        size_t minimumLine = 100;
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = '\t';
        paramFile.numberField = 12;
        paramFile.numberLine = 10;
        smartDescriptor::buffer::BuildBuffer buildBuffer(minimumLine, paramFile);
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + "1.csv");
        smartDescriptor::buffer::DataAnalysis dataAnalysis(buildBuffer.getDataAnalysis(fileParameters));
        smartDescriptor::detection::DetectEmail detectEmail(threshold, dataAnalysis);
        std::vector<smartDescriptor::DescriptorField> descriptor;
        std::vector<bool> toCheck;
        toCheck = std::vector<bool>(paramFile.numberField, true);
        detectEmail.decisionEmail(descriptor,toCheck);
        BOOST_CHECK_EQUAL(descriptor.size(),1);
        BOOST_CHECK_EQUAL(descriptor[0].position,8);
    }
BOOST_AUTO_TEST_SUITE_END()