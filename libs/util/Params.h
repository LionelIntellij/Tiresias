#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

namespace smartDescriptor {

    struct ParamsDelimiter {
        std::vector<std::string> delimiters;
        double threshold;
    };

    class Params {

    public:
        Params(const std::string &filenameConfig);

        ParamsDelimiter &getParamsDelimiter();

        double getThresholdHeader();

        int getMinimumLine();

    private:
        boost::property_tree::ptree m_treeParams;

    };
}
#endif