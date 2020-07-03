#include "FileArchive.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <exception>
#include <iostream>

using namespace std;
namespace smartDescriptor
{
    namespace readerFile
    {

        FileArchive::FileArchive(const FileParameters &fileParameters) : m_sizeBuffer(0)
        {
            m_archiveFile = archive_read_new();
            setFilter(fileParameters.getCompressed());
            setArchive(fileParameters.getArchive());
            if (archive_read_open_filename(m_archiveFile, fileParameters.getFilenameInput().c_str(), 10240) ==
                ARCHIVE_OK)
            {
                archive_read_next_header(m_archiveFile, &m_entry);
            }
            else
            {
                cerr << "archive unknown" << endl;
                exit(0);
            }
        }

        bool FileArchive::getBlockFile()
        {
            m_buffer.clear();
            if (archive_read_data_block(m_archiveFile, &m_data, &m_size, &m_offset) == ARCHIVE_OK)
            {
                string str((const char *) m_data, m_size);
                boost::split(m_buffer, str, boost::is_any_of("\n"));
                m_sizeBuffer = m_buffer.size() - 1;
                return true;
            }
            else
            {
                return false;
            }
        }

        bool FileArchive::getLineFile(string &line)
        {
            if (m_sizeBuffer > 0)
            {
                line = (*m_buffer.begin());
                m_buffer.pop_front();
                m_sizeBuffer--;
                return true;
            }
            else if (getBlockFile())
            {
                line = (*m_buffer.begin());
                m_buffer.pop_front();
                m_sizeBuffer--;
                return true;
            }
            else
            {
                return false;
            }
        }

        void FileArchive::setArchive(smartDescriptor::Archive archive)
        {
            if (archive == smartDescriptor::TAR)
            {
                archive_read_support_format_tar(m_archiveFile);
            }
            if (archive == smartDescriptor::ZIP)
            {
                archive_read_support_format_zip(m_archiveFile);
            }
        }

        void FileArchive::setFilter(smartDescriptor::Compressed compressed)
        {

            if (compressed == smartDescriptor::GZ)
            {
                archive_read_support_filter_gzip(m_archiveFile);
            }
            if (compressed == smartDescriptor::LZMA || compressed == smartDescriptor::LZ)
            {
                archive_read_support_filter_lzma(m_archiveFile);
            }
            if (compressed == smartDescriptor::BZ2)
            {
                archive_read_support_filter_bzip2(m_archiveFile);
            }
            if (compressed == smartDescriptor::XZ)
            {
                archive_read_support_filter_xz(m_archiveFile);
            }
        }
    }
}