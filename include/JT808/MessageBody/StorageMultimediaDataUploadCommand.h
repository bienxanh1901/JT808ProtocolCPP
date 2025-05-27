#ifndef STORAGEMULTIMEDIADATAUPLOADCOMMAND_H
#define STORAGEMULTIMEDIADATAUPLOADCOMMAND_H

#include "StorageMultimediaDataRetrieval.h"

namespace JT808::MessageBody {

class StorageMultimediaDataUploadCommand : public StorageMultimediaDataRetrieval
{
public:
    StorageMultimediaDataUploadCommand() = default;
    StorageMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event, const std::string& startTime,
                                       const std::string& endTime, uint8_t isDelete);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StorageMultimediaDataUploadCommand& other);

    uint8_t isDelete() const;
    void setIsDelete(uint8_t newIsDelete);

private:
    uint8_t m_isDelete = 0;
};

}
#endif // STORAGEMULTIMEDIADATAUPLOADCOMMAND_H
