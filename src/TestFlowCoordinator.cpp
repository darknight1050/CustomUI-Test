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

void OnTextChanged(CustomUITest::TestFlowCoordinator* self, Il2CppString* text) {
    getLogger().info("New text: " + to_utf8(csstrtostr(text)));
}

void OnConfirmPressed(CustomUITest::TestFlowCoordinator* self, Il2CppString* text) {
    getLogger().info("Final text: " + to_utf8(csstrtostr(text)));
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void OnCancelPressed(CustomUITest::TestFlowCoordinator* self) {
    getLogger().info("Canceled");
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        KeyboardViewController->add_confirmPressed(il2cpp_utils::MakeAction<System::Action_1<Il2CppString*>>(il2cpp_functions::class_get_type(classof(System::Action_1<Il2CppString*>*)), this, OnConfirmPressed));
        KeyboardViewController->add_cancelPressed(il2cpp_utils::MakeAction<System::Action>(il2cpp_functions::class_get_type(classof(System::Action*)), this, OnCancelPressed));
        KeyboardViewController->add_textChanged(il2cpp_utils::MakeAction<System::Action_1<Il2CppString*>>(il2cpp_functions::class_get_type(classof(System::Action_1<Il2CppString*>*)), this, OnTextChanged));
        ProvideInitialViewControllers(CookieClickerViewController, nullptr, nullptr, KeyboardViewController, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    BeatSaberUI::getMainFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}