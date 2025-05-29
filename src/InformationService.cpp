#include "JT808/MessageBody/InformationService.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/InformationServiceSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

InformationService::InformationService()
    : MessageBodyBase(Schema::InformationServiceSchema)
{
}

InformationService::InformationService(uint8_t type, std::string info)
    : MessageBodyBase(Schema::InformationServiceSchema)
    , m_type(type)
    , m_info(std::move(info))
{
}

void InformationService::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void InformationService::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint16_t length = 0;
    // type
    m_type = data[pos++];
    // length
    length = Utils::endianSwap16(data + pos);
    pos += sizeof(length);
    // info
    m_info = Utils::gbkDecode(data + pos, length);

    setIsValid(true);
}

std::vector<uint8_t> InformationService::package()
{
    std::vector<uint8_t> result;
    // type
    result.push_back(m_type);
    // length
    Utils::appendU16(m_info.size(), result);
    // info
    Utils::appendGBK(m_info, result);

    return result;
}

bool InformationService::operator==(const InformationService& other) const
{
    return m_type == other.m_type && m_info == other.m_info;
}

void InformationService::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        m_type = data["type"];
        m_info = data["info"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json InformationService::toJson()
{
    return {{"type", m_type}, {"info", m_info}};
}

uint8_t InformationService::type() const
{
    return m_type;
}

void InformationService::setType(uint8_t newType)
{
    m_type = newType;
}

std::string InformationService::info() const
{
    return m_info;
}

void InformationService::setInfo(const std::string& newInfo)
{
    m_info = newInfo;
}

}
