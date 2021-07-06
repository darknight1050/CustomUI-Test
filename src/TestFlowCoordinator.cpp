#include "include/TestFlowCoordinator.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "customlogger.hpp"

using namespace QuestUI;

DEFINE_TYPE(CustomUITest, TestFlowCoordinator);

void CustomUITest::TestFlowCoordinator::Awake(){
    if(!CookieClickerViewController)
        CookieClickerViewController = BeatSaberUI::CreateViewController<CustomUITest::CookieClickerViewController*>();
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){
        SetTitle(il2cpp_utils::createcsstr("TestFlowCoordinator"), HMUI::ViewController::AnimationType::In);
        showBackButton = true;
        ProvideInitialViewControllers(CookieClickerViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
}