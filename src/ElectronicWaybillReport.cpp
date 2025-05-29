#include "JT808/MessageBody/MessageBodyBase.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <vector>

#include "JT808/MessageBody/ElectronicWaybillReport.h"
#include "JT808/Schema/ElectronicWaybillReportSchema.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

ElectronicWaybillReport::ElectronicWaybillReport()
    : MessageBodyBase(Schema::ElectronicWaybillReportSchema)
{
}

ElectronicWaybillReport::ElectronicWaybillReport(const std::vector<uint8_t>& data)
    : MessageBodyBase(Schema::ElectronicWaybillReportSchema)
    , m_data(data)
{
}

void ElectronicWaybillReport::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void ElectronicWaybillReport::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // lengthconst
    uint32_t const length = Utils::endianSwap32(data + pos);
    pos += sizeof(length);
    // data
    m_data.assign(data + pos, data + pos + length);

    setIsValid(true);
}

std::vector<uint8_t> ElectronicWaybillReport::package()
{
    std::vector<uint8_t> result;
    // length
    Utils::appendU32(m_data.size(), result);
    // data
    Utils::append(m_data, result);

    return result;
}

bool ElectronicWaybillReport::operator==(const ElectronicWaybillReport& other) const
{
    return m_data == other.m_data;
}

void ElectronicWaybillReport::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_data = data["data"].get<std::vector<uint8_t>>();
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json ElectronicWaybillReport::toJson()
{
    return nlohmann::json::object({{"length", m_data.size()}, {"data", m_data}});
}

std::vector<uint8_t> ElectronicWaybillReport::data() const
{
    return m_data;
}

void ElectronicWaybillReport::setData(const std::vector<uint8_t>& newData)
{
    m_data = newData;
}

}
