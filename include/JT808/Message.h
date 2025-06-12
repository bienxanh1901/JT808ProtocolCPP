#ifndef MESSAGE_H
#define MESSAGE_H

#include "Common.h"
#include "MessageIds.h"
#include <cstdint>
#include <memory>
#include <string>

#include "MessageBody/MessageBodyBase.h"

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
    enum EncryptAlgorithms : uint8_t
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
    enum BodyTypes : uint8_t
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
        uint32_t rawData = 0;
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
        uint16_t value = 0;
    };

    /**
     * @brief JT808 Message Header
     * @details
     *      id: Message ID
     *      bodyProps: BodyProperties
     *      phone: Terminal Phone number
     *      seq: Message Serial Number
     *      pkgEncap: PackageEncapsulation
     */
    struct Header
    {
        MessageIds id = PlatformGeneralResponseMsgId;
        BodyProperties bodyProps = {0};
        std::string phone;
        uint16_t seq = 0;
        PackageEncapsulation pkgEncap = {0};

        bool operator==(const Header& other) const;
        int parse(const uint8_t* data, int size);
        ByteArray package() const;

        void fromJson(const Json& data);
        Json toJson();
    };

    Message();
    Message(Header header, std::unique_ptr<MessageBody::MessageBodyBase> body);

    MessageIds id();
    void setId(MessageIds id);

    void fromJson(const Json& data);
    Json toJson();

    void parse(const ByteArray& data);
    ByteArray package();
    bool isValid() const;
    Header header() const;
    MessageBody::MessageBodyBase* body() const;
    void setBody(std::unique_ptr<MessageBody::MessageBodyBase> newBody);
    void setBody(MessageBody::MessageBodyBase* newBody);
    void setHeader(const Header& newHeader);

private:
    using MethodPtr = void (Message::*)();
    void validateChecksum(uint8_t checksum);
    bool parseHeader(const ByteArray& data);
    bool parseBody(const ByteArray& data);
    bool validateJson(const Json& data);
    ByteArray packageHeader();
    ByteArray packageBody();

    bool m_isValid = true;
    Header m_header;
    uint8_t m_checksum = 0;
    std::unique_ptr<MessageBody::MessageBodyBase> m_body;
    JsonValidator m_validator;
};
}

#endif // MESSAGE_H
