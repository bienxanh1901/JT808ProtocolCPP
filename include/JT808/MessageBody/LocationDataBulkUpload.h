#ifndef LOCATIONDATABULKUPLOAD_H
#define LOCATIONDATABULKUPLOAD_H

#include "LocationInformation.h"
#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class LocationDataBulkUpload : public MessageBodyBase
{
public:
    enum DataType : uint8_t
    {
        RegularReport = 0,
        BindAreaReport = 1
    };

    LocationDataBulkUpload() = default;
    LocationDataBulkUpload(DataType type, const std::vector<LocationInformation>& locations);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const LocationDataBulkUpload& other) const;

    DataType type() const;
    void setType(DataType newType);

    std::vector<LocationInformation> locations() const;
    void setLocations(const std::vector<LocationInformation>& newLocations);

private:
    DataType m_type = RegularReport;
    std::vector<LocationInformation> m_locations;
};

}
#endif // LOCATIONDATABULKUPLOAD_H
