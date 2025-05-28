#include "JT808/MessageBody/InformationServiceCancel.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

InformationServiceCancel::InformationServiceCancel(uint8_t id, uint8_t flag)
    : m_id(id)
    , m_flag(flag)
{
}

void InformationServiceCancel::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void InformationServiceCancel::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;

    m_id = data[pos++];
    m_flag = data[pos];

    setIsValid(true);
}

std::vector<uint8_t> InformationServiceCancel::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_id);
    result.push_back(m_flag);

    return result;
}

bool InformationServiceCancel::operator==(const InformationServiceCancel& other) const
{
    return m_flag == other.m_flag && m_id == other.m_id;
}

uint8_t InformationServiceCancel::id() const
{
    return m_id;
}

void InformationServiceCancel::setId(uint8_t newId)
{
    m_id = newId;
}

uint8_t InformationServiceCancel::flag() const
{
    return m_flag;
}

void InformationServiceCancel::setFlag(uint8_t newFlag)
{
    m_flag = newFlag;
}

}
