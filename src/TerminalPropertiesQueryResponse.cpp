#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/TerminalProperties.h"
#include "JT808/Schema/TerminalPropertiesQueryResponseSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

TerminalPropertiesQueryResponse::TerminalPropertiesQueryResponse()
    : MessageBodyBase(Schema::TerminalPropertiesQueryResponseSchema)
{
}

TerminalPropertiesQueryResponse::TerminalPropertiesQueryResponse(const TerminalType& type, std::string manufacturer,
                                                                 std::string model, std::string id, std::string iccid,
                                                                 std::string hwVersion, std::string fwVersion,
                                                                 const GNSSProperties& gnssProp,
                                                                 const CommunicationModuleProperties& commProp)
    : MessageBodyBase(Schema::TerminalPropertiesQueryResponseSchema)
    , m_type(type)
    , m_manufacturer(std::move(manufacturer))
    , m_model(std::move(model))
    , m_id(std::move(id))
    , m_iccid(std::move(iccid))
    , m_hwVersion(std::move(hwVersion))
    , m_fwVersion(std::move(fwVersion))
    , m_gnssProp(gnssProp)
    , m_commProp(commProp)
{
}

void TerminalPropertiesQueryResponse::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void TerminalPropertiesQueryResponse::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint8_t len = 0;

    // type
    m_type.value = Utils::endianSwap16(data + pos);
    pos += sizeof(m_type);
    // manufacturer
    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    // model
    m_model.assign(data + pos, data + pos + 20);
    Utils::eraseTrailingNull(m_model);
    pos += 20;
    // id
    m_id.assign(data + pos, data + pos + 7);
    Utils::eraseTrailingNull(m_id);
    pos += 7;
    // iccid
    m_iccid = BCD::toString(data + pos, 10);
    pos += 10;
    // hardware version length
    len = data[pos++];
    // hardware version
    m_hwVersion.assign(data + pos, data + pos + len);
    pos += len;
    // firmware version length
    len = data[pos++];
    // firmware version
    m_fwVersion.assign(data + pos, data + pos + len);
    pos += len;
    // gnss props
    m_gnssProp.value = data[pos++];
    // commnuication props
    m_commProp.value = data[pos];

    setIsValid(true);
}

ByteArray TerminalPropertiesQueryResponse::package()
{
    ByteArray result;
    // type
    Utils::appendU16(m_type.value, result);
    // manufacturer
    Utils::append(m_manufacturer, result);
    // model
    Utils::append(m_model, result);
    if (m_model.length() < 20) {
        Utils::appendNull(result, 20 - m_model.length());
    }
    // id
    Utils::append(m_id, result);
    if (m_id.length() < 7) {
        Utils::appendNull(result, 7 - m_id.length());
    }
    // iccid
    Utils::appendBCD(m_iccid, result);
    // hardware version length
    result.push_back(m_hwVersion.length());
    // hardware version
    Utils::append(m_hwVersion, result);
    // firmware version length
    result.push_back(m_fwVersion.length());
    // firmware version
    Utils::append(m_fwVersion, result);
    // gnss props
    result.push_back(m_gnssProp.value);
    // comm props
    result.push_back(m_commProp.value);

    return result;
}

bool TerminalPropertiesQueryResponse::operator==(const TerminalPropertiesQueryResponse& other) const
{
    return m_type.value == other.m_type.value && m_manufacturer == other.m_manufacturer && m_model == other.m_model
        && m_id == other.m_id && m_iccid == other.m_iccid && m_hwVersion == other.m_hwVersion
        && m_fwVersion == other.m_fwVersion && m_gnssProp.value == other.m_gnssProp.value
        && m_commProp.value == other.commProp().value;
}

void TerminalPropertiesQueryResponse::fromJson(const Json& data)
{
    if (validate(data)) {
        m_type.value = data["type"];
        m_manufacturer = data["manufacturer"];
        m_model = data["model"];
        m_id = data["id"];
        m_iccid = data["iccid"];
        m_hwVersion = data["hardware_version"];
        m_fwVersion = data["firmware_version"];
        m_gnssProp.value = data["gnss_prop"];
        m_commProp.value = data["comm_prop"];
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json TerminalPropertiesQueryResponse::toJson()
{
    return {
        {"type", m_type.value},
        {"manufacturer", m_manufacturer},
        {"model", m_model},
        {"id", m_id},
        {"iccid", m_iccid},
        {"hardware_version", m_hwVersion},
        {"firmware_version", m_fwVersion},
        {"gnss_prop", m_gnssProp.value},
        {"comm_prop", m_commProp.value},
    };
}

TerminalType TerminalPropertiesQueryResponse::type() const
{
    return m_type;
}

void TerminalPropertiesQueryResponse::setType(const TerminalType& newType)
{
    m_type = newType;
}

std::string TerminalPropertiesQueryResponse::manufacturer() const
{
    return m_manufacturer;
}

void TerminalPropertiesQueryResponse::setManufacturer(const std::string& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::string TerminalPropertiesQueryResponse::model() const
{
    return m_model;
}

void TerminalPropertiesQueryResponse::setModel(const std::string& newModel)
{
    m_model = newModel;
}

std::string TerminalPropertiesQueryResponse::id() const
{
    return m_id;
}

void TerminalPropertiesQueryResponse::setId(const std::string& newId)
{
    m_id = newId;
}

std::string TerminalPropertiesQueryResponse::iccid() const
{
    return m_iccid;
}

void TerminalPropertiesQueryResponse::setIccid(const std::string& newIccid)
{
    m_iccid = newIccid;
}

std::string TerminalPropertiesQueryResponse::hwVersion() const
{
    return m_hwVersion;
}

void TerminalPropertiesQueryResponse::setHwVersion(const std::string& newHwVersion)
{
    m_hwVersion = newHwVersion;
}

std::string TerminalPropertiesQueryResponse::fwVersion() const
{
    return m_fwVersion;
}

void TerminalPropertiesQueryResponse::setFwVersion(const std::string& newFwVersion)
{
    m_fwVersion = newFwVersion;
}

GNSSProperties TerminalPropertiesQueryResponse::gnssProp() const
{
    return m_gnssProp;
}

void TerminalPropertiesQueryResponse::setGnssProp(const GNSSProperties& newGnssProp)
{
    m_gnssProp = newGnssProp;
}

CommunicationModuleProperties TerminalPropertiesQueryResponse::commProp() const
{
    return m_commProp;
}

void TerminalPropertiesQueryResponse::setCommProp(const CommunicationModuleProperties& newCommProp)
{
    m_commProp = newCommProp;
}

}
