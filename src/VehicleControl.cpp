#include "JT808/MessageBody/VehicleControl.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

VehicleControl::VehicleControl(Flag flag)
    : m_flag(flag)
{
}

void VehicleControl::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void VehicleControl::parse(const uint8_t* data, int /*size*/)
{
    m_flag.value = data[0];

    setIsValid(true);
}

std::vector<uint8_t> VehicleControl::package()
{
    std::vector<uint8_t> result;

    result.push_back(m_flag.value);

    return result;
}

bool VehicleControl::operator==(const VehicleControl& other) const
{
    return m_flag.value == other.m_flag.value;
}

VehicleControl::Flag VehicleControl::flag() const
{
    return m_flag;
}

void VehicleControl::setFlag(const Flag& newFlag)
{
    m_flag = newFlag;
}

}
