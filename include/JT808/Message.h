#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include "JT808/MessageBody/MessageBodyBase.h"
#include "JT808/MessageIds.h"

namespace JT808 {

/**
 * JT808 Message
 */
class Message
{
public:
    /**
     * @brief ProtocolEscapeFlags
     */
    typedef enum
    {
        ProtocolSign = 0x7E,
        ProtocolEscape = 0x7D,
        ProtocolEscapeSign = 0x02,
        ProtocolEscapeEscape = 0x01,
    } ProtocolEscapeFlags;

    /**
     * @brief EncryptAlgorithms
     * @details The bit 10th-12th in BodyProperties (encrypt field)
     * When all three bits are 0, message body is not encrypted.
     * When bit 10th is 1, message body is encrypted using RSA algorithm
     * Other are reserved.
     */
    typedef enum
    {
        NoEncryptAlgorithm = 0, // BITSET: 000
        RSAEncryptAlgorithm = 1, // BITSET: 001
    } EncryptAlgorithms;

    /**
     * @brief MessageBodyTypes
     * @details The bit 13th in BodyProperties (segment field)
     * If this bit is 1, message body is long message,
     * otherwise message body is short message
     */
    typedef enum
    {
        ShortBodyType = 0,
        LongBodyType = 1
    } BodyTypes;

    /**
     * @brief PackageEncapsulation
     * @details
     *      fragTotal: Total number of sub messages
     *      fragSN: Message Package Serial Number
     */
    typedef union {
        struct
        {
            uint16_t fragTotal;
            uint16_t fragSN;
        } data;
        uint32_t rawData;
    } PackageEncapsulation;

    /**
     * @brief BodyProperties
     * @details
     *      len: Length of Message Body
     *      encrypt: EncryptAlgorithms
     *      segment: MessageBodyTypes
     *      reserve: reserved bits
     */
    typedef union {
        struct
        {
            uint16_t len : 10;
            uint16_t encrypt : 3;
            uint16_t segment : 1;
            uint16_t reserve : 2;
        } bits;
        uint16_t value;
    } BodyProperties;

    /**
     * @brief JT808 Message Header
     * @details
     *      msgID: Message ID
     *      bodyProps: BodyProperties
     *      phone: Terminal Phone number
     *      msgSN: Message Serial Number
     *      pkgEncap: PackageEncapsulation
     */
    typedef struct
    {
        uint16_t msgID;
        BodyProperties bodyProps;
        std::string phone;
        uint16_t msgSN;
        PackageEncapsulation pkgEncap;
    } Header;

    Message(const std::vector<uint8_t>& data = {});

    void parse();
    void package();

    bool isValid() const;

    Header header() const;

    MessageBody::MessageBodyBase* body() const;

    std::vector<uint8_t> rawData() const;
    void setRawData(const std::vector<uint8_t>& newRawData);

    void setBody(std::unique_ptr<MessageBody::MessageBodyBase> newBody);
    void setBody(MessageIds id, const std::vector<uint8_t>& rawBodyData);
    void setBody(MessageBody::MessageBodyBase* newBody);

    void setId(MessageIds id);
    MessageIds id();

    void setHeader(const Header& newHeader);

private:
    void escape();
    std::vector<uint8_t> reverseEscape(const std::vector<uint8_t>& data);

    void calculateChecksum(uint8_t* data, int len);
    void validateChecksum(uint8_t checksum);

    bool parseHeader(const std::vector<uint8_t>& data);
    bool parseBody(const std::vector<uint8_t>& data);

    bool packageHeader();
    bool packageBody();

    std::vector<uint8_t> m_rawData;
    bool m_isValid = true;
    Header m_header = {0};
    uint8_t m_checksum = 0;
    std::unique_ptr<MessageBody::MessageBodyBase> m_body;
};
}

#endif // MESSAGE_H
