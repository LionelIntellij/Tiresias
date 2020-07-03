#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "NGramExtractor.h"
#include "ExtractedNGrams.h"
#include <unordered_map>

BOOST_AUTO_TEST_SUITE(test_NGramExtractor)

    BOOST_AUTO_TEST_CASE(test_NGramExtractor){
      std::string Text ="lionel lacroix";
      int numberGrams = 3;
      smartDescriptor::nGrams::NGramExtractor nGramExtractor(numberGrams);
      nGramExtractor.extract(Text);
      smartDescriptor::nGrams::ExtractedNGrams * extractedNGrams = nullptr;
      extractedNGrams= new smartDescriptor::nGrams::ExtractedNGrams(nGramExtractor.getExtractedNGrams());
      std::string result = extractedNGrams->randomGram();
      std::unordered_map<std::string , std::string> resultWaited = { {"lio",""},
                                                        {"ion" ,""},
                                                        {"nel" ,""},
                                                        {"one",""},
                                                        {"lac",""},
                                                        {"acr","" },
                                                        {"cro",""},
                                                        {"iox",""}};
      BOOST_CHECK_EQUAL(resultWaited.find(extractedNGrams->randomGram())!=resultWaited.end() ,true);
      delete extractedNGrams;
    }

BOOST_AUTO_TEST_SUITE_END()