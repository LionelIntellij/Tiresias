#include "DataAnalysis.h"
#include <vector>
#include <boost/test/unit_test.hpp>
#include <iostream>


BOOST_AUTO_TEST_SUITE(test_DataAnalysis)

    BOOST_AUTO_TEST_CASE(test_DataAnalysis_fill)
    {
        size_t numberMaxElement = 5;
        size_t numberField = 2;
        std::vector<std::vector<std::string>> bufferName = {{"lionel",  "mohamed", "jean",   "lilia", "william",},
                                                            {"Lacroix", "mohamed", "Belico", "Kodja"}};
        smartDescriptor::buffer::DataAnalysis dataAnalysis(numberField, numberMaxElement);
        for (size_t indexField = 0; indexField < numberField; ++indexField)
        {
            for (size_t index = 0; index < bufferName[indexField].size(); ++index)
            {
                dataAnalysis.fillBuffer(indexField, index, bufferName[indexField][index]);
            }
        }
        BOOST_CHECK_EQUAL(dataAnalysis.get(0, 0), bufferName[0][0]);
        BOOST_CHECK_EQUAL(dataAnalysis.get(1, 0), bufferName[1][0]);
        BOOST_CHECK_EQUAL(dataAnalysis.getSize(0), bufferName[0].size());
        BOOST_CHECK_EQUAL(dataAnalysis.getSize(1), bufferName[1].size());
        BOOST_CHECK_EQUAL(dataAnalysis.getNumberField(), numberField);
    }

    BOOST_AUTO_TEST_CASE(test_DataAnalysis_split)
    {
        size_t numberMaxElement = 5;
        size_t numberField = 2;
        std::vector<std::vector<std::string>> bufferName = {{"lionel est        le plus fort"},
                                                            {"Lacroix c'est mon nom"}};
        smartDescriptor::buffer::DataAnalysis dataAnalysis(numberMaxElement, numberField);
        for (size_t indexField = 0; indexField < numberField; ++indexField)
        {
            for (size_t index = 0; index < bufferName[indexField].size(); ++index)
            {
                dataAnalysis.fillBuffer(indexField, index, bufferName[indexField][index]);
            }
        }
        std::vector<std::string> split;
        dataAnalysis.getSplitBlank(0, 0, split);
        BOOST_CHECK_EQUAL(split.size(), 5);
        dataAnalysis.getSplitBlank(1, 0, split);
        BOOST_CHECK_EQUAL(split.size(), 4);
    }

/*
    BOOST_AUTO_TEST_CASE(test_DataAnalysis_connection)
    {
        size_t numberMaxElement = 5;
        size_t numberField = 2;
        std::vector<std::vector<std::string>> bufferName =         size_t numberMaxElement = 5;
        size_t numberField = 2;
        std::vector<std::vector<std::string>> bufferName = {{"lionel",  "mohamed", "jean",   "lilia", "william",},
                                                            {"Lacroix", "mohamed", "Belico", "Kodja"}};
        smartDescriptor::buffer::DataAnalysis dataAnalysis(numberField, numberMaxElement);
        for (size_t indexField = 0; indexField < numberField; ++indexField)
        {
            for (size_t index = 0; index < bufferName[indexField].size(); ++index)
            {
                dataAnalysis.fillBuffer(indexField, index, bufferName[indexField][index]);
            }
        }
    }
    */


BOOST_AUTO_TEST_SUITE_END()