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
    if(!KeyboardViewController)
        KeyboardViewController = BeatSaberUI::CreateViewController<QuestUI::KeyboardViewController*>();
}

void OnTextChanged(CustomUITest::TestFlowCoordinator* self, Il2CppString* text) {
    getLogger().info("New text: " + to_utf8(csstrtostr(text)));
}

void OnConfirmPressed(CustomUITest::TestFlowCoordinator* self, Il2CppString* text) {
    getLogger().info("Final text: " + to_utf8(csstrtostr(text)));
    QuestUI::getModSettingsFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void OnCancelPressed(CustomUITest::TestFlowCoordinator* self) {
    getLogger().info("Canceled");
    QuestUI::getModSettingsFlowCoordinator()->DismissFlowCoordinator(self, nullptr, false);
}

void CustomUITest::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        KeyboardViewController->add_confirmPressed(il2cpp_utils::MakeAction<System::Action_1<Il2CppString*>>(il2cpp_functions::class_get_type(classof(System::Action_1<Il2CppString*>*)), this, OnConfirmPressed));
        KeyboardViewController->add_cancelPressed(il2cpp_utils::MakeAction<System::Action>(il2cpp_functions::class_get_type(classof(System::Action*)), this, OnCancelPressed));
        KeyboardViewController->add_textChanged(il2cpp_utils::MakeAction<System::Action_1<Il2CppString*>>(il2cpp_functions::class_get_type(classof(System::Action_1<Il2CppString*>*)), this, OnTextChanged));
        ProvideInitialViewControllers(CookieClickerViewController, nullptr, KeyboardViewController, nullptr, nullptr);
    }
}

void CustomUITest::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    QuestUI::getModSettingsFlowCoordinator()->DismissFlowCoordinator(this, nullptr, false);
}