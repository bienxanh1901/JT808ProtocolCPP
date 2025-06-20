#ifndef STOREDMULTIMEDIADATAUPLOADCOMMAND_H
#define STOREDMULTIMEDIADATAUPLOADCOMMAND_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <string>

namespace JT808::MessageBody {

class StoredMultimediaDataUploadCommand : public MessageBodyBase
{
public:
    StoredMultimediaDataUploadCommand();
    StoredMultimediaDataUploadCommand(const uint8_t* data, int size);
    StoredMultimediaDataUploadCommand(const Json& data);
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

    MediaType type() const;
    void setType(MediaType newType);
    uint8_t channel() const;
    void setChannel(uint8_t newChannel);
    EventCode event() const;
    void setEvent(EventCode newEvent);
    std::string startTime() const;
    void setStartTime(const std::string& newStartTime);
    std::string endTime() const;
    void setEndTime(const std::string& newEndTime);

private:
    MediaType m_type = ImageType;
    uint8_t m_channel = 0;
    EventCode m_event = PlaformCommand;
    std::string m_startTime;
    std::string m_endTime;
    uint8_t m_isDelete = 0;
};

}
#endif // STOREDMULTIMEDIADATAUPLOADCOMMAND_H
