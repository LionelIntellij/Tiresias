#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "AnalysisHeader.h"
#include "Header.h"
#include "Utils.h"
#include <unordered_map>

BOOST_AUTO_TEST_SUITE(test_AnalysisHeader)


    BOOST_AUTO_TEST_CASE(test_AnalysisHeader)
    {
        std::vector<smartDescriptor::FieldFlags> fieldFlags = {smartDescriptor::LASTNAME, smartDescriptor::FIRSTNAME,
                                                               smartDescriptor::PHONE};
        smartDescriptor::header::Header header({"nom", "prenom", "tel1", "tel6", "tel3", "Tel"});
        smartDescriptor::header::AnalysisHeader analysisHeader(header, fieldFlags);
        std::vector<smartDescriptor::header::DescriptorHeader> descriptor;
        analysisHeader.decisionHeader(descriptor);
        std::unordered_map<smartDescriptor::FieldFlags, int> result = {{smartDescriptor::LASTNAME,  0},
                                                                       {smartDescriptor::FIRSTNAME, 1},};
        std::unordered_map<size_t, int> instancePhone {{5, 0},
                                                       {2, 1},
                                                       {4, 2},
                                                       {3, 3}};
        BOOST_CHECK_EQUAL(descriptor.size(), header.getSize());
        for (const smartDescriptor::header::DescriptorHeader &descriptorHeader : descriptor)
        {
            if (descriptorHeader.field == smartDescriptor::PHONE)
            {
                BOOST_CHECK_EQUAL(instancePhone.at(descriptorHeader.position), descriptorHeader.instance);
            }
            else
            {
                BOOST_CHECK_EQUAL(result.at(descriptorHeader.field), descriptorHeader.position);
            }
        }
    }


BOOST_AUTO_TEST_SUITE_END()