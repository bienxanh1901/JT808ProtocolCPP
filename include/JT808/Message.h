#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "JT808/MessageBody/MessageBodyBase.h"

namespace JT808 {

/**
 * JT808 Message
 */
class Message
{
public:
    /**
     * @brief EncryptAlgorithms
     * @details The bit 10th-12th in BodyProperties (encrypt field)
     * When all three bits are 0, message body is not encrypted.
     * When bit 10th is 1, message body is encrypted using RSA algorithm
     * Other are reserved.
     */
    enum EncryptAlgorithms
    {
        NoEncryptAlgorithm = 0, // BITSET: 000
        RSAEncryptAlgorithm = 1, // BITSET: 001
    };

    /**
     * @brief MessageBodyTypes
     * @details The bit 13th in BodyProperties (segment field)
     * If this bit is 1, message body is long message,
     * otherwise message body is short message
     */
    enum BodyTypes
    {
        ShortBodyType = 0,
        LongBodyType = 1
    };

    /**
     * @brief PackageEncapsulation
     * @details
     *      fragTotal: Total number of sub messages
     *      fragSN: Message Package Serial Number
     */
    union PackageEncapsulation {
        struct
        {
            uint16_t fragTotal;
            uint16_t fragSN;
        } data;
        uint32_t rawData;
    };

    /**
     * @brief BodyProperties
     * @details
     *      len: Length of Message Body
     *      encrypt: EncryptAlgorithms
     *      segment: MessageBodyTypes
     *      reserve: reserved bits
     */
    union BodyProperties {
        struct
        {
            uint16_t len : 10;
            uint16_t encrypt : 3;
            uint16_t segment : 1;
            uint16_t reserve : 2;
        } bits;
        uint16_t value;
    };

    /**
     * @brief JT808 Message Header
     * @details
     *      msgID: Message ID
     *      bodyProps: BodyProperties
     *      phone: Terminal Phone number
     *      msgSN: Message Serial Number
     *      pkgEncap: PackageEncapsulation
     */
    struct Header
    {
        uint16_t msgID;
        BodyProperties bodyProps;
        std::string phone;
        uint16_t msgSN;
        PackageEncapsulation pkgEncap;
    };

    Message();
    Message(const Header& header, std::unique_ptr<MessageBody::MessageBodyBase> body);

    void parse(const std::vector<uint8_t>& data);
    std::vector<uint8_t> package();
    bool isValid() const;
    Header header() const;
    MessageBody::MessageBodyBase* body() const;
    void setBody(std::unique_ptr<MessageBody::MessageBodyBase> newBody);
    void setBody(MessageBody::MessageBodyBase* newBody);
    void setHeader(const Header& newHeader);

private:
    using MethodPtr = void (Message::*)();
    void validateChecksum(uint8_t checksum);
    bool parseHeader(const std::vector<uint8_t>& data);
    bool parseBody(const std::vector<uint8_t>& data);
    std::vector<uint8_t> packageHeader();
    std::vector<uint8_t> packageBody();

    bool m_isValid = true;
    Header m_header = {0};
    uint8_t m_checksum = 0;
    std::unique_ptr<MessageBody::MessageBodyBase> m_body;
};
}

#endif // MESSAGE_H
