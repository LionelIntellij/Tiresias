#include <string>
#include <vector>
#include "ReaderCsv.h"

template<class FileType>
ReaderCsv<FileType>::ReaderCsv(const ParamFile &paramFile, FileType *file) :
        m_offset(0), m_file(file), m_numberField(paramFile.numberField), m_numberLine(paramFile.numberLine) {
    boost::escaped_list_separator<char> els(paramFile.escape, paramFile.delimiter, paramFile.quote);
    m_els = els;
}

template<class FileType>
void ReaderCsv<FileType>::get(std::string &line, std::vector<std::string> &record) {
    if (!line.empty() && line[line.size() - 1] == '\r') {
        line.pop_back();
    }
    record.clear();
    Tokenizer tok(line, m_els);
    record.assign(tok.begin(), tok.end());
    m_offset++;
}


template<class FileType>
bool ReaderCsv<FileType>::getRecord(size_t &offset, std::vector<std::string> &record) {
    std::string line;
    m_file->getLineFile(line);
    get(line, record);
    size_t size = record.size();
    while (size != m_numberField && m_file->getLineFile(line)) {
        m_indexToRejected.push_back(m_offset);
        m_sizeToRejected.push_back(size);
        get(line, record);
        size = record.size();
    }
    offset = m_offset;
    return !size == 0;
}


template<class FileType>
void ReaderCsv<FileType>::getStatistics(std::string &statistics) {
    if (m_indexToRejected.empty()) {
        statistics = " ------------- statistics number field --------------";
        size_t index = 0;
        statistics += " index line  | number field";
        for (const size_t &indexRejected : m_indexToRejected) {
            statistics += std::to_string(indexRejected) + " | " + std::to_string(m_sizeToRejected[index]);
            index++;
        }
    }
}


