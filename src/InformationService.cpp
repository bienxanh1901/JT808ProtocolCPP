#include "JT808/MessageBody/InformationService.h"

namespace JT808::MessageBody {

InformationService::InformationService(uint8_t type, const std::string& info)
    : MessageBodyBase()
    , m_type(type)
    , m_length(info.size())
    , m_info(info)
{
}

void InformationService::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void InformationService::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type = data[pos++];
    m_length = Utils::endianSwap16(data + pos);
    pos += sizeof(m_length);
    m_info = Utils::gbkDecode(data + pos, m_length);

    setIsValid(true);
}

std::vector<uint8_t> InformationService::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_type);
    Utils::appendU16(m_length, result);
    Utils::appendGBK(m_info, result);

    return result;
}

bool InformationService::operator==(const InformationService& other)
{
    return m_type == other.m_type && m_length == other.m_length && m_info == other.m_info;
}

uint8_t InformationService::type() const
{
    return m_type;
}

void InformationService::setType(uint8_t newType)
{
    m_type = newType;
}

uint16_t InformationService::length() const
{
    return m_length;
}

void InformationService::setLength(uint16_t newLength)
{
    m_length = newLength;
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
