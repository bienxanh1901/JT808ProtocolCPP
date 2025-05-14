#ifndef TERMINALPROPERTIES_H
#define TERMINALPROPERTIES_H

#include <stdint.h>

namespace JT808 {
namespace MessageBody {

/**
 * @brief TerminalType
 */
typedef union {
    struct
    {
        uint16_t isPassengerVehicle : 1;
        uint16_t isDangerousGoodsVehicle : 1;
        uint16_t isRegularGoodsVehicle : 1;
        uint16_t isRentalCar : 1;
        uint16_t reserved : 2;
        uint16_t isHardDiskVideo : 1;
        uint16_t isSplitedDevice : 1;
        uint16_t reserved2 : 8;
    } bits;
    uint16_t value;
} TerminalType;

typedef union {
    struct
    {
        uint8_t isGPSSupported : 1;
        uint8_t isBDSSupported : 1;
        uint8_t isGLONASSSupported : 1;
        uint8_t isGalileoSupported : 1;
        uint8_t reserved : 4;
    } bits;
    uint8_t value;
} GNSSProperties;

typedef union {
    struct
    {
        uint8_t isGPRSSupported : 1;
        uint8_t isCDMASupported : 1;
        uint8_t isTD_SCDMASupported : 1;
        uint8_t isWCDMASupported : 1;
        uint8_t isCDMA2000Supported : 1;
        uint8_t isTD_LTESupported : 1;
        uint8_t reserved : 1;
        uint8_t isOtherSupported : 1;
    } bits;
    uint8_t value;
} CommunicationModuleProperties;

}
}

#endif // TERMINALPROPERTIES_H
