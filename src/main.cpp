#define RAPIDJSON_HAS_STDSTRING 1

#include "main.hpp"

static ModInfo modInfo;

const Logger& getLogger() {
  static const Logger logger(modInfo, LoggerOptions(false, true));
  return logger;
}

HMUI::FlowCoordinator* flowCoordinator = nullptr;
void OnButtonClick(UnityEngine::UI::Button* button) {
    getLogger().info("OnButtonClick");
    if(!flowCoordinator) {
        flowCoordinator = BeatSaberUI::CreateFlowCoordinator<CustomUITest::TestFlowCoordinator*>();
    }
    BeatSaberUI::getMainFlowCoordinator()->PresentFlowCoordinator(flowCoordinator, nullptr, false, false);
}

UnityEngine::UI::Button* button;
MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void, GlobalNamespace::MainMenuViewController* self, bool firstActivation, HMUI::ViewController::ActivationType activationType) {
    MainMenuViewController_DidActivate(self, firstActivation, activationType);
    if(firstActivation){
        UnityEngine::UI::Button* settingsButton = (UnityEngine::UI::Button*)RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_settingsButton"));
        button = UnityEngine::Object::Instantiate(settingsButton);
        button->set_name(il2cpp_utils::createcsstr("TestButton"));
        button->get_transform()->SetParent(settingsButton->get_transform()->GetParent(), false);
        button->get_onClick()->AddListener(il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction*)), (Il2CppObject*)nullptr, OnButtonClick));
        BeatSaberUI::SetButtonText(button, "TestButton");
    }
}

extern "C" void setup(ModInfo& info) {
    modInfo.id = "CustomUI-Test";
    modInfo.version = "0.1.0";
    info = modInfo;
}

extern "C" void load() {
    getLogger().info("Starting CustomUI-Test installation...");
    custom_types::Register::RegisterType<CustomUITest::CookieClickerViewController>();
    custom_types::Register::RegisterType<CustomUITest::CustomUIKeyboard>();
    custom_types::Register::RegisterType<CustomUITest::KeyboardViewController>();
    custom_types::Register::RegisterType<CustomUITest::TestFlowCoordinator>();
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));
    getLogger().info("Successfully installed CustomUI-Test!");
}