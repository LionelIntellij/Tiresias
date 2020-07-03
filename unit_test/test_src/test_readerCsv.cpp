#include "ReaderCsv.h"
#include <vector>
#include <iostream>
#include <FileCsv.h>
#include "module.h"

BOOST_AUTO_TEST_SUITE(test_ReaderCsv)

    BOOST_AUTO_TEST_CASE(test_Reader_csv)
    {
        smartDescriptor::readerCsv::ParamFile paramFile;
        paramFile.delimiter = '\t';
        paramFile.numberField = 12;
        paramFile.numberLine = 10;
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + "1.csv");
        smartDescriptor::readerFile::FileCsv *fileCsv = nullptr;
        fileCsv = new smartDescriptor::readerFile::FileCsv(fileParameters);
        smartDescriptor::readerCsv::ReaderCsv<smartDescriptor::readerFile::FileCsv> readerCsv(paramFile, fileCsv);
        size_t sizeRecord;
        std::vector<std::string> record;
        int numberRecord = 0;
        while (readerCsv.getRecord(sizeRecord, record))
        {
            if (record.size() == paramFile.numberField)
            {
                numberRecord++;
            }
        }
        BOOST_CHECK_EQUAL(numberRecord, paramFile.numberLine-1);
        delete fileCsv;
    }
BOOST_AUTO_TEST_SUITE_END()