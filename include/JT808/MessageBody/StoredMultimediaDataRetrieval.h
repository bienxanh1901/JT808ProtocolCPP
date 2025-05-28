#ifndef STOREDMULTIMEDIADATARETRIEVAL_H
#define STOREDMULTIMEDIADATARETRIEVAL_H

#include "MessageBodyBase.h"
#include "Multimedia.h"

namespace JT808::MessageBody {

class StoredMultimediaDataRetrieval : public MessageBodyBase
{
public:
    StoredMultimediaDataRetrieval() = default;
    StoredMultimediaDataRetrieval(MediaType type, uint8_t channel, EventCode event, const std::string& startTime,
                                  const std::string& endTime);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StoredMultimediaDataRetrieval& other) const;

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
};

}
#endif // STOREDMULTIMEDIADATARETRIEVAL_H
