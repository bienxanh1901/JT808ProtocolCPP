#ifndef STOREDMULTIMEDIADATARETRIEVAL_H
#define STOREDMULTIMEDIADATARETRIEVAL_H

#include "MessageBodyBase.h"
#include "Multimedia.h"
#include <cstdint>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class StoredMultimediaDataRetrieval : public MessageBodyBase
{
public:
    StoredMultimediaDataRetrieval();
    StoredMultimediaDataRetrieval(const nlohmann::json& schema);
    StoredMultimediaDataRetrieval(MediaType type, uint8_t channel, EventCode event, std::string startTime,
                                  std::string endTime);
    StoredMultimediaDataRetrieval(const nlohmann::json& schema, MediaType type, uint8_t channel, EventCode event,
                                  std::string startTime, std::string endTime);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const StoredMultimediaDataRetrieval& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

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
