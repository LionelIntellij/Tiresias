#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "SearchHeader.h"
#include "DataAnalysis.h"
#include "ReaderCsv.h"
#include "BuildBuffer.h"
#include "module.h"


BOOST_AUTO_TEST_SUITE(test_SearchHeader)

    BOOST_AUTO_TEST_CASE(test_SearchHeader_has_header)
    {

        size_t minimumLine = 5;
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = ';';
        paramFile.numberField = 15;
        paramFile.numberLine = 10;
        double threshold = 0.9;

        smartDescriptor::buffer::BuildBuffer buildBuffer(minimumLine, paramFile);
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::buffer::DataAnalysis dataAnalysis(buildBuffer.getDataAnalysis(fileParameters));
        smartDescriptor::header::Header header(buildBuffer.getHeader());
        smartDescriptor::header::SearchHeader searchHeader(threshold, header, dataAnalysis);
        BOOST_CHECK_EQUAL(searchHeader.hasHeader(), true);
    }


    BOOST_AUTO_TEST_CASE(test_SearchHeader_has_not_header)
    {

        size_t minimumLine = 10;
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = ';';
        paramFile.numberField = 15;
        paramFile.numberLine = 10;
        double threshold = 0.9;

        smartDescriptor::buffer::BuildBuffer buildBuffer(minimumLine, paramFile);
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::buffer::DataAnalysis dataAnalysis(buildBuffer.getDataAnalysis(fileParameters));
        std::vector<std::string> head(paramFile.numberField);
        for (size_t indexField = 0; indexField < paramFile.numberField; ++indexField)
        {
            if (dataAnalysis.getSize(indexField) > 0)
            {
                head[indexField] = dataAnalysis.getEnd(indexField);
            }
            else
            {
                head[indexField] = "test";
            }
        }
        smartDescriptor::header::Header header(head);
        smartDescriptor::header::SearchHeader searchHeader(threshold, header, dataAnalysis);
        BOOST_CHECK_EQUAL(searchHeader.hasHeader(), false);
    }

BOOST_AUTO_TEST_SUITE_END()