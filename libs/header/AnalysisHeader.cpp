#include <iostream>
#include "AnalysisHeader.h"
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace smartDescriptor {
    namespace header {
        AnalysisHeader::AnalysisHeader(const Header & header,
                                       const std::vector<FieldFlags> &fieldsFlags):m_header(header),
                                                                                   m_numberField(m_header.getSize()){
            boost::property_tree::ptree treeClassifier;
            std::string filenameClassifier = pathFile("SMART_DESCRIPTOR_DICO") + "/" + "DicoHeader.json";
            boost::property_tree::read_json(filenameClassifier, treeClassifier);
            for (const FieldFlags &fieldFlag :fieldsFlags) {
                Classifier classifier(fieldFlag);
                for (boost::property_tree::ptree::value_type &head : treeClassifier.get_child(field.at(fieldFlag))) {
                    classifier.fill(head.second.data());
                }
                classifier.match(m_header);
                m_classifierHeader.push_back(classifier);
            }
        }

        void AnalysisHeader::decisionHeader(std::vector<DescriptorHeader> &descriptor) {
            for (Classifier &classifier :m_classifierHeader) {
                std::vector<size_t> position(classifier.getPosition());
                if (position.size() == 1) {
                    DescriptorHeader descriptorHeader(classifier.getField(), *position.begin());
                    descriptor.push_back(descriptorHeader);
                } else if (position.size() > 1) {
                    multiField(classifier, descriptor);
                } else {
                    m_fieldNoFound.push_back(classifier.getField());
                }
            }
        }

        void AnalysisHeader::multiField(Classifier &classifier,
                                        std::vector<DescriptorHeader> &descriptor) {
            FieldFlags fieldFlags = classifier.getField();
            if (fieldFlags != smartDescriptor::PHONE_FIX &&
                fieldFlags != smartDescriptor::EMAIL &&
                fieldFlags != smartDescriptor::PHONE_MOB &&
                fieldFlags != smartDescriptor::PHONE) {
                m_fieldNoFound.push_back(fieldFlags);
            } else {
                std::vector<size_t> HasDigit;
                int fieldNumber = 0;
                std::vector<size_t> positionField(classifier.getPosition());
                for (const size_t position : positionField) {
                    if (m_header.getDigit(position) != 0) {
                        HasDigit.push_back(position);
                    } else {
                        DescriptorHeader descriptorHeader(fieldFlags, position, fieldNumber);
                        descriptor.push_back(descriptorHeader);
                        fieldNumber++;
                    }
                }
                if (!HasDigit.empty()) {
                    affectFieldDigit(fieldFlags, HasDigit, fieldNumber, descriptor);
                }
            }
        }


        void AnalysisHeader::affectFieldDigit(const FieldFlags fieldFlags,
                                              const std::vector<size_t> &HasDigit,
                                              int fieldNumber, std::vector<DescriptorHeader> &descriptor) {
            std::vector<size_t> positionSorted(HasDigit.size());
            size_t position(0);
            std::generate(begin(positionSorted), end(positionSorted), [&] { return position++; });
            std::sort(begin(positionSorted), end(positionSorted), [&](int positionReferent, int positionCompared) {
                return m_header.getDigit(HasDigit[positionReferent])
                       < m_header.getDigit(HasDigit[positionCompared]);
            });
            for (const size_t index : positionSorted) {
                DescriptorHeader descriptorHeader(fieldFlags, HasDigit[index], fieldNumber);
                descriptor.push_back(descriptorHeader);
                fieldNumber++;
            }
        }


        void AnalysisHeader::getStatistics(std::string &statistics) {
            statistics = "------------------  Statistics header  ------------------------\n";
            statistics += "name of field  :  position of field  :  instance of field\n";
            for (const DescriptorHeader &descriptor : m_descriptor) {
                statistics += smartDescriptor::field.at(descriptor.field) + " : " +
                        std::to_string(descriptor.position);
                if (descriptor.instance > 0) {
                    statistics += " : " + std::to_string(descriptor.instance) + "\n";
                } else {
                    statistics += "\n";
                }
            }
        }

        const std::vector<smartDescriptor::FieldFlags> &AnalysisHeader::getFieldNoFound() {
            return m_fieldNoFound;
        }
    }
}