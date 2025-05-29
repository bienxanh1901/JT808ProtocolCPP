#ifndef DELETINGAREAROUTE_H
#define DELETINGAREAROUTE_H

#include "MessageBodyBase.h"
#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace JT808::MessageBody {

class DeletingAreaRoute : public MessageBodyBase
{
public:
    DeletingAreaRoute();
    DeletingAreaRoute(const std::vector<uint32_t>& ids);
    void parse(const std::vector<uint8_t>& data) override;
    void parse(const uint8_t* data, int size) override;
    std::vector<uint8_t> package() override;
    bool operator==(const DeletingAreaRoute& other) const;

    void fromJson(const nlohmann::json& data) override;
    nlohmann::json toJson() override;

    std::vector<uint32_t> ids() const;
    void setIds(const std::vector<uint32_t>& newIds);

private:
    std::vector<uint32_t> m_ids;
};

}
#endif // DELETINGAREAROUTE_H
