#include "Classifier.h"
#include <vector>
#include <boost/test/unit_test.hpp>
#include <iostream>


BOOST_AUTO_TEST_SUITE(test_Classifier)

    BOOST_AUTO_TEST_CASE(test_Classifier_header) {
        smartDescriptor::header::Classifier classifier(smartDescriptor::LASTNAME);
        std::vector<std::string> lastName = {"nom", "name", "lastname"};
        for (const std::string &data:lastName) {
            classifier.fill(data);
        }
        smartDescriptor::header::Header header({"name", "firstname", "phone"});
        classifier.match(header);
        BOOST_CHECK_EQUAL(classifier.getPosition()[0], 0);
        BOOST_CHECK_EQUAL(classifier.getPosition().size(), 1);
    }

BOOST_AUTO_TEST_SUITE_END()