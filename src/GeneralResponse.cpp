#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/Utils.h"

namespace JT808 {
namespace MessageBody {

GeneralResponse::GeneralResponse(const std::vector<uint8_t>& data)
    : MessageBodyBase(data)
{
}

GeneralResponse::GeneralResponse(uint8_t* data, int size)
    : MessageBodyBase(data, size)
{
}

void GeneralResponse::parse()
{
    if (m_rawData.size() != m_expectedSize) {
        return;
    }

    uint8_t* data = m_rawData.data();
    int pos = 0;

    m_seq = Utils::endianSwap16(data + pos);
    pos += sizeof(m_seq);
    m_id = Utils::endianSwap16(data + pos);
    pos += sizeof(m_id);
    m_result = ResponseResults(data[pos]);
    m_isValid = true;
}

void GeneralResponse::package()
{
    Utils::U16Array u16Data = {0};

    m_rawData.clear();

    // seq
    u16Data.value = Utils::endianSwap16(m_seq);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    // seq
    u16Data.value = Utils::endianSwap16(m_id);
    m_rawData.insert(m_rawData.end(), u16Data.array, u16Data.array + sizeof(u16Data));

    // result
    m_rawData.push_back(m_result);

    m_isValid = true;
}

uint16_t GeneralResponse::seq() const
{
    return m_seq;
}

void GeneralResponse::setSeq(uint16_t newSeq)
{
    m_seq = newSeq;
}

uint16_t GeneralResponse::id() const
{
    return m_id;
}

void GeneralResponse::setId(uint16_t newId)
{
    m_id = newId;
}

GeneralResponse::ResponseResults GeneralResponse::result() const
{
    return m_result;
}

void GeneralResponse::setResult(ResponseResults newResult)
{
    m_result = newResult;
}

}
}
