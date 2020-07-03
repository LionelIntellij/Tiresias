#include <boost/algorithm/string.hpp>
#include <algorithm>
#include "BuildBuffer.h"
#include "FileArchive.h"
#include "FileCompressed.h"
#include "FileCsv.h"

namespace smartDescriptor
{
    namespace buffer
    {
        BuildBuffer::BuildBuffer(const size_t minimumLine, const smartDescriptor::readerCsv::ParamFile &paramFile)
                : m_paramFile(paramFile), m_index(0), m_modulo(1)
        {
            size_t numberLine = setModulo(m_paramFile.numberLine, minimumLine);
            m_dataAnalysis = std::unique_ptr<DataAnalysis>(new DataAnalysis(m_paramFile.numberField, numberLine));
            Column<std::string> column(numberLine);
            m_buffer = std::vector<Column<std::string>>(paramFile.numberField, column);
            m_instance = std::vector<size_t>(m_paramFile.numberField, 0);
        }


        DataAnalysis &BuildBuffer::getDataAnalysis(smartDescriptor::readerFile::FileParameters &fileParameters)
        {
            if (fileParameters.getArchive() != smartDescriptor::NO_ARCHIVE)
            {
                auto * file = new  smartDescriptor::readerFile::FileArchive(fileParameters);
                getRecord(file);
                delete file;
            }
            else if (fileParameters.getCompressed() != smartDescriptor::NO_COMPRESSED)
            {
                auto * file= new smartDescriptor::readerFile::FileCompressed (fileParameters);
                getRecord(file);
                delete file;
            }
            else if (fileParameters.getExtension() != smartDescriptor::NO_EXTENSION)
            {
                auto * file= new smartDescriptor::readerFile::FileCsv(fileParameters);
                getRecord(file);
                delete file;
            }
            else
            {
                std::cerr << " Input filename : " << fileParameters.getFilenameInput() << std::endl;
                throw std::runtime_error(" file has not extension ");
            }
            m_dataAnalysis->setConnection();
            return (*m_dataAnalysis);
        }


        bool BuildBuffer::hasHeader()
        {
            return !(m_header == nullptr);
        }

        const smartDescriptor::header::Header &BuildBuffer::getHeader()
        {
            return *m_header;
        }

        size_t BuildBuffer::setModulo(const size_t numberTotalLine, const size_t minimumLine)
        {
            size_t numberLine = minimumLine;
            size_t numberLineWanted = std::max<size_t>(minimumLine, 100) + 1;
            if (numberTotalLine < numberLineWanted)
            {
                m_modulo = 1;
                numberLine = numberTotalLine;
            }
            else
            {
                m_modulo = numberTotalLine / numberLineWanted;
            }
            return numberLine;
        }


        void BuildBuffer::computeSize(const std::vector<std::string> &lineSplit)
        {
            size_t size = 0;
            for (size_t indexField = 0; indexField < m_paramFile.numberField; ++indexField)
            {
                size = lineSplit[indexField].size();
                if (size > 0)
                {
                    m_dataAnalysis->updateFieldSize(indexField, size);
                    m_buffer[indexField].fill(lineSplit[indexField], m_index);
                }
                m_instance[indexField]++;
            }
            if (m_index % m_modulo == 0)
            {
                fillDataAnalysis();
            }
        }


        void BuildBuffer::getStatistics(std::string &statistics)
        {
            statistics = "----------------- statistics build buffer -------------------";
            statistics += "| index field | max size field | instance in % |";
            for (size_t indexField = 0; indexField < m_paramFile.numberField; ++indexField)
            {
                statistics += "  |" + std::to_string(indexField) + "| " +
                              std::to_string((m_instance[indexField] * 100.) / m_index) + " |" +
                              std::to_string(m_dataAnalysis->getMaxFieldSize(indexField)) + "|";
            }
        }


        void BuildBuffer::fillDataAnalysis()
        {
            size_t numberLine = m_index / m_modulo;
            for (size_t indexField = 0; indexField < m_paramFile.numberField; ++indexField)
            {
                while (m_buffer[indexField].getSize() != 0 && m_dataAnalysis->getSize(indexField) != numberLine)
                {
                    m_dataAnalysis->fillBuffer(indexField, m_index, m_buffer[indexField].getEnd());
                    m_buffer[indexField].popBack();
                }
            }
        }
    }
}