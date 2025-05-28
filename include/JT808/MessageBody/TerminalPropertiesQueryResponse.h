#ifndef TERMINALPROPERTIESQUERYRESPONSE_H
#define TERMINALPROPERTIESQUERYRESPONSE_H

#include "MessageBodyBase.h"
#include "TerminalProperties.h"

namespace JT808::MessageBody {

/**
 * @brief The TerminalPropertiesQueryResponse class
 */
class TerminalPropertiesQueryResponse : public MessageBodyBase
{
public:
    TerminalPropertiesQueryResponse() = default;
    TerminalPropertiesQueryResponse(const TerminalType& type, const std::vector<uint8_t>& manufacturer,
                                    const std::vector<uint8_t>& model, const std::vector<uint8_t>& id,
                                    const std::string& iccid, const std::string& hwVersion,
                                    const std::string& fwVersion, const GNSSProperties& gnssProp,
                                    const CommunicationModuleProperties& commProp);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const TerminalPropertiesQueryResponse& other) const;

    TerminalType type() const;
    void setType(const TerminalType& newType);
    std::vector<uint8_t> manufacturer() const;
    void setManufacturer(const std::vector<uint8_t>& newManufacturer);
    std::vector<uint8_t> model() const;
    void setModel(const std::vector<uint8_t>& newModel);
    std::vector<uint8_t> id() const;
    void setId(const std::vector<uint8_t>& newId);
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
    std::vector<uint8_t> m_manufacturer;
    std::vector<uint8_t> m_model;
    std::vector<uint8_t> m_id;
    std::string m_iccid;
    std::string m_hwVersion;
    std::string m_fwVersion;
    GNSSProperties m_gnssProp = {0};
    CommunicationModuleProperties m_commProp = {0};
};

}

#endif // TERMINALPROPERTIESQUERYRESPONSE_H
