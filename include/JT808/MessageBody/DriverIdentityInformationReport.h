#ifndef DRIVERIDENTITYINFORMATIONREPORT_H
#define DRIVERIDENTITYINFORMATIONREPORT_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

/**
 * @brief The DrivingRecordDataCollectionCommand class
 */
class DriverIdentityInformationReport : public MessageBodyBase
{
public:
    enum Status : uint8_t
    {
        ICCardAdded = 0x01,
        ICCardRemoved = 0x02,
    };

    enum ICResult : uint8_t
    {
        Successful = 0x00,
        AuthenticationFailed = 0x01,
        CardLocked = 0x02,
        CardRemoved = 0x03,
        DataValidationFailed = 0x04
    };

    DriverIdentityInformationReport() = default;
    DriverIdentityInformationReport(Status status, const std::string& time, ICResult icResult,
                                    const std::string& driverName, const std::string& certificate,
                                    const std::string& organization, const std::string& certExpiry);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DriverIdentityInformationReport& other) const;

    Status status() const;
    void setStatus(Status newStatus);
    std::string time() const;
    void setTime(const std::string& newTime);
    ICResult icResult() const;
    void setIcResult(ICResult newIcResult);
    std::string driverName() const;
    void setDriverName(const std::string& newDriverName);
    std::string certificate() const;
    void setCertificate(const std::string& newCertificate);
    std::string organization() const;
    void setOrganization(const std::string& newOrganization);
    std::string certExpiry() const;
    void setCertExpiry(const std::string& newCertExpiry);

private:
    Status m_status = ICCardAdded;
    std::string m_time;
    ICResult m_icResult = Successful;
    std::string m_driverName;
    std::string m_certificate;
    std::string m_organization;
    std::string m_certExpiry;
};

}

#endif // DRIVERIDENTITYINFORMATIONREPORT_H
