#ifndef SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMAND_H
#define SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMAND_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class SingleStoredMultimediaItemRetrievalUploadCommand : public MessageBodyBase
{
public:
    SingleStoredMultimediaItemRetrievalUploadCommand();
    SingleStoredMultimediaItemRetrievalUploadCommand(uint32_t id, uint8_t isDelete);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const SingleStoredMultimediaItemRetrievalUploadCommand& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    uint32_t id() const;
    void setId(uint32_t newId);
    uint8_t isDelete() const;
    void setIsDelete(uint8_t newIsDelete);

private:
    uint32_t m_id = 0;
    uint8_t m_isDelete = 0;
};

}
#endif // SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMAND_H
