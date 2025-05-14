#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "JT808/BCD.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

TerminalPropertiesQueryResponse::TerminalPropertiesQueryResponse(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

TerminalPropertiesQueryResponse::TerminalPropertiesQueryResponse(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void TerminalPropertiesQueryResponse::parse()
{
    uint8_t* data = m_rawData.data();
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

    m_isValid = true;
}

void TerminalPropertiesQueryResponse::package()
{
    Utils::U16Array u16Data = {0};

    m_rawData.clear();

    u16Data.value = Utils::endianSwap16(m_type.value);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    m_rawData.insert(m_rawData.end(), m_manufacturer.begin(), m_manufacturer.end());
    m_rawData.insert(m_rawData.end(), m_model.begin(), m_model.end());
    m_rawData.insert(m_rawData.end(), m_id.begin(), m_id.end());

    std::vector<uint8_t> iccid = BCD::fromString(m_iccid);
    m_rawData.insert(m_rawData.end(), iccid.begin(), iccid.end());

    m_rawData.push_back(m_hwVersionLen);
    m_rawData.insert(m_rawData.end(), m_hwVersion.begin(), m_hwVersion.end());

    m_rawData.push_back(m_fwVersionLen);
    m_rawData.insert(m_rawData.end(), m_fwVersion.begin(), m_fwVersion.end());

    m_rawData.push_back(m_gnssProp.value);

    m_rawData.push_back(m_commProp.value);

    m_isValid = true;
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
}
