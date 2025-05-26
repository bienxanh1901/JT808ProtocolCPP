#ifndef MESSAGEBODYFACTORY_H
#define MESSAGEBODYFACTORY_H

#include "CallbackPhone.h"
#include "DeletingAreaRoute.h"
#include "EventReport.h"
#include "EventSetting.h"
#include "GeneralResponse.h"
#include "InformationService.h"
#include "InformationServiceCancel.h"
#include "InformationServiceMenuSetting.h"
#include "JT808/MessageIds.h"
#include "LocationInformationQueryResponse.h"
#include "LocationInformationReport.h"
#include "ManualAlarmConfirmation.h"
#include "MessageBodyBase.h"
#include "PhoneBookSetting.h"
#include "QuestionDispatch.h"
#include "QuestionResponse.h"
#include "SettingArea.h"
#include "SettingPolygonArea.h"
#include "SettingRoute.h"
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
            {SettingCircleAreaMsgId, [] { return std::make_unique<SettingArea>(CircleArea); }},
            {DeletingCircleAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingRectangleAreaMsgId, [] { return std::make_unique<SettingArea>(RectangleArea); }},
            {DeletingRectangleAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingPolygonAreaMsgId, [] { return std::make_unique<SettingPolygonArea>(); }},
            {DeletingPolygonAreaMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
            {SettingRouteMsgId, [] { return std::make_unique<SettingRoute>(); }},
            {DeletingRouteMsgId, [] { return std::make_unique<DeletingAreaRoute>(); }},
        };

        auto it = factoryMap.find(id);

        if (it != factoryMap.end()) {
            return it->second();
        } else {
            return std::make_unique<MessageBody::MessageBodyBase>();
        }
    }
};
}

#endif // MESSAGEBODYFACTORY_H
