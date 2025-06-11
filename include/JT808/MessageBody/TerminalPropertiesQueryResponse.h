#ifndef TERMINALPROPERTIESQUERYRESPONSE_H
#define TERMINALPROPERTIESQUERYRESPONSE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "TerminalProperties.h"
#include <cstdint>
#include <string>
namespace JT808::MessageBody {

/**
 * @brief The TerminalPropertiesQueryResponse class
 */
class TerminalPropertiesQueryResponse : public MessageBodyBase
{
public:
    TerminalPropertiesQueryResponse();
    TerminalPropertiesQueryResponse(const TerminalType& type, std::string manufacturer, std::string model,
                                    std::string id, std::string iccid, std::string hwVersion, std::string fwVersion,
                                    const GNSSProperties& gnssProp, const CommunicationModuleProperties& commProp);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const TerminalPropertiesQueryResponse& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    TerminalType type() const;
    void setType(const TerminalType& newType);
    std::string manufacturer() const;
    void setManufacturer(const std::string& newManufacturer);
    std::string model() const;
    void setModel(const std::string& newModel);
    std::string id() const;
    void setId(const std::string& newId);
    std::string iccid() const;
    void setIccid(const std::string& newIccid);
    std::string hwVersion() const;
    void setHwVersion(const std::string& newHwVersion);
    std::string fwVersion() const;
    void setFwVersion(const std::string& newFwVersion);
    GNSSProperties gnssProp() const;
    void setGnssProp(const GNSSProperties& newGnssProp);
    CommunicationModuleProperties commProp() const;
    void setCommProp(const CommunicationModuleProperties& newCommProp);

private:
    TerminalType m_type = {0};
    std::string m_manufacturer;
    std::string m_model;
    std::string m_id;
    std::string m_iccid;
    std::string m_hwVersion;
    std::string m_fwVersion;
    GNSSProperties m_gnssProp = {0};
    CommunicationModuleProperties m_commProp = {0};
};

}

#endif // TERMINALPROPERTIESQUERYRESPONSE_H
