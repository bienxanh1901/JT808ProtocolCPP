#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/TerminalParameter.h"
#include "JT808/Utils.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <utility>
#include <vector>

namespace JT808::MessageBody {

TerminalParameterSetting::TerminalParameterSetting()
    : MessageBodyBase({})
{
}

TerminalParameterSetting::TerminalParameterSetting(const nlohmann::json& schema)
    : MessageBodyBase(schema)
{
}

TerminalParameterSetting::TerminalParameterSetting(TerminalParameters params)
    : MessageBodyBase({})
    , m_params(std::move(params))
{
}

TerminalParameterSetting::TerminalParameterSetting(const nlohmann::json& schema, TerminalParameters params)
    : MessageBodyBase(schema)
    , m_params(std::move(params))
{
}

void TerminalParameterSetting::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalParameterSetting::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint32_t id = 0;
    uint8_t len = 0;
    std::vector<uint8_t> value;

    // length
    uint8_t const length = data[pos++];
    // params
    for (int i = 0; i < length; i++) {
        id = Utils::endianSwap32(data + pos);
        pos += sizeof(id);
        len = data[pos++];
        value.assign(data + pos, data + pos + len);
        pos += len;

        m_params[id] = value;
    }

    setIsValid(true);
}

std::vector<uint8_t> TerminalParameterSetting::package()
{
    std::vector<uint8_t> result;
    // length
    result.push_back(m_params.size());
    // params
    for (const auto& item : m_params) {
        Utils::appendU32(item.first, result);
        result.push_back(item.second.size());
        Utils::append(item.second, result);
    }

    return result;
}

bool TerminalParameterSetting::operator==(const TerminalParameterSetting& other) const
{
    return m_params == other.m_params;
}

void TerminalParameterSetting::fromJson(const nlohmann::json& data)
{
    if (validate(data)) {
        if (data["length"] > 0) {
            for (auto& item : data["params"]) {
                m_params[item["id"]] = item["value"].get<std::vector<uint8_t>>();
            }
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

nlohmann::json TerminalParameterSetting::toJson()
{
    nlohmann::json result({{"length", m_params.size()}, {"params", {}}});

    for (auto& param : m_params) {
        result["params"].push_back({{"id", param.first}, {"value", param.second}});
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
