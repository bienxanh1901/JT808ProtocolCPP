#include "JT808/MessageBody/VehicleControl.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/VehicleControlSchema.h"
#include <cstdint>

namespace JT808::MessageBody {

VehicleControl::VehicleControl()
    : MessageBodyBase(Schema::VehicleControlSchema)
{
}

VehicleControl::VehicleControl(Flag flag)
    : MessageBodyBase(Schema::VehicleControlSchema)
    , m_flag(flag)
{
}

void VehicleControl::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void VehicleControl::parse(const uint8_t* data, int /*size*/)
{
    m_flag.value = data[0];

    setIsValid(true);
}

ByteArray VehicleControl::package()
{
    ByteArray result;

    result.push_back(m_flag.value);

    return result;
}

bool VehicleControl::operator==(const VehicleControl& other) const
{
    return m_flag.value == other.m_flag.value;
}

void VehicleControl::fromJson(const Json& data)
{
    if (validate(data)) {
        m_flag.value = data["flag"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json VehicleControl::toJson()
{
    return {{"flag", m_flag.value}};
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
