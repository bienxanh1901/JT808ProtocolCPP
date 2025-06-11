#ifndef DELETINGAREAROUTE_H
#define DELETINGAREAROUTE_H

#include "JT808/Common.h"
#include "MessageBodyBase.h"
#include <cstdint>

namespace JT808::MessageBody {

class DeletingAreaRoute : public MessageBodyBase
{
public:
    DeletingAreaRoute();
    DeletingAreaRoute(const std::vector<uint32_t>& ids);
    void parse(const ByteArray& data) override;
    void parse(const uint8_t* data, int size) override;
    ByteArray package() override;
    bool operator==(const DeletingAreaRoute& other) const;

    void fromJson(const Json& data) override;
    Json toJson() override;

    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    std::vector<uint32_t> m_ids;
};

}
#endif // DELETINGAREAROUTE_H
