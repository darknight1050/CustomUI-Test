#include "include/TestFlowCoordinator.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "customlogger.hpp"

using namespace QuestUI;

DEFINE_CLASS(CustomUITest::TestFlowCoordinator);

void CustomUITest::TestFlowCoordinator::Awake(){
    if(!CookieClickerViewController)
        CookieClickerViewController = BeatSaberUI::CreateViewController<CustomUITest::CookieClickerViewController*>();
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        ProvideInitialViewControllers(CookieClickerViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    QuestUI::getModSettingsFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}