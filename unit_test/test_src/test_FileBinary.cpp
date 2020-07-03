#include "FileArchiveBinary.h"
#include "FileCsvBinary.h"
#include "FileZLibBinary.h"
#include "FileBzLibBinary.h"
#include "module.h"
#include "FileParameters.h"


BOOST_AUTO_TEST_SUITE(test_FileBinary)

    BOOST_AUTO_TEST_CASE(test_FileBinaryCsv)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".csv");
        smartDescriptor::readerFile::FileCsvBinary fileCsvBinary(fileParameters);

        size_t blockSize;
        unsigned char *buffer = nullptr;
        size_t TotalBlockSize = 0;
        while (fileCsvBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileCsvBinary.getFileSize(), TotalBlockSize);
    }

    BOOST_AUTO_TEST_CASE(test_FileArchiveBinary_tar)
    {

        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar");
        smartDescriptor::readerFile::FileArchiveBinary fileArchiveBinary(fileParameters);

        size_t blockSize;
        size_t TotalBlockSize = 0;

        unsigned char *buffer = nullptr;
        while (fileArchiveBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileArchiveBinary.getFileSize(), TotalBlockSize);
    }

    BOOST_AUTO_TEST_CASE(test_FileArchiveBinary_zip)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".zip");
        smartDescriptor::readerFile::FileArchiveBinary fileArchiveBinary(fileParameters);
        size_t blockSize;
        size_t TotalBlockSize = 0;

        unsigned char *buffer = nullptr;
        while (fileArchiveBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileArchiveBinary.getFileSize(), TotalBlockSize);
    }


    BOOST_AUTO_TEST_CASE(test_FileArchiveBinary_tar_gz)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.gz");
        smartDescriptor::readerFile::FileArchiveBinary fileArchiveBinary(fileParameters);
        size_t blockSize;
        size_t TotalBlockSize = 0;

        unsigned char *buffer = nullptr;
        while (fileArchiveBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileArchiveBinary.getFileSize(), TotalBlockSize);
    }

    BOOST_AUTO_TEST_CASE(test_FileArchiveBinary_tar_xz)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.xz");
        smartDescriptor::readerFile::FileArchiveBinary fileArchiveBinary(fileParameters);
        size_t blockSize;
        size_t TotalBlockSize = 0;

        unsigned char *buffer = nullptr;
        while (fileArchiveBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileArchiveBinary.getFileSize(), TotalBlockSize);
    }

    BOOST_AUTO_TEST_CASE(test_FileArchive_tar_bz2)
    {
        smartDescriptor::readerFile::FileParameters fileParameters(pathFile + ".tar.bz2");
        smartDescriptor::readerFile::FileArchiveBinary fileArchiveBinary(fileParameters);
        size_t blockSize;
        size_t TotalBlockSize = 0;

        unsigned char *buffer = nullptr;
        while (fileArchiveBinary.getBlockData(blockSize, &buffer))
        {
            TotalBlockSize += blockSize;
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileArchiveBinary.getFileSize(), TotalBlockSize);
    }

    BOOST_AUTO_TEST_CASE(test_FileCompressed_BZ2)
    {
        smartDescriptor::readerFile::FileBzLibBinary fileBzLibBinary(pathFile + ".csv.bz2");
        size_t blockSize;

        unsigned char *buffer = nullptr;
        while (fileBzLibBinary.getBlockData(blockSize, &buffer))
        {
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileBzLibBinary.getFileSize(), 1385);
    }

    BOOST_AUTO_TEST_CASE(test_FileCompressed_GZ)
    {
        smartDescriptor::readerFile::FileZLibBinary fileZLibBinary(pathFile + ".csv.gz");
        size_t blockSize;
        unsigned char *buffer = nullptr;
        while (fileZLibBinary.getBlockData(blockSize, &buffer))
        {
            delete buffer;
        }
        BOOST_CHECK_EQUAL(fileZLibBinary.getFileSize(), 1385);
    }

BOOST_AUTO_TEST_SUITE_END()


