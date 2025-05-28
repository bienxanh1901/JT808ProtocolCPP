#ifndef STOREDMULTIMEDIADATAUPLOADCOMMAND_H
#define STOREDMULTIMEDIADATAUPLOADCOMMAND_H

#include "StoredMultimediaDataRetrieval.h"

namespace JT808::MessageBody {

class StoredMultimediaDataUploadCommand : public StoredMultimediaDataRetrieval
{
public:
    StoredMultimediaDataUploadCommand() = default;
    StoredMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event, const std::string& startTime,
                                      const std::string& endTime, uint8_t isDelete);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StoredMultimediaDataUploadCommand& other) const;

    uint8_t isDelete() const;
    void setIsDelete(uint8_t newIsDelete);

private:
    uint8_t m_isDelete = 0;
};

}
#endif // STOREDMULTIMEDIADATAUPLOADCOMMAND_H
