#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "JT808/Schema/TerminalParameterSettingSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <utility>

namespace JT808::MessageBody {

TerminalParameterSetting::TerminalParameterSetting()
    : MessageBodyBase(Schema::TerminalParameterSettingSchema)
{
}

TerminalParameterSetting::TerminalParameterSetting(const Json& schema)
    : MessageBodyBase(schema)
{
}

TerminalParameterSetting::TerminalParameterSetting(TerminalParameters params)
    : MessageBodyBase(Schema::TerminalParameterSettingSchema)
    , m_params(std::move(params))
{
}

TerminalParameterSetting::TerminalParameterSetting(const Json& schema, TerminalParameters params)
    : MessageBodyBase(schema)
    , m_params(std::move(params))
{
}

void TerminalParameterSetting::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterSetting::parse(const uint8_t* data, int size)
{
    int pos = 0;
    int pos1 = 0;
    // length
    uint8_t const length = data[pos++];
    // params
    for (int i = 0; i < length; i++) {
        TerminalParameter param = {0};
        pos1 = param.parse(data + pos, size);
        m_params.push_back(param);
        pos += pos1;
    }

    setIsValid(true);
}

ByteArray TerminalParameterSetting::package()
{
    ByteArray result;
    // length
    result.push_back(m_params.size());
    // params
    for (auto& item : m_params) {
        Utils::append(item.package(), result);
    }

    return result;
}

bool TerminalParameterSetting::operator==(const TerminalParameterSetting& other) const
{
    return m_params == other.m_params;
}

void TerminalParameterSetting::fromJson(const Json& data)
{
    if (validate(data)) {
        if (data["length"] > 0) {
            for (auto& item : data["params"]) {
                TerminalParameter param = {0};
                param.fromJson(item);
                m_params.push_back(param);
            }
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalParameterSetting::toJson()
{
    Json result({{"length", m_params.size()}, {"params", {}}});

    for (auto& item : m_params) {
        result["params"].push_back(item.toJson());
    }

    return result;
}

TerminalParameters TerminalParameterSetting::params() const
{
    return m_params;
}

void TerminalParameterSetting::setParams(const TerminalParameters& newParams)
{
    m_params = newParams;
}

}
