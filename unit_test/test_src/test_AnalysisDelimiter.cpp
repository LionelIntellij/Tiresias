#include "AnalysisDelimiter.h"
#include <vector>
#include <boost/test/unit_test.hpp>
#include "Params.h"

BOOST_AUTO_TEST_SUITE(test_AnalysisDelimiter)

    BOOST_AUTO_TEST_CASE(test_Delimiter_semicolon)
    {
        unsigned char ctext[] = "lionel;lacroix;050899999,\n"
                                "lionel;lacroix;050899999\n"
                                "lionel;\";la;c;r;;o;ix\";050899999,\n"
                                "lionel;\";la;c;r;;o;ix\";050899999,\n"
                                "lionel;\"lac;roix\";050899999";
        size_t size = strlen((char *) ctext);

        smartDescriptor::ParamsDelimiter paramsDelimiter;
        paramsDelimiter.delimiters = {";", ",", "|"};
        paramsDelimiter.threshold = 0.9;

        smartDescriptor::readerCsv::AnalysisDelimiter analysisDelimiter(paramsDelimiter);
        analysisDelimiter.computeStatistics(size, ctext);

        smartDescriptor::readerCsv::StatisticsDelimiter ParamDelimiters;
        analysisDelimiter.setDelimiter(ParamDelimiters);
        BOOST_CHECK_EQUAL(ParamDelimiters.delimiter ,";");

    }

    BOOST_AUTO_TEST_CASE(test_Delimiter_tab)
    {
        unsigned char ctext[] = "lionel\tlacroix\t050899999,\n"
                                "lionel\tlacroix\t050899999\n"
                                "lionel\t\";la;c;r;;o;ix\"\t050899999,\n"
                                "lionel\t\";la;c;r;;o;ix\"\t050899999,\n"
                                "lionel\t\"lac;roix\"\t050899999";
        size_t size = strlen((char *) ctext);

        smartDescriptor::ParamsDelimiter paramsDelimiter;
        paramsDelimiter.delimiters = {";", ",", "\t"};
        paramsDelimiter.threshold = 0.9;

        smartDescriptor::readerCsv::AnalysisDelimiter analysisDelimiter(paramsDelimiter);
        analysisDelimiter.computeStatistics(size, ctext);

        smartDescriptor::readerCsv::StatisticsDelimiter ParamDelimiters;
        analysisDelimiter.setDelimiter(ParamDelimiters);
        BOOST_CHECK_EQUAL(ParamDelimiters.delimiter ,"\t");

    }

BOOST_AUTO_TEST_SUITE_END()