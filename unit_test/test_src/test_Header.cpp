#include "Header.h"
#include <vector>
#include <boost/test/unit_test.hpp>
#include <iostream>


BOOST_AUTO_TEST_SUITE(test_Header)

    BOOST_AUTO_TEST_CASE(test_Head) {
        std::vector<std::string> head = {
                 "nom1" ,"1NOm2","prenom3","2prenom5"
        };
        smartDescriptor::header::Header header(head);

        BOOST_CHECK_EQUAL(header.get(0),head[0]);
        BOOST_CHECK_EQUAL(header.getField(0),"nom");
        BOOST_CHECK_EQUAL(header.getField(1),"nom");
        BOOST_CHECK_EQUAL(header.getDigit(1),12);
        std::cerr<<"merde"<<std::endl;
    }
BOOST_AUTO_TEST_SUITE_END()