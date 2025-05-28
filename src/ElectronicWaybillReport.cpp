#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "JT808/MessageBody/ElectronicWaybillReport.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

ElectronicWaybillReport::ElectronicWaybillReport(std::string data)
    : m_data(std::move(data))
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

std::string ElectronicWaybillReport::data() const
{
    return m_data;
}

void ElectronicWaybillReport::setData(const std::string& newData)
{
    m_data = newData;
}

}
