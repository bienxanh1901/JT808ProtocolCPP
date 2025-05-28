#ifndef SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMAND_H
#define SINGLESTOREDMULTIMEDIAITEMRETRIEVALUPLOADCOMMAND_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

class SingleStoredMultimediaItemRetrievalUploadCommand : public MessageBodyBase
{
public:
    SingleStoredMultimediaItemRetrievalUploadCommand() = default;
    SingleStoredMultimediaItemRetrievalUploadCommand(uint32_t id, uint8_t isDelete);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const SingleStoredMultimediaItemRetrievalUploadCommand& other) const;

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
