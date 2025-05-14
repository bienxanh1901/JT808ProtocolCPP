#ifndef MESSAGEIDS_H
#define MESSAGEIDS_H

namespace JT808 {
typedef enum
{
    // Terminal
    TerminalGeneralResponse = 0x0001,
    TerminalHeartBeat = 0x0002,
    TerminalLogout = 0x0003,
    TerminalRegistration = 0x0100,
    TerminalAuthentication = 0x0102,
    TerminalParameterQueryResponse = 0x0104,
    TerminalPropertiesQueryResponse = 0x0107,
    TerminalUpgradePackageResult = 0x0108,
    LocationInformationReport = 0x0200,
    LocationInformationQueryResponse = 0x0201,
    // Platform
    PlatformGeneralResponse = 0x8001,
    SubPackageRetransmissionRequest = 0x8003,
    TerminalRegistrationResponse = 0x8100,
    TerminalParameterSetting = 0x8103,
    TerminalParameterQuery = 0x8104,
    TerminalControl = 0x8105,
    TerminalSpecificParameterQuery = 0x8106,
    TerminalPropertiesQuery = 0x8107,
    TerminalUpgradePackage = 0x8108,
    LocationInformationQuery = 0x8201,
    TemporaryLocationTrackingControl = 0x8202,
    ManualAlarmConfirmation = 0x8203
} MessageIds;
}
#endif // MESSAGEIDS_H
