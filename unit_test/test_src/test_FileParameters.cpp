#include "module.h"
#include "FileParameters.h"

BOOST_AUTO_TEST_SUITE(test_FileParameters)

    BOOST_AUTO_TEST_CASE(test_FileNaked){
     smartDescriptor::readerFile::FileParameters fileParameters(pathFile+".csv");
     BOOST_CHECK_EQUAL(fileParameters.getFilenameInput() ,pathFile+".csv");
     BOOST_CHECK_EQUAL(fileParameters.getCompressed() ,smartDescriptor::NO_COMPRESSED);
     BOOST_CHECK_EQUAL( fileParameters.getArchive() , smartDescriptor::NO_ARCHIVE);
     BOOST_CHECK_EQUAL(fileParameters.getExtension() ,smartDescriptor::CSV);
    }

    BOOST_AUTO_TEST_CASE(test_FileExtension){
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile+".csv.gz");
        BOOST_CHECK_EQUAL(fileParameters.getFilenameInput() ,pathFile+".csv.gz");
        BOOST_CHECK_EQUAL(fileParameters.getArchive() ,smartDescriptor::NO_ARCHIVE);
        BOOST_CHECK_EQUAL(fileParameters.getExtension() ,smartDescriptor::CSV);
        BOOST_CHECK_EQUAL(fileParameters.getCompressed() ,smartDescriptor::GZ);

    }


    BOOST_AUTO_TEST_CASE(test_FileFormat){
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile+".zip");
        BOOST_CHECK_EQUAL(fileParameters.getFilenameInput() ,pathFile+".zip");
        BOOST_CHECK_EQUAL(fileParameters.getArchive() ,smartDescriptor::ZIP);
        BOOST_CHECK_EQUAL(fileParameters.getCompressed() ,smartDescriptor::NO_COMPRESSED);
        BOOST_CHECK_EQUAL(fileParameters.getExtension() ,smartDescriptor::NO_EXTENSION);
    }

    BOOST_AUTO_TEST_CASE(test_FileFormatExtension){
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile+".tar.gz");
        BOOST_CHECK_EQUAL(fileParameters.getFilenameInput() ,pathFile+".tar.gz");
        BOOST_CHECK_EQUAL(fileParameters.getArchive() ,smartDescriptor::TAR);
        BOOST_CHECK_EQUAL(fileParameters.getCompressed() ,smartDescriptor::GZ);
        BOOST_CHECK_EQUAL(fileParameters.getExtension() ,smartDescriptor::NO_EXTENSION);
    }

BOOST_AUTO_TEST_SUITE_END()
