#include "FileArchive.h"
#include "FileCsv.h"
#include "FileCompressed.h"
#include "module.h"
#include "FileParameters.h"


BOOST_AUTO_TEST_SUITE(test_File)

    BOOST_AUTO_TEST_CASE(test_FileCsv)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::readerFile::FileCsv fileCsv(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileCsv.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

    BOOST_AUTO_TEST_CASE(test_FileCompressed_BZ2)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv.bz2");
        smartDescriptor::readerFile::FileCompressed fileCompressed(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileCompressed.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

    BOOST_AUTO_TEST_CASE(test_FileCompressed_GZ)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv.gz");
        smartDescriptor::readerFile::FileCompressed fileCompressed(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileCompressed.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }


    BOOST_AUTO_TEST_CASE(test_FileArchive_zip)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".zip");
        smartDescriptor::readerFile::FileArchive fileArchive(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileArchive.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

    BOOST_AUTO_TEST_CASE(test_FileArchive_tar)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar");
        smartDescriptor::readerFile::FileArchive fileArchive(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileArchive.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());

    }

    BOOST_AUTO_TEST_CASE(test_FileArchive_tar_gz)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.gz");
        smartDescriptor::readerFile::FileArchive fileArchive(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileArchive.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

    BOOST_AUTO_TEST_CASE(test_FileArchive_tar_xz)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.xz");
        smartDescriptor::readerFile::FileArchive fileArchive(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileArchive.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

    BOOST_AUTO_TEST_CASE(test_FileArchive_tar_bz2)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.bz2");
        smartDescriptor::readerFile::FileArchive fileArchive(fileParameters);
        std::string line;
        std::vector<std::string> bufferLine;
        while (fileArchive.getLineFile(line))
        {
            if (!line.empty())
            {
                bufferLine.push_back(line);
            }
        }
        BOOST_CHECK_EQUAL(10, bufferLine.size());
    }

BOOST_AUTO_TEST_SUITE_END()


