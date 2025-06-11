#ifndef LOCATIONINFORMATION_H
#define LOCATIONINFORMATION_H

#include <cstdint>

#include "BasicLocationInformation.h"
#include "ExtraLocationInformation.h"
#include "JT808/Common.h"

namespace JT808::MessageBody {

class LocationInformation
{
public:
    LocationInformation() = default;
    LocationInformation(BasicLocationInformation basic, ExtraLocationInformation extra);
    bool operator==(const LocationInformation& other) const;
    int parse(const uint8_t* data, int size);
    ByteArray package();

    void fromJson(const Json& data);
    Json toJson();

    BasicLocationInformation basic() const;
    void setBasic(const BasicLocationInformation& newBasic);
    ExtraLocationInformation extra() const;
    void setExtra(const ExtraLocationInformation& newExtra);

private:
    BasicLocationInformation m_basic;
    ExtraLocationInformation m_extra;
};

}
#endif // LOCATIONINFORMATION_H
