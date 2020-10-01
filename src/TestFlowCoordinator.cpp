#include "include/TestFlowCoordinator.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"

#include "BeatSaberUI.hpp"

#include "customlogger.hpp"

void CustomUITest::TestFlowCoordinator::Awake(){
    if(!CookieClickerViewController){
        CookieClickerViewController = BeatSaberUI::CreateViewController<CustomUITest::CookieClickerViewController*>();
    }
    if(!KeyboardViewController){
        KeyboardViewController = BeatSaberUI::CreateViewController<CustomUITest::KeyboardViewController*>();
    }
}

void OnConfirmPressed(CustomUITest::TestFlowCoordinator* self, Il2CppString* text) {
    getLogger().info(to_utf8(csstrtostr(text)));
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void OnCancelPressed(CustomUITest::TestFlowCoordinator* self) {
    getLogger().info("Cancel");
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        KeyboardViewController->add_confirmPressed(il2cpp_utils::MakeAction<System::Action_1<Il2CppString*>>(il2cpp_functions::class_get_type(classof(System::Action_1<Il2CppString*>*)), this, OnConfirmPressed));
        KeyboardViewController->add_cancelPressed(il2cpp_utils::MakeAction<System::Action>(il2cpp_functions::class_get_type(classof(System::Action*)), this, OnCancelPressed));
        ProvideInitialViewControllers(KeyboardViewController, CookieClickerViewController, nullptr, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}