// Includes
#include "AnalysisCharacter.h"
#include "FileArchiveBinary.h"
#include "FileBzLibBinary.h"
#include "FileArchiveBinary.h"
#include "FileZLibBinary.h"
#include "FileCsvBinary.h"


namespace smartDescriptor
{
    namespace encoding
    {

        AnalysisCharacter::AnalysisCharacter(const size_t minimumWord) : m_minimumWord(minimumWord)
        {
        }

        void AnalysisCharacter::CheckBOM(const unsigned char *buffer, size_t size)
        {
            if (size >= 2 && buffer[0] == FIRST_UTF16_BOM_LE && buffer[1] == SECOND_UTF16_BOM_LE)
            {
                m_featuresBytes.isUTF16_LE_BOM = true;
            }
            else if (size >= 2 && buffer[0] == FIRST_UTF16_BOM_BE && buffer[1] == SECOND_UTF16_BOM_BE)
            {
                m_featuresBytes.isUTF16_BE_BOM;
            }
            else if (size >= 3 && buffer[0] == FIRST_UTF8_BOM && buffer[1] == SECOND_UTF8_BOM &&
                     buffer[2] == THIRD_UTF8_BOM)
            {
                m_featuresBytes.isUTF8_BOM;
            }
        }

        void AnalysisCharacter::analysisFile(const smartDescriptor::readerFile::FileParameters &fileParameters,
                                             const ParamsDelimiter &paramsDelimiters)
        {
            Compressed compressed = fileParameters.getCompressed();
            Extension extension = fileParameters.getExtension();
            Archive archive = fileParameters.getArchive();
            if (archive != NO_ARCHIVE)
            {
                smartDescriptor::readerFile::FileArchiveBinary file(fileParameters);
                detectEncoding(file, paramsDelimiters);
            }
            else if (compressed == GZ)
            {
                smartDescriptor::readerFile::FileZLibBinary file(fileParameters.getFilenameInput());
                detectEncoding(file, paramsDelimiters);
            }
            else if (compressed == BZ2)
            {
                smartDescriptor::readerFile::FileBzLibBinary file(fileParameters.getFilenameInput());
                detectEncoding(file, paramsDelimiters);
            }
            else if (extension != NO_EXTENSION)
            {
                smartDescriptor::readerFile::FileCsvBinary file(fileParameters);
                detectEncoding(file, paramsDelimiters);
            }
            else
            {
                std::cerr << " Input filename : " << fileParameters.getFilenameInput() << std::endl;
                throw std::runtime_error(" file has not extension ");
            }
        }

        void AnalysisCharacter::setReader(const unsigned char *buffer, const ParamsDelimiter &paramsDelimiters,
                                          const size_t size)
        {
            smartDescriptor::readerCsv::AnalysisDelimiter analysisDelimiter(paramsDelimiters);
            analysisDelimiter.computeStatistics(size, buffer);
            smartDescriptor::readerCsv::StatisticsDelimiter statisticsDelimiter;
            analysisDelimiter.setDelimiter(statisticsDelimiter);
            m_paramFile.numberField = statisticsDelimiter.instanceDelimiter + 1;
            m_paramFile.delimiter = smartDescriptor::readerCsv::delimiterBytes.at(statisticsDelimiter.delimiter);
            m_encodingBuffer = std::unique_ptr<EncodingAnalysis>(
                    new EncodingAnalysis(m_paramFile.numberField, m_minimumWord));
        }


        void AnalysisCharacter::detectSpecialWord(const size_t numberField, const size_t numberLine,
                                                  const std::vector<unsigned char> &word)
        {
            size_t sizeSpecial = 0;
            size_t index = 0;
            size_t indexSpecial = 0;
            while (index < word.size())
            {
                while (word[index] > 127)
                {
                    sizeSpecial++;
                    index++;
                }
                indexSpecial = index - sizeSpecial;
                index++;
            }
            if (sizeSpecial)
            {
                m_encodingBuffer->fill(numberField,numberLine,indexSpecial,sizeSpecial,word);
            }
        }


        smartDescriptor::readerCsv::ParamFile &AnalysisCharacter::getParamFile() const
        {
            return m_paramFile;
        }

        void AnalysisCharacter::analysisText(const unsigned char *buffer, size_t size)
        {
            unsigned char character;
            bool inQuote = false;
            size_t numberField = 0;
            size_t index = 0;
            std::vector<unsigned char> word;
            while (index < size)
            {
                character = buffer[index];
                if (character == 0x22)
                {
                    inQuote = !inQuote;
                }
                else if (character == 0x0a)
                {
                    numberField = 0;
                    m_paramFile.numberLine++;
                }
                else if (character == m_paramFile.delimiter && !inQuote)
                {
                    numberField++;
                    if (!word.empty())
                    {
                        detectSpecialWord(numberField, m_paramFile.numberLine, word);
                    }
                    word.clear();
                }
                else if (std::isspace(character))
                {
                    if (!word.empty())
                    {
                        detectSpecialWord(numberField, m_paramFile.numberLine, word);
                    }
                    word.clear();
                }
                else
                {
                    word.push_back(character);
                }
                index++;
            }
        }


        void AnalysisCharacter::getStatistics(std::string &statistics)
        {
            statistics = m_statistics;
            statistics += "------------- statistics Analysis coding ---------------";
        }


        void AnalysisCharacter::CheckNewLine(const unsigned char *buffer, size_t size)
        {
            size_t beControls = 0, leControls = 0, hasNull = 0;
            unsigned char currentCharacter, oldCharacter;
            size_t index = 0;
            size--;
            while (index < size)
            {
                oldCharacter = buffer[index++];
                currentCharacter = buffer[index++];
                if (oldCharacter == 0x00)
                {
                    if (currentCharacter == 0x0d || currentCharacter == 0x0a)
                    {
                        beControls++;
                    }
                }
                if (currentCharacter == 0x00)
                {
                    hasNull++;
                    if (oldCharacter == 0x0d || oldCharacter == 0x0a)
                    {
                        leControls++;
                    }
                }
            }
            if (leControls > 1)
            {
                m_featuresBytes.hasUTF16_LE_Control = true;
            }
            if (beControls > 1)
            {
                m_featuresBytes.hasUTF16_BE_Control = true;
            }
            if (hasNull > 1)
            {
                m_featuresBytes.hasNull = true;
            }
        }

    }
}



/*
///////////////////////////////////////////////////////////////////////////////
// Checks if a buffer contains valid utf8. Returns:
// None - not valid utf8
// UTF8_NOBOM - valid utf8 encodings and multibyte sequences
// ASCII - Only data in the 0-127 range.
///////////////////////////////////////////////////////////////////////////////

AnalysisCharacter::Encoding AnalysisCharacter::CheckUTF8(const unsigned char *buffer, size_t size) const {
    bool only_saw_ascii_range = true;
    size_t pos = 0;
    int more_chars;

    while (pos < size) {
        unsigned char ch = pBuffer[pos++];

        if (ch == 0 && null_suggests_binary_) {
            return None;
        } else if (ch <= 127) {
            // 1 byte
            more_chars = 0;
        } else if (ch >= 194 && ch <= 223) {
            // 2 Byte
            more_chars = 1;
        } else if (ch >= 224 && ch <= 239) {
            // 3 Byte
            more_chars = 2;
        } else if (ch >= 240 && ch <= 244) {
            // 4 Byte
            more_chars = 3;
        } else {
            return None;                        // Not utf8
        }

        // Check secondary chars are in range if we are expecting any
        while (more_chars && pos < size) {
            only_saw_ascii_range = false;        // Seen non-ascii chars now

            ch = pBuffer[pos++];
            if (ch < 128 || ch > 191)
                return None;                    // Not utf8

            --more_chars;
        }
    }

    // If we get to here then only valid UTF-8 sequences have been processed

    // If we only saw chars in the range 0-127 then we can't assume UTF8 (the caller will need to decide)
    if (only_saw_ascii_range)
        return ASCII;
    else
        return UTF8_NOBOM;
}

*/