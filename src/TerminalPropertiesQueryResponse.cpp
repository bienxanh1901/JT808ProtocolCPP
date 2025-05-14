#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808::MessageBody {

TerminalPropertiesQueryResponse::TerminalPropertiesQueryResponse(
    const TerminalType& type, const std::vector<uint8_t>& manufacturer, const std::vector<uint8_t>& model,
    const std::vector<uint8_t>& id, const std::string& iccid, const std::string& hwVersion,
    const std::string& fwVersion, const GNSSProperties& gnssProp, const CommunicationModuleProperties& commProp)
    : MessageBodyBase()
    , m_type(type)
    , m_manufacturer(manufacturer)
    , m_model(model)
    , m_id(id)
    , m_iccid(iccid)
    , m_hwVersionLen(hwVersion.length())
    , m_hwVersion(hwVersion)
    , m_fwVersionLen(fwVersion.length())
    , m_fwVersion(fwVersion)
    , m_gnssProp(gnssProp)
    , m_commProp(commProp)
{
}

void TerminalPropertiesQueryResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void TerminalPropertiesQueryResponse::parse(const uint8_t* data, int size)
{
    int pos = 0;

    m_type.value = Utils::endianSwap16(data + pos);
    pos += sizeof(m_type);

    m_manufacturer.assign(data + pos, data + pos + 5);
    pos += 5;
    m_model.assign(data + pos, data + pos + 20);
    pos += 20;
    m_id.assign(data + pos, data + pos + 7);
    pos += 7;

    std::vector<uint8_t> iccid(data + pos, data + pos + 10);
    m_iccid = BCD::toString(iccid);
    pos += 10;

    m_hwVersionLen = data[pos++];
    m_hwVersion.assign(data + pos, data + pos + m_hwVersionLen);
    pos += m_hwVersionLen;

    m_fwVersionLen = data[pos++];
    m_fwVersion.assign(data + pos, data + pos + m_fwVersionLen);
    pos += m_fwVersionLen;

    m_gnssProp.value = data[pos++];
    m_commProp.value = data[pos];

    setIsValid(true);
}

std::vector<uint8_t> TerminalPropertiesQueryResponse::package()
{
    std::vector<uint8_t> result;

    Utils::appendU16(m_type.value, result);
    result.insert(result.end(), m_manufacturer.begin(), m_manufacturer.end());
    result.insert(result.end(), m_model.begin(), m_model.end());
    result.insert(result.end(), m_id.begin(), m_id.end());
    Utils::appendBCD(m_iccid, result);
    result.push_back(m_hwVersionLen);
    result.insert(result.end(), m_hwVersion.begin(), m_hwVersion.end());
    result.push_back(m_fwVersionLen);
    result.insert(result.end(), m_fwVersion.begin(), m_fwVersion.end());
    result.push_back(m_gnssProp.value);
    result.push_back(m_commProp.value);

    return result;
}

bool TerminalPropertiesQueryResponse::operator==(const TerminalPropertiesQueryResponse& other)
{
    return m_type.value == other.m_type.value && m_manufacturer == other.m_manufacturer && m_model == other.m_model
        && m_id == other.m_id && m_iccid == other.m_iccid && m_hwVersionLen == other.m_hwVersionLen
        && m_hwVersion == other.m_hwVersion && m_fwVersionLen == other.m_fwVersionLen
        && m_fwVersion == other.m_fwVersion && m_gnssProp.value == other.m_gnssProp.value
        && m_commProp.value == other.commProp().value;
}

TerminalType TerminalPropertiesQueryResponse::type() const
{
    return m_type;
}

void TerminalPropertiesQueryResponse::setType(const TerminalType& newType)
{
    m_type = newType;
}

std::vector<uint8_t> TerminalPropertiesQueryResponse::manufacturer() const
{
    return m_manufacturer;
}

void TerminalPropertiesQueryResponse::setManufacturer(const std::vector<uint8_t>& newManufacturer)
{
    m_manufacturer = newManufacturer;
}

std::vector<uint8_t> TerminalPropertiesQueryResponse::model() const
{
    return m_model;
}

void TerminalPropertiesQueryResponse::setModel(const std::vector<uint8_t>& newModel)
{
    m_model = newModel;
}

std::vector<uint8_t> TerminalPropertiesQueryResponse::id() const
{
    return m_id;
}

void TerminalPropertiesQueryResponse::setId(const std::vector<uint8_t>& newId)
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

uint8_t TerminalPropertiesQueryResponse::hwVersionLen() const
{
    return m_hwVersionLen;
}

void TerminalPropertiesQueryResponse::setHwVersionLen(uint8_t newHwVersionLen)
{
    m_hwVersionLen = newHwVersionLen;
}

std::string TerminalPropertiesQueryResponse::hwVersion() const
{
    return m_hwVersion;
}

void TerminalPropertiesQueryResponse::setHwVersion(const std::string& newHwVersion)
{
    m_hwVersion = newHwVersion;
}

uint8_t TerminalPropertiesQueryResponse::fwVersionLen() const
{
    return m_fwVersionLen;
}

void TerminalPropertiesQueryResponse::setFwVersionLen(uint8_t newFwVersionLen)
{
    m_fwVersionLen = newFwVersionLen;
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
