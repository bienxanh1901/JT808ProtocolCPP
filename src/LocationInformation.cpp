#include "JT808/MessageBody/LocationInformation.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/BasicLocationInformation.h"
#include "JT808/MessageBody/ExtraLocationInformation.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <utility>

namespace JT808::MessageBody {

LocationInformation::LocationInformation(BasicLocationInformation basic, ExtraLocationInformation extra)
    : m_basic(std::move(basic))
    , m_extra(std::move(extra))
{
}

bool LocationInformation::operator==(const LocationInformation& other) const
{
    return m_basic == other.m_basic && m_extra == other.m_extra;
}

int LocationInformation::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;

    // basic
    pos = m_basic.parse(data, size);
    // extra
    if (size > pos) {
        pos1 = m_extra.parse(data + pos, size - pos);
        pos += pos1;
    }

    return pos > size ? size : pos;
}

ByteArray LocationInformation::package()
{
    ByteArray result(m_basic.package());
    Utils::append(m_extra.package(), result);

    return result;
}

void LocationInformation::fromJson(const Json& data)
{
    m_basic.fromJson(data["basic"]);
    if (data.contains("extra")) {
        m_extra.fromJson(data["extra"]);
    }
}

Json LocationInformation::toJson()
{
    Json const extra = m_extra.toJson();
    Json result = Json::object({{"basic", m_basic.toJson()}});
    if (!extra.empty()) {
        result["extra"] = extra;
    }

    return result;
}
}
