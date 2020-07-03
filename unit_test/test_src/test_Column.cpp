#include "Column.h"
#include <vector>
#include <string>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_Column)

    BOOST_AUTO_TEST_CASE(test_Column_simple)
    {
        size_t numberMaxElement = 5;
        smartDescriptor::buffer::Column<std::string> column(numberMaxElement);
        std::vector<std::string> buffer = {"lionel", "jean", "lilia", "william", "mohamed"};

        for (size_t index = 0; index < numberMaxElement; index++)
        {
            column.fill(buffer[index], index);
        }
        BOOST_CHECK_EQUAL(column.getSize(), numberMaxElement);
        BOOST_CHECK_EQUAL(column.getFlags(0), 0);
        BOOST_CHECK_EQUAL(column.get(0), buffer[0]);
    }


    BOOST_AUTO_TEST_CASE(test_Column_pop)
    {
        size_t numberMaxElement = 5;
        smartDescriptor::buffer::Column<std::string> column(numberMaxElement);
        std::vector<std::string> buffer = {"lionel", "jean", "lilia", "william", "mohamed"};

        for (size_t index = 0; index < numberMaxElement; index++)
        {
            column.fill(buffer[index], index);
        }
        column.popFront();
        BOOST_CHECK_EQUAL(column.get(0), buffer[1]);
        BOOST_CHECK_EQUAL(column.getSize(), numberMaxElement - 1);
        column.popBack();
        BOOST_CHECK_EQUAL(column.getSize(), numberMaxElement - 2);
        BOOST_CHECK_EQUAL(column.get(numberMaxElement - 3),buffer[numberMaxElement - 2]);
    }


    BOOST_AUTO_TEST_CASE(test_Column_fill)
    {
        size_t numberMaxElement = 5;
        smartDescriptor::buffer::Column<std::string> column(numberMaxElement);
        std::vector<std::string> buffer = {"lionel", "jean", "lilia", "william", "mohamed", "rasha", "andrei"};
        size_t index = 0;
        for (const std::string & word :buffer)
        {
            column.fill(word, index);
            index++;
        }
        BOOST_CHECK_EQUAL(column.getSize(), numberMaxElement);
        BOOST_CHECK_EQUAL(column.get(0),buffer[2]);
    }
BOOST_AUTO_TEST_SUITE_END()