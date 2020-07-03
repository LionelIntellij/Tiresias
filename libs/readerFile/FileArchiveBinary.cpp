#include "FileArchiveBinary.h"
#include <algorithm>


namespace smartDescriptor {
    namespace readerFile {

        FileArchiveBinary::FileArchiveBinary(const smartDescriptor::readerFile::FileParameters &fileParameters) {
            m_archiveFile = archive_read_new();
            setFilter(fileParameters.getCompressed());
            setArchive(fileParameters.getArchive());
            if (archive_read_open_filename(m_archiveFile, fileParameters.getFilenameInput().c_str(), 10240) ==
                ARCHIVE_OK) {
                archive_read_next_header(m_archiveFile, &m_entry);
            } else {
                std::cerr << "archive unknown" << std::endl;
                throw;
            }
            m_fileSize = (size_t) archive_entry_size(m_entry);
        }

        bool FileArchiveBinary::getBlockData(size_t &bufferSize, unsigned char **buffer) {
            const void * data;
            if (m_offset != 0 && (archive_read_data_block(m_archiveFile, &data, &bufferSize, &m_offset) == ARCHIVE_OK)) {
                *buffer = new unsigned char [bufferSize];
                memcpy(*buffer,(unsigned char *)data , bufferSize);
                return true;
            } else {
                return false;
            }
        }

        void FileArchiveBinary::setArchive(smartDescriptor::Archive archive) {
            if (archive == smartDescriptor::TAR) {
                archive_read_support_format_tar(m_archiveFile);
            }
            if (archive == smartDescriptor::ZIP) {
                archive_read_support_format_zip(m_archiveFile);
            }
        }

        void FileArchiveBinary::setFilter(smartDescriptor::Compressed compressed) {

            if (compressed == smartDescriptor::GZ) {
                archive_read_support_filter_gzip(m_archiveFile);
            }
            if (compressed == smartDescriptor::LZMA
                || compressed == smartDescriptor::LZ) {
                archive_read_support_filter_lzma(m_archiveFile);
            }
            if (compressed == smartDescriptor::BZ2) {
                archive_read_support_filter_bzip2(m_archiveFile);
            }
            if (compressed == smartDescriptor::XZ) {
                archive_read_support_filter_xz(m_archiveFile);
            }
        }
    }
}