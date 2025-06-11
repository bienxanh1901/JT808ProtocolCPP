#include "JT808/MessageBody/DeletingAreaRoute.h"
#include "JT808/Common.h"
#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/Schema/DeletingAreaRouteSchema.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

DeletingAreaRoute::DeletingAreaRoute()
    : MessageBodyBase(Schema::DeletingAreaRouteSchema)
{
}

DeletingAreaRoute::DeletingAreaRoute(const std::vector<uint32_t>& ids)
    : MessageBodyBase(Schema::DeletingAreaRouteSchema)
    , m_ids(ids)
{
}

void DeletingAreaRoute::parse(const ByteArray& data)
{
    parse(data.data(), data.size());
}

void DeletingAreaRoute::parse(const uint8_t* data, int /*size*/)
{
    int pos = 0;
    // length
    uint8_t const length = data[pos++];
    // ids
    for (int i = 0; i < length; i++) {
        m_ids.push_back(Utils::endianSwap32(data + pos));
        pos += 4;
    }

    setIsValid(true);
}

ByteArray DeletingAreaRoute::package()
{
    ByteArray result;
    // length
    result.push_back(m_ids.size());
    // ids
    for (auto& id : m_ids) {
        Utils::appendU32(id, result);
    }

    return result;
}

bool DeletingAreaRoute::operator==(const DeletingAreaRoute& other) const
{
    return m_ids == other.m_ids;
}

void DeletingAreaRoute::fromJson(const Json& data)
{
    if (validate(data)) {
        if (data["length"] > 0) {
            m_ids = data["ids"].get<std::vector<uint32_t>>();
        }
        setIsValid(true);
    } else {
        setIsValid(false);
    }
}

Json DeletingAreaRoute::toJson()
{
    return {{"length", m_ids.size()}, {"ids", m_ids}};
}

std::vector<uint32_t> DeletingAreaRoute::ids() const
{
    return m_ids;
}

void DeletingAreaRoute::setIds(const std::vector<uint32_t>& newIds)
{
    m_ids = newIds;
}
}
