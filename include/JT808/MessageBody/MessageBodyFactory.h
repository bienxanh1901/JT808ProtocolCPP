#ifndef MESSAGEBODYFACTORY_H
#define MESSAGEBODYFACTORY_H

#include "JT808//MessageBody/MessageBodyBase.h"
#include "JT808/MessageBody/CallbackPhone.h"
#include "JT808/MessageBody/DeletingCircleArea.h"
#include "JT808/MessageBody/EventReport.h"
#include "JT808/MessageBody/EventSetting.h"
#include "JT808/MessageBody/GeneralResponse.h"
#include "JT808/MessageBody/InformationService.h"
#include "JT808/MessageBody/InformationServiceCancel.h"
#include "JT808/MessageBody/InformationServiceMenuSetting.h"
#include "JT808/MessageBody/LocationInformationQueryResponse.h"
#include "JT808/MessageBody/LocationInformationReport.h"
#include "JT808/MessageBody/ManualAlarmConfirmation.h"
#include "JT808/MessageBody/PhoneBookSetting.h"
#include "JT808/MessageBody/QuestionDispatch.h"
#include "JT808/MessageBody/QuestionResponse.h"
#include "JT808/MessageBody/SettingCircleArea.h"
#include "JT808/MessageBody/SubPackageRetransmissionRequest.h"
#include "JT808/MessageBody/TemporaryLocationTrackingControl.h"
#include "JT808/MessageBody/TerminalAuthentication.h"
#include "JT808/MessageBody/TerminalControl.h"
#include "JT808/MessageBody/TerminalParameterQuery.h"
#include "JT808/MessageBody/TerminalParameterQueryResponse.h"
#include "JT808/MessageBody/TerminalParameterSetting.h"
#include "JT808/MessageBody/TerminalPropertiesQueryResponse.h"
#include "JT808/MessageBody/TerminalRegistration.h"
#include "JT808/MessageBody/TerminalRegistrationResponse.h"
#include "JT808/MessageBody/TerminalUpgradePackage.h"
#include "JT808/MessageBody/TerminalUpgradePackageResult.h"
#include "JT808/MessageBody/TextMessageDispatch.h"
#include "JT808/MessageBody/VehicleControl.h"
#include "JT808/MessageBody/VehicleControlResponse.h"
#include "JT808/MessageIds.h"

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
            {SettingCircleAreaMsgId, [] { return std::make_unique<SettingCircleArea>(); }},
            {DeletingCircleAreaMsgId, [] { return std::make_unique<DeletingCircleArea>(); }},
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
