#include "include/TestFlowCoordinator.hpp"

#include "BeatSaberUI.hpp"

void CustomUITest::TestFlowCoordinator::Awake(){
    if(!testViewController){
        testViewController = BeatSaberUI::CreateViewController<CustomUITest::TestViewController*>();
    }
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        ProvideInitialViewControllers(testViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}