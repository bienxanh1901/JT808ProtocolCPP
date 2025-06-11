#ifndef STOREDMULTIMEDIADATAUPLOADCOMMAND_H
#define STOREDMULTIMEDIADATAUPLOADCOMMAND_H

#include "JT808/Common.h"
#include "Multimedia.h"
#include "StoredMultimediaDataRetrieval.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

class StoredMultimediaDataUploadCommand : public StoredMultimediaDataRetrieval
{
public:
    StoredMultimediaDataUploadCommand();
    StoredMultimediaDataUploadCommand(MediaType type, uint8_t channel, EventCode event, const std::string& startTime,
                                      const std::string& endTime, uint8_t isDelete);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const StoredMultimediaDataUploadCommand& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint8_t isDelete() const;
    void setIsDelete(uint8_t newIsDelete);

private:
    uint8_t m_isDelete = 0;
};

}
#endif // STOREDMULTIMEDIADATAUPLOADCOMMAND_H
