#ifndef MESSAGEIDS_H
#define MESSAGEIDS_H

#include <cstdint>

namespace JT808 {
enum MessageIds : uint16_t
{
    // Terminal
    TerminalGeneralResponseMsgId = 0x0001,
    TerminalHeartBeatMsgId = 0x0002,
    TerminalLogoutMsgId = 0x0003,
    TerminalRegistrationMsgId = 0x0100,
    TerminalAuthenticationMsgId = 0x0102,
    TerminalParameterQueryResponseMsgId = 0x0104,
    TerminalPropertiesQueryResponseMsgId = 0x0107,
    TerminalUpgradePackageResultMsgId = 0x0108,
    LocationInformationReportMsgId = 0x0200,
    LocationInformationQueryResponseMsgId = 0x0201,
    EventReportMsgId = 0x0301,
    QuestionResponseMsgId = 0x0302,
    InformationServiceCancelMsgId = 0x0303,
    VehicleControlResponseMsgId = 0x0500,
    DrivingRecordDataUploadMsgId = 0x0700,
    ElectronicWaybillReportMsgId = 0x0701,
    DriverIdentityInformationReportMsgId = 0x0702,
    LocationDataBulkUploadMsgId = 0x0704,
    CANBusDataUploadMsgId = 0x0705,
    MultimediaEventInformationUploadMsgId = 0x0800,
    MultimediaDataUploadMsgId = 0x0801,
    StorageMultimediaDataRetrievalResponseMsgId = 0x0802,
    ImmediateCameraCaptureCommandResponseMsgId = 0x0805,
    // Platform
    PlatformGeneralResponseMsgId = 0x8001,
    SubPackageRetransmissionRequestMsgId = 0x8003,
    TerminalRegistrationResponseMsgId = 0x8100,
    TerminalParameterSettingMsgId = 0x8103,
    TerminalParameterQueryMsgId = 0x8104,
    TerminalControlMsgId = 0x8105,
    TerminalSpecificParameterQueryMsgId = 0x8106,
    TerminalPropertiesQueryMsgId = 0x8107,
    TerminalUpgradePackageMsgId = 0x8108,
    LocationInformationQueryMsgId = 0x8201,
    TemporaryLocationTrackingControlMsgId = 0x8202,
    ManualAlarmConfirmationMsgId = 0x8203,
    TextMessageDispatchMsgId = 0x8300,
    EventSettingMsgId = 0x8301,
    QuestionDispatchMsgId = 0x8302,
    InformationServiceMenuSettingMsgId = 0x8303,
    InformationServiceMsgId = 0x8304,
    CallbackPhoneMsgId = 0x8400,
    PhoneBookSettingMsgId = 0x8401,
    VehicleControlMsgId = 0x8500,
    SettingCircularAreaMsgId = 0x8600,
    DeletingCircularAreaMsgId = 0x8601,
    SettingRectangularAreaMsgId = 0x8602,
    DeletingRectangularAreaMsgId = 0x8603,
    SettingPolygonAreaMsgId = 0x8604,
    DeletingPolygonAreaMsgId = 0x8605,
    SettingRouteMsgId = 0x8606,
    DeletingRouteMsgId = 0x8607,
    DrivingRecordDataCollectionCommandMsgId = 0x8700,
    DrivingRecordParameterCommandMsgId = 0x8701,
    DriverIdentityInformationRequestMsgId = 0x8702,
    MultimediaDataUploadResponseMsgId = 0x8800,
    ImmediateCameraCaptureCommandMsgId = 0x8801,
    StorageMultimediaDataRetrievalMsgId = 0x8802,
    StorageMultimediaDataUploadCommandMsgId = 0x8803,
    AudioRecordingStartCommandMsgId = 0x8804,

};
}
#endif // MESSAGEIDS_H
