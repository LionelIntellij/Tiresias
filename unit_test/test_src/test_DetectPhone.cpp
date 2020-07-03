#include "DataAnalysis.h"
#include <vector>
#include "BuildBuffer.h"
#include <iostream>
#include "module.h"
#include "DetectPhone.h"

BOOST_AUTO_TEST_SUITE(test_DetectPhone)

    BOOST_AUTO_TEST_CASE(test_DetectPhone_true)
    {
        double threshold = 0.8;
        size_t minimumLine = 100;
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = ';';
        paramFile.numberField = 15;
        paramFile.numberLine = 10;
        smartDescriptor::buffer::BuildBuffer buildBuffer(minimumLine, paramFile);
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::buffer::DataAnalysis dataAnalysis(buildBuffer.getDataAnalysis(fileParameters));
        smartDescriptor::detection::DetectPhone detectPhone(threshold, dataAnalysis);
        std::vector<smartDescriptor::DescriptorField> descriptor;
        std::vector<bool> toCheck;
        toCheck = std::vector<bool>(paramFile.numberField, true);
        detectPhone.decisionPhone(descriptor,toCheck);
        std::string statistics ;
        BOOST_CHECK_EQUAL(descriptor.size() ,1);
        BOOST_CHECK_EQUAL(descriptor[0].position ,12);
    }

BOOST_AUTO_TEST_SUITE_END()