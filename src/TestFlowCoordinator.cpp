#include "include/TestFlowCoordinator.hpp"

#include "BeatSaberUI.hpp"

void CustomUITest::TestFlowCoordinator::Awake(){
    if(!CookieClickerViewController){
        CookieClickerViewController = BeatSaberUI::CreateViewController<CustomUITest::CookieClickerViewController*>();
    }
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        ProvideInitialViewControllers(CookieClickerViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}