#ifndef DELETINGCIRCLEAREA_H
#define DELETINGCIRCLEAREA_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class DeletingCircleArea : public MessageBodyBase
{
public:
    DeletingCircleArea() = default;
    DeletingCircleArea(const std::vector<uint16_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DeletingCircleArea& other);

    uint16_t seq() const;
    void setSeq(uint16_t newSeq);

    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<uint16_t> ids() const;
    void setIds(const std::vector<uint16_t>& newIds);

private:
    uint8_t m_length = 0;
    std::vector<uint16_t> m_ids;
};

}
#endif // DELETINGCIRCLEAREA_H
