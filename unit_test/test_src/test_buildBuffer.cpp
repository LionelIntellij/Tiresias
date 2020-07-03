#include "BuildBuffer.h"
#include "DataAnalysis.h"
#include <vector>
#include "FileParameters.h"
#include "module.h"

BOOST_AUTO_TEST_SUITE(test_buildBuffer)

    BOOST_AUTO_TEST_CASE(test_buildBuffer) {
        size_t minimumLine = 100;
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = ';';
        paramFile.numberField = 15;
        paramFile.numberLine = 10;
        smartDescriptor::buffer::BuildBuffer buildBuffer(minimumLine, paramFile);
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::buffer::DataAnalysis dataAnalysis(buildBuffer.getDataAnalysis(fileParameters));
        BOOST_CHECK_EQUAL(dataAnalysis.getNumberField(), 15);
        std::vector<size_t> flagsConnection;
        dataAnalysis.getFlagsConnection(flagsConnection);
        BOOST_CHECK_EQUAL(flagsConnection.size(), paramFile.numberLine - 1);
        std::vector<std::string> headResult = {
                "SOC", "AGECO", "IDDOS", "IDCLI",
                "NOM", "PRENOM", "NOMJF", "CMPVOIE",
                "VOIE", "LOCA", "CPCL", "BDIST",
                "NUMTEL", "COMPLNOM", "TOPVTELP"};
        smartDescriptor::header::Header header(buildBuffer.getHeader());
        size_t indexField = 0;
        for (const std::string &field : headResult) {
            BOOST_CHECK_EQUAL(field,header.get(indexField));
                indexField++;
        }
    }

BOOST_AUTO_TEST_SUITE_END()