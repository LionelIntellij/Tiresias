#include <deque>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "FileParameters.h"

namespace smartDescriptor
{
    namespace readerFile
    {

        FileParameters::FileParameters(const std::string &filenameInput) : m_filenameInput(filenameInput), m_extension(
                NO_EXTENSION), m_compressed(NO_COMPRESSED), m_archive(NO_ARCHIVE)
        {
            if (!boost::filesystem::exists(m_filenameInput))
            {
                std::cerr << "File not found " + m_filenameInput << std::endl;
                throw;
            }
            std::deque<std::string> extensionFile;
            boost::split(extensionFile, filenameInput, boost::is_any_of("."));
            if (m_extension > 1)
            {
                extensionFile.pop_front();
                setUpper(extensionFile);
                setArchive(extensionFile);
                setCompressed(extensionFile);
                setExtension(extensionFile);
            }
        }


        void FileParameters::setUpper(std::deque<std::string> &extensions)
        {
            size_t index;
            for (index = 0; index < extensions.size(); ++index)
            {
                std::transform(extensions[index].begin(), extensions[index].end(), extensions[index].begin(),
                               ::toupper);
            }
        }


        void FileParameters::setArchive(const std::deque<std::string> &archives)
        {
            std::vector<std::string> archiveFound;
            for (const std::string &archive : archives)
            {
                if (archiveFile.find(archive) != archiveFile.end())
                {
                    archiveFound.push_back(archive);
                }
            }
            if (archiveFound.size() == 1)
            {
                m_archive = archiveFile.at(*archiveFound.begin());
            }
            if (archiveFound.size() > 1)
            {
                std::string allArchive;
                for (const std::string &archive :archiveFound)
                {
                    allArchive += archive + " ";
                }
                std::cerr << "several archive : " + allArchive + " found" << std::endl;
                throw std::runtime_error("file type unknown");
            }
        }


        void FileParameters::setCompressed(const std::deque<std::string> &compressed)
        {
            std::vector<std::string> compressedFound;
            for (const std::string &compress : compressed)
            {
                if (compressedFile.find(compress) != compressedFile.end())
                {
                    compressedFound.push_back(compress);
                }
            }
            if (compressedFound.size() == 1)
            {
                m_compressed = compressedFile.at(*compressedFound.begin());
            }
            if (compressedFound.size() > 1)
            {
                std::string allCompressed;
                for (const std::string &compress :compressedFound)
                {
                    allCompressed += compress + " ";
                }
                std::cerr << "several compressed : " + allCompressed + " found" << std::endl;
                throw std::runtime_error("file type unknown");
            }
        }


        void FileParameters::setExtension(const std::deque<std::string> &extensions)
        {
            std::vector<std::string> extensionsFound;
            for (const std::string &extension : extensions)
            {
                if (extensionFile.find(extension) != extensionFile.end())
                {
                    extensionsFound.push_back(extension);
                }
            }
            if (extensionsFound.size() == 1)
            {
                m_extension = extensionFile.at(*extensionsFound.begin());
            }
            if (extensionsFound.size() > 1)
            {
                std::string allExtensions;
                for (const std::string &extension : extensionsFound)
                {
                    allExtensions += extension + " ";
                }
                std::cerr << "several extensions : " + allExtensions + " found" << std::endl;
                throw std::runtime_error("file type unknown");
            }
        }

        Extension FileParameters::getExtension() const
        {
            return m_extension;
        }

        Archive FileParameters::getArchive() const
        {
            return m_archive;
        }

        Compressed FileParameters::getCompressed() const
        {
            return m_compressed;
        }

        const std::string &FileParameters::getFilenameInput() const
        {
            return m_filenameInput;
        }
    }
}