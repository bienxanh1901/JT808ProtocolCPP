#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/MessageBody/SequenceMessageBodyBase.h"
#include "JT808/Utils.h"
#include <cstdint>
#include <vector>

namespace JT808::MessageBody {

GeneralResponse::GeneralResponse(uint16_t seq, uint16_t id, GeneralResponse::ResponseResults result)
    : SequenceMessageBodyBase(seq)
    , m_id(id)
    , m_result(result)
{
}

void GeneralResponse::parse(const std::vector<uint8_t>& data)
{
    parse(data.data(), data.size());
}

void GeneralResponse::parse(const uint8_t* data, int size)
{
    if (size != 5) {
        setIsValid(false);
        return;
    }

    int pos = 2;

    SequenceMessageBodyBase::parse(data, size);
    // id
    m_id = Utils::endianSwap16(data + pos);
    pos += sizeof(m_id);
    // result
    m_result = ResponseResults(data[pos]);

    setIsValid(true);
}

std::vector<uint8_t> GeneralResponse::package()
{
    std::vector<uint8_t> result(SequenceMessageBodyBase::package());

    // id
    Utils::appendU16(m_id, result);
    // result
    result.push_back(m_result);

    setIsValid(true);
    return result;
}

bool GeneralResponse::operator==(const GeneralResponse& other) const
{
    return SequenceMessageBodyBase::operator==(other) && m_id == other.m_id && m_result == other.m_result;
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
