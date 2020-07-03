#include <Params.h>

using namespace std;

smartDescriptor::Params::Params(const std::string &filenameConfig) {
    ifstream fileConfig(filenameConfig);
    boost::property_tree::read_json(fileConfig, m_treeParams);
    fileConfig.close();
}

smartDescriptor::ParamsDelimiter &smartDescriptor::Params::getParamsDelimiter() {
    ParamsDelimiter paramsDelimiter;
    paramsDelimiter.threshold = m_treeParams.get<double>("analysisDelimiter.threshold");
    for (boost::property_tree::ptree::value_type &delims : m_treeParams.get_child("analysisDelimiter.delimiters")) {
        paramsDelimiter.delimiters.push_back(delims.second.data());
    }
    return paramsDelimiter;
}

int smartDescriptor::Params::getMinimumLine(){
    return m_treeParams.get<int>("minimumLine");
}

double smartDescriptor::Params::getThresholdHeader() {
    return m_treeParams.get<double>("thresholdHeader");
}