#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "Utils.h"

namespace smartDescriptor
{
    struct DescriptorField
    {
        DescriptorField(const size_t position, const FieldFlags field) : position(position), field(field), likelihood(
                0.0), unlikelihood(0.0), fieldNumber(0)
        {
        }

        size_t position;
        FieldFlags field;
        double likelihood;
        double unlikelihood;
        int fieldNumber;
    };

    class Descriptor
    {
    public:
        Descriptor();

        void createDescriptor();

        void addDescriptor(const DescriptorField &descriptorField);

    private:

        size_t m_numberField;

    };
}

#endif