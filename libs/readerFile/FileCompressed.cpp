#include "FileCompressed.h"
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/zlib.hpp>
//#include <boost/iostreams/filter/lzma.hpp>
#include <iostream>


namespace smartDescriptor {
    namespace readerFile {
        FileCompressed::FileCompressed(FileParameters &fileParameters) {
            m_fileCompressed = new(std::nothrow) std::ifstream(fileParameters.getFilenameInput()
                                                    , std::ios_base::in | std::ios_base::binary);
             Compressed compressed = fileParameters.getCompressed();
            if ( compressed== BZ2) {
                m_file.push(boost::iostreams::bzip2_decompressor());
            } else if (compressed == Z) {
                m_file.push(boost::iostreams::zlib_decompressor());
            } else if (compressed == GZ) {
                m_file.push(boost::iostreams::gzip_decompressor());
            }
            m_file.push(*m_fileCompressed);
        }

        bool FileCompressed::getLineFile(std::string &line) {
            return std::getline(m_file, line) ? true : false;
        }
    }

}
