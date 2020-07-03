#ifndef DETECT_TEXT_ENCODING_H_
#define DETECT_TEXT_ENCODING_H_

#include "Utils.h"
#include "FileParameters.h"
#include "AnalysisDelimiter.h"
#include "Params.h"
#include "ReaderCsv.h"
//#include <stddef.h>
#include "Column.h"
#include "ReaderCsv.h"
#include "EncodingAnalysis.h"


namespace smartDescriptor
{
    namespace encoding
    {

        typedef std::vector<unsigned char> bytes;

        enum DetectUTF16_BOM_LE : unsigned char
        {
            FIRST_UTF16_BOM_LE = 0xFF, SECOND_UTF16_BOM_LE = 0xFE
        };

        enum DetectUTF16_BOM_BE : unsigned char
        {
            FIRST_UTF16_BOM_BE = 0xFE, SECOND_UTF16_BOM_BE = 0xFF
        };

        enum DetectUTF8_BOM
        {
            FIRST_UTF8_BOM = 0xEF, SECOND_UTF8_BOM = 0xBB, THIRD_UTF8_BOM = 0xBF
        };

        struct FeaturesBytes
        {
            bool hasNull = false;
            bool isUTF8LE_BOM = false;
            bool isUTF16_LE_BOM = false;
            bool isUTF16_BE_BOM = false;
            bool isUTF8_BOM = false;
            bool hasUTF16_LE_Control = false;
            bool hasUTF16_BE_Control = false;
        };


        class AnalysisCharacter
        {
        public:
            explicit AnalysisCharacter::AnalysisCharacter(size_t minimumLine);

            void analysisFile(const smartDescriptor::readerFile::FileParameters &fileParameters,
                              const ParamsDelimiter &paramsDelimiters);

            smartDescriptor::readerCsv::ParamFile &getParamFile() const;

            void getStatistics(std::string &statistics);

        private:
            //attribut
            std::unique_ptr<EncodingAnalysis> m_encodingBuffer = nullptr;
            smartDescriptor::readerCsv::ParamFile m_paramFile;
            std::string m_statistics;
            FeaturesBytes m_featuresBytes;
            size_t m_minimumWord;


            //Methods
            template<typename FileType>
            void detectEncoding(FileType &file, const smartDescriptor::ParamsDelimiter &paramsDelimiter)
            {
                unsigned char *buffer = nullptr;
                size_t bufferSize = 0;
                file.getBlockData(bufferSize, &buffer);
                CheckBOM(buffer, bufferSize);
                setReader(buffer, paramsDelimiter, bufferSize);
                CheckNewLine(buffer,bufferSize);
                analysisText(buffer, bufferSize);

                while (file.getBlockData(bufferSize, &buffer))
                {
                    analysisText(buffer, bufferSize);
                    delete buffer;
                }
            }

            //Methods

            void CheckBOM(const unsigned char *buffer, size_t size);

            void setReader(const unsigned char *buffer, const smartDescriptor::ParamsDelimiter &paramsDelimiter,
                           size_t size);

            void analysisText(const unsigned char *buffer, size_t size);

            void CheckNewLine(const unsigned char *buffer, size_t size);

            void detectSpecialWord(size_t numberField, size_t numberLine,
                                   const std::vector<unsigned char> &word);

        };


        /*
        class DetectTextEncoding {

        public:
            DetectTextEncoding(FileParameters &fileParameters);

            ~DetectTextEncoding();

            static Encoding
            CheckBOM(const unsigned char *pBuffer, size_t size);        // Just check if there is a BOM and return
            Encoding DetectEncoding(const unsigned char *pBuffer,
                                    size_t size) const;    // Check BOM and also guess if there is no BOM
            static int
            GetBOMLengthFromEncodingMode(Encoding encoding);            // Just return the BOM length of a given mode

            void SetNullSuggestsBinary(bool null_suggests_binary) { null_suggests_binary_ = null_suggests_binary; }

            void SetUtf16UnexpectedNullPercent(int percent);

            void SetUtf16ExpectedNullPercent(int percent);

        private:
            TextEncodingDetect(const TextEncodingDetect &);

            const TextEncodingDetect &operator=(const TextEncodingDetect &);

            static const unsigned char *utf16_bom_le_;
            static const unsigned char *utf16_bom_be_;
            static const unsigned char *utf8_bom_;

            bool null_suggests_binary_;
            int utf16_expected_null_percent_;
            int utf16_unexpected_null_percent_;

            Encoding CheckUTF8(const unsigned char *pBuffer,
                               size_t size) const;                // Check for valid UTF8 with no BOM
            static Encoding CheckUTF16NewlineChars(const unsigned char *pBuffer,
                                                   size_t size);    // Check for valid UTF16 with no BOM via control chars
            Encoding CheckUTF16ASCII(const unsigned char *pBuffer,
                                     size_t size) const;        // Check for valid UTF16 with no BOM via null distribution
            static bool DoesContainNulls(const unsigned char *pBuffer, size_t size);            // Check for nulls
        };*/
    }
}
#endif
