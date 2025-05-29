#ifndef LOCATIONINFORMATION_H
#define LOCATIONINFORMATION_H

#include <cstdint>
#include <vector>

#include "BasicLocationInformation.h"
#include "ExtraLocationInformation.h"
#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class LocationInformation
{
public:
    LocationInformation() = default;
    LocationInformation(BasicLocationInformation basic, ExtraLocationInformation extra);
    bool operator==(const LocationInformation& other) const;
    int parse(const uint8_t* data, int size);
    std::vector<uint8_t> package();

    void fromJson(const nlohmann::json& data);
    nlohmann::json toJson();

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
