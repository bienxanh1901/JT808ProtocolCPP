#ifndef TERMINALPROPERTIESQUERYRESPONSE_H
#define TERMINALPROPERTIESQUERYRESPONSE_H

#include "MessageBodyBase.h"
#include "TerminalProperties.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace JT808 {
namespace MessageBody {

/**
 * @brief The TerminalPropertiesQueryResponse class
 */
class TerminalPropertiesQueryResponse : public MessageBodyBase
{
public:
    TerminalPropertiesQueryResponse(const std::vector<uint8_t>& data = {});
    TerminalPropertiesQueryResponse(uint8_t* data, int size);

    void parse() override;
    void package() override;

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
    uint8_t hwVersionLen() const;
    void setHwVersionLen(uint8_t newHwVersionLen);
    std::string hwVersion() const;
    void setHwVersion(const std::string& newHwVersion);
    uint8_t fwVersionLen() const;
    void setFwVersionLen(uint8_t newFwVersionLen);
    std::string fwVersion() const;
    void setFwVersion(const std::string& newFwVersion);
    GNSSProperties gnssProp() const;
    void setGnssProp(const GNSSProperties& newGnssProp);
    CommunicationModuleProperties commProp() const;
    void setCommProp(const CommunicationModuleProperties& newCommProp);

private:
    TerminalType m_type = {0};
    std::vector<uint8_t> m_manufacturer = {};
    std::vector<uint8_t> m_model = {};
    std::vector<uint8_t> m_id = {};
    std::string m_iccid = "";
    uint8_t m_hwVersionLen = 0;
    std::string m_hwVersion = {0};
    uint8_t m_fwVersionLen = 0;
    std::string m_fwVersion = {0};
    GNSSProperties m_gnssProp = {0};
    CommunicationModuleProperties m_commProp = {0};
};

}
}

#endif // TERMINALPROPERTIESQUERYRESPONSE_H
