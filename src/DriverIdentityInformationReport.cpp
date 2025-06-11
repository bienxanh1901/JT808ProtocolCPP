#include "JT808/MessageBody/DriverIdentityInformationReport.h"
#include "JT808/BCD.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DriverIdentityInformationReportSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <string>
#include <utility>

namespace JT808::MessageBody {

DriverIdentityInformationReport::DriverIdentityInformationReport()
    : MessageBodyBase(Schema::DriverIdentityInformationReportSchema)
{
}

DriverIdentityInformationReport::DriverIdentityInformationReport(Status status, std::string time, ICResult icResult,
                                                                 std::string driverName, std::string certificate,
                                                                 std::string organization, std::string certExpiry)
    : MessageBodyBase(Schema::DriverIdentityInformationReportSchema)
    , m_status(status)
    , m_time(std::move(time))
    , m_icResult(icResult)
    , m_driverName(std::move(driverName))
    , m_certificate(std::move(certificate))
    , m_organization(std::move(organization))
    , m_certExpiry(std::move(certExpiry))
{
}

void DriverIdentityInformationReport::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void DriverIdentityInformationReport::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    uint8_t length = 0;

    // status
    m_status = Status(data[pos++]);
    // time
    m_time = BCD::toString(data + pos, 6);
    pos += 6;
    // result
    m_icResult = ICResult(data[pos++]);

    if (m_icResult == Successful) {
        // driverName
        length = data[pos++];
        m_driverName.assign(data + pos, data + pos + length);
        pos += length;
        // certificate
        m_certificate.assign(data + pos, data + pos + 20);
        Utils::eraseTrailingNull(m_certificate);
        pos += 20;
        // organization
        length = data[pos++];
        m_organization.assign(data + pos, data + pos + length);
        pos += length;
        // certificate expiry
        m_certExpiry = BCD::toString(data + pos, 4);
    }

    setIsValid(true);
}

ByteArray DriverIdentityInformationReport::package()
{
    ByteArray result;

    // status
    result.push_back(m_status);
    // time
    Utils::appendBCD(m_time, result);
    // result
    result.push_back(m_icResult);
    if (m_icResult == Successful) {
        // driverName
        result.push_back(m_driverName.length());
        Utils::append(m_driverName, result);
        // certificate
        Utils::append(m_certificate, result);
        if (m_certificate.length() < 20) {
            Utils::appendNull(result, 20 - m_certificate.length());
        }
        // organization
        result.push_back(m_organization.length());
        Utils::append(m_organization, result);
        // certificate expiry
        Utils::appendBCD(m_certExpiry, result);
    }

    return result;
}

bool DriverIdentityInformationReport::operator==(const DriverIdentityInformationReport& other) const
{
    return m_status == other.m_status && m_time == other.m_time && m_icResult == other.m_icResult
        && m_driverName == other.m_driverName && m_certificate == other.m_certificate
        && m_organization == other.m_organization && m_certExpiry == other.m_certExpiry;
}

void DriverIdentityInformationReport::fromJson(const Json& data)
{
    if (validate(data)) {
        m_status = Status(data["status"]);
        m_time = data["time"];
        m_icResult = ICResult(data["ic_result"]);
        if (m_icResult == Successful) {
            m_driverName = data["driver_name"];
            m_certificate = data["certificate"];
            m_organization = data["organization"];
            m_certExpiry = data["cert_expiry"];
        }

        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DriverIdentityInformationReport::toJson()
{
    Json result({{"status", m_status}, {"time", m_time}, {"ic_result", m_icResult}});

    if (m_icResult == Successful) {
        result["driver_name"] = m_driverName;
        result["certificate"] = m_certificate;
        result["organization"] = m_organization;
        result["cert_expiry"] = m_certExpiry;
    }

    return result;
}

DriverIdentityInformationReport::Status DriverIdentityInformationReport::status() const
{
    return m_status;
}

void DriverIdentityInformationReport::setStatus(Status newStatus)
{
    m_status = newStatus;
}

std::string DriverIdentityInformationReport::time() const
{
    return m_time;
}

void DriverIdentityInformationReport::setTime(const std::string& newTime)
{
    m_time = newTime;
}

DriverIdentityInformationReport::ICResult DriverIdentityInformationReport::icResult() const
{
    return m_icResult;
}

void DriverIdentityInformationReport::setIcResult(ICResult newIcResult)
{
    m_icResult = newIcResult;
}

std::string DriverIdentityInformationReport::driverName() const
{
    return m_driverName;
}

void DriverIdentityInformationReport::setDriverName(const std::string& newDriverName)
{
    m_driverName = newDriverName;
}

std::string DriverIdentityInformationReport::certificate() const
{
    return m_certificate;
}

void DriverIdentityInformationReport::setCertificate(const std::string& newCertificate)
{
    m_certificate = newCertificate;
}

std::string DriverIdentityInformationReport::organization() const
{
    return m_organization;
}

void DriverIdentityInformationReport::setOrganization(const std::string& newOrganization)
{
    m_organization = newOrganization;
}

std::string DriverIdentityInformationReport::certExpiry() const
{
    return m_certExpiry;
}

void DriverIdentityInformationReport::setCertExpiry(const std::string& newCertExpiry)
{
    m_certExpiry = newCertExpiry;
}
}
