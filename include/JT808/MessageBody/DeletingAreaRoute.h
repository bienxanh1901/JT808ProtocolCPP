#ifndef DELETINGAREAROUTE_H
#define DELETINGAREAROUTE_H

#include "MessageBodyBase.h"

namespace JT808::MessageBody {

class DeletingAreaRoute : public MessageBodyBase
{
public:
    DeletingAreaRoute() = default;
    DeletingAreaRoute(const std::vector<uint32_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DeletingAreaRoute& other);

    uint8_t length() const;
    void setLength(uint8_t newLength);
    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    uint8_t m_length = 0;
    std::vector<uint32_t> m_ids;
};

}
#endif // DELETINGAREAROUTE_H
