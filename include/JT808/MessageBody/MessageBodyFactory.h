#ifndef MESSAGEBODYFACTORY_H
#define MESSAGEBODYFACTORY_H

#include "AudioRecordingStartCommand.h"
#include "CANBusDataUpload.h"
#include "CallbackPhone.h"
#include "DataCompressionReport.h"
#include "DataTransmission.h"
#include "DeletingAreaRoute.h"
#include "DriverIdentityInformationReport.h"
#include "DrivingRecordCommand.h"
#include "DrivingRecordDataUpload.h"
#include "ElectronicWaybillReport.h"
#include "EventReport.h"
#include "EventSetting.h"
#include "GeneralResponse.h"
#include "ImmediateCameraCaptureCommand.h"
#include "ImmediateCameraCaptureCommandResponse.h"
#include "InformationService.h"
#include "InformationServiceCancel.h"
#include "InformationServiceMenuSetting.h"
#include "JT808/MessageBody/AreaSettingProperties.h"
#include "JT808/MessageIds.h"
#include "LocationDataBulkUpload.h"
#include "LocationInformationQueryResponse.h"
#include "LocationInformationReport.h"
#include "ManualAlarmConfirmation.h"
#include "MessageBodyBase.h"
#include "MultimediaDataUpload.h"
#include "MultimediaDataUploadResponse.h"
#include "MultimediaEventInformationUpload.h"
#include "PhoneBookSetting.h"
#include "QuestionDispatch.h"
#include "QuestionResponse.h"
#include "RSAPublicKey.h"
#include "SettingArea.h"
#include "SettingPolygonArea.h"
#include "SettingRoute.h"
#include "SingleStoredMultimediaItemRetrievalUploadCommand.h"
#include "StoredMultimediaDataRetrieval.h"
#include "StoredMultimediaDataRetrievalResponse.h"
#include "StoredMultimediaDataUploadCommand.h"
#include "SubPackageRetransmissionRequest.h"
#include "TemporaryLocationTrackingControl.h"
#include "TerminalAuthentication.h"
#include "TerminalControl.h"
#include "TerminalParameterQuery.h"
#include "TerminalParameterQueryResponse.h"
#include "TerminalParameterSetting.h"
#include "TerminalPropertiesQueryResponse.h"
#include "TerminalRegistration.h"
#include "TerminalRegistrationResponse.h"
#include "TerminalUpgradePackage.h"
#include "TerminalUpgradePackageResult.h"
#include "TextMessageDispatch.h"
#include "VehicleControl.h"
#include "VehicleControlResponse.h"

#include <functional>
#include <memory>
#include <unordered_map>

namespace JT808::MessageBody {

using MessageBodyPtr = std::unique_ptr<MessageBodyBase>;

class MessageBodyFactory
{

public:
    using Creator = std::function<MessageBodyPtr()>;

    static MessageBodyPtr create(MessageIds id)
    {
        static const std::unordered_map<MessageIds, Creator> factoryMap = {
            {TerminalGeneralResponseMsgId, [] { return std::make_unique<GeneralResponse>(); }},
            {PlatformGeneralResponseMsgId, [] { return std::make_unique<GeneralResponse>(); }},
            {TerminalRegistrationMsgId, [] { return std::make_unique<TerminalRegistration>(); }},
            {TerminalAuthenticationMsgId, [] { return std::make_unique<TerminalAuthentication>(); }},
            {TerminalParameterQueryResponseMsgId, [] { return std::make_unique<TerminalParameterQueryResponse>(); }},
            {TerminalPropertiesQueryResponseMsgId, [] { return std::make_unique<TerminalPropertiesQueryResponse>(); }},
            {TerminalUpgradePackageResultMsgId, [] { return std::make_unique<TerminalUpgradePackageResult>(); }},
            {TerminalUpgradePackageMsgId, [] { return std::make_unique<TerminalUpgradePackage>(); }},
            {LocationInformationReportMsgId, [] { return std::make_unique<LocationInformationReport>(); }},
            {LocationInformationQueryResponseMsgId,
             [] { return std::make_unique<LocationInformationQueryResponse>(); }},
            {SubPackageRetransmissionRequestMsgId, [] { return std::make_unique<SubPackageRetransmissionRequest>(); }},
            {TerminalRegistrationResponseMsgId, [] { return std::make_unique<TerminalRegistrationResponse>(); }},
            {TerminalParameterSettingMsgId, [] { return std::make_unique<TerminalParameterSetting>(); }},
            {TerminalControlMsgId, [] { return std::make_unique<TerminalControl>(); }},
            {TerminalSpecificParameterQueryMsgId, [] { return std::make_unique<TerminalParameterQuery>(); }},
            {TemporaryLocationTrackingControlMsgId,
             [] { return std::make_unique<TemporaryLocationTrackingControl>(); }},
            {ManualAlarmConfirmationMsgId, [] { return std::make_unique<ManualAlarmConfirmation>(); }},
            {TextMessageDispatchMsgId, [] { return std::make_unique<TextMessageDispatch>(); }},
            {EventSettingMsgId, [] { return std::make_unique<EventSetting>(); }},
            {EventReportMsgId, [] { return std::make_unique<EventReport>(); }},
            {QuestionDispatchMsgId, [] { return std::make_unique<QuestionDispatch>(); }},
            {QuestionResponseMsgId, [] { return std::make_unique<QuestionResponse>(); }},
            {InformationServiceMenuSettingMsgId, [] { return std::make_unique<InformationServiceMenuSetting>(); }},
            {InformationServiceCancelMsgId, [] { return std::make_unique<InformationServiceCancel>(); }},
            {InformationServiceMsgId, [] { return std::make_unique<InformationService>(); }},
            {CallbackPhoneMsgId, [] { return std::make_unique<CallbackPhone>(); }},
            {PhoneBookSettingMsgId, [] { return std::make_unique<PhoneBookSetting>(); }},
            {VehicleControlMsgId, [] { return std::make_unique<VehicleControl>(); }},
            {VehicleControlResponseMsgId, [] { return std::make_unique<VehicleControlResponse>(); }},
            {SettingCircularAreaMsgId, [] { return std::make_unique<SettingArea>(CircularArea); }},
            {DeletingCircularAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingRectangularAreaMsgId, [] { return std::make_unique<SettingArea>(RectangularArea); }},
            {DeletingRectangularAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingPolygonAreaMsgId, [] { return std::make_unique<SettingPolygonArea>(); }},
            {DeletingPolygonAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingRouteMsgId, [] { return std::make_unique<SettingRoute>(); }},
            {DeletingRouteMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {DrivingRecordDataCollectionCommandMsgId, [] { return std::make_unique<DrivingRecordCommand>(); }},
            {DrivingRecordDataUploadMsgId, [] { return std::make_unique<DrivingRecordDataUpload>(); }},
            {DrivingRecordParameterCommandMsgId, [] { return std::make_unique<DrivingRecordCommand>(); }},
            {ElectronicWaybillReportMsgId, [] { return std::make_unique<ElectronicWaybillReport>(); }},
            {DriverIdentityInformationReportMsgId, [] { return std::make_unique<DriverIdentityInformationReport>(); }},
            {LocationDataBulkUploadMsgId, [] { return std::make_unique<LocationDataBulkUpload>(); }},
            {CANBusDataUploadMsgId, [] { return std::make_unique<CANBusDataUpload>(); }},
            {MultimediaEventInformationUploadMsgId,
             [] { return std::make_unique<MultimediaEventInformationUpload>(); }},
            {MultimediaDataUploadMsgId, [] { return std::make_unique<MultimediaDataUpload>(); }},
            {MultimediaDataUploadResponseMsgId, [] { return std::make_unique<MultimediaDataUploadResponse>(); }},
            {ImmediateCameraCaptureCommandMsgId, [] { return std::make_unique<ImmediateCameraCaptureCommand>(); }},
            {ImmediateCameraCaptureCommandResponseMsgId,
             [] { return std::make_unique<ImmediateCameraCaptureCommandResponse>(); }},
            {StoredMultimediaDataRetrievalMsgId, [] { return std::make_unique<StoredMultimediaDataRetrieval>(); }},
            {StoredMultimediaDataRetrievalResponseMsgId,
             [] { return std::make_unique<StoredMultimediaDataRetrievalResponse>(); }},
            {StoredMultimediaDataUploadCommandMsgId,
             [] { return std::make_unique<StoredMultimediaDataUploadCommand>(); }},
            {AudioRecordingStartCommandMsgId, [] { return std::make_unique<AudioRecordingStartCommand>(); }},
            {SingleStoredMultimediaItemRetrievalUploadCommandMsgId,
             [] { return std::make_unique<SingleStoredMultimediaItemRetrievalUploadCommand>(); }},
            {DownwardDataTransmissionMsgId, [] { return std::make_unique<DataTransmission>(); }},
            {UpwardDataTransmissionMsgId, [] { return std::make_unique<DataTransmission>(); }},
            {DataCompressionReportMsgId, [] { return std::make_unique<DataCompressionReport>(); }},
            {PlatformRSAPublicKeyMsgId, [] { return std::make_unique<RSAPublicKey>(); }},
            {TerminalRSAPublicKeyMsgId, [] { return std::make_unique<RSAPublicKey>(); }},

        };

        auto it = factoryMap.find(id);

        if (it != factoryMap.end()) {
            return it->second();
        } else {
            Json schema;
            return std::make_unique<MessageBody::MessageBodyBase>(schema);
        }
    }
};
}

#endif // MESSAGEBODYFACTORY_H
