#define RAPIDJSON_HAS_STDSTRING 1

#include "include/main.hpp"
#include "extern/custom-types/shared/register.hpp"
#include "extern/custom-types/shared/macros.hpp"
#include "extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "extern/beatsaber-hook/shared/config/config-utils.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "HMUI/FlowCoordinator_ActivationType.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "HMUI/ViewController_ActivationType.hpp"
#include "HMUI/ViewController_DeactivationType.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/Button_ButtonClickedEvent.hpp"

#include <chrono>
#include <map>
#include <queue>
#include <thread>

static ModInfo modInfo;

const Logger& getLogger() {
  static const Logger logger(modInfo, LoggerOptions(false, true));
  return logger;
}

Configuration& getConfig() {
    static Configuration overall_config(modInfo);
    return overall_config;
}

template<class T = HMUI::ViewController*>
T CreateViewController() {
    T viewController = RET_0_UNLESS(il2cpp_utils::New<UnityEngine::GameObject*>(il2cpp_utils::createcsstr("BSMLViewController")))->AddComponent<T>();
    UnityEngine::Object::DontDestroyOnLoad(viewController->get_gameObject());

    UnityEngine::RectTransform* rectTransform = viewController->get_rectTransform();
    rectTransform->set_anchorMin(UnityEngine::Vector2(0.0f, 0.0f));
    rectTransform->set_anchorMax(UnityEngine::Vector2(1.0f, 1.0f));
    rectTransform->set_sizeDelta(UnityEngine::Vector2(0.0f, 0.0f));
    rectTransform->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
    return viewController;
}

template<class T = HMUI::FlowCoordinator*>
T CreateFlowCoordinator() {
    T flowCoordinator = RET_0_UNLESS(il2cpp_utils::New<UnityEngine::GameObject*>(il2cpp_utils::createcsstr("BSMLFlowCoordinator")))->AddComponent<T>();
    flowCoordinator->baseInputModule = RET_0_UNLESS(UnityEngine::Object::FindObjectOfType<GlobalNamespace::MainFlowCoordinator*>())->baseInputModule;
    return flowCoordinator;
}

DECLARE_CLASS_CODEGEN(Il2CppNamespace, TestViewController, HMUI::ViewController,

    DECLARE_METHOD(void, Awake);

    DECLARE_INTERFACE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2), bool firstActivation, HMUI::ViewController::ActivationType activationType);

    DECLARE_INTERFACE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 1), HMUI::ViewController::DeactivationType deactivationType);

    REGISTER_FUNCTION(TestViewController,
        getLogger().debug("Registering TestViewController!");
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)

void Il2CppNamespace::TestViewController::Awake(){
}

void Il2CppNamespace::TestViewController::DidActivate(bool firstActivation, HMUI::ViewController::ActivationType activationType){
}

void Il2CppNamespace::TestViewController::DidDeactivate(HMUI::ViewController::DeactivationType deactivationType){
}

DECLARE_CLASS_CODEGEN(Il2CppNamespace, TestFlowCoordinator, HMUI::FlowCoordinator,

    DECLARE_INSTANCE_FIELD(Il2CppNamespace::TestViewController*, testViewController);


    DECLARE_METHOD(void, Awake);

    DECLARE_INTERFACE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 2), bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType);

    DECLARE_INTERFACE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(TestFlowCoordinator,
        getLogger().debug("Registering TestFlowCoordinator!");
        REGISTER_FIELD(testViewController);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)


void Il2CppNamespace::TestFlowCoordinator::Awake(){
    if(!testViewController){
        testViewController = CreateViewController<Il2CppNamespace::TestViewController*>();
    }
}

void Il2CppNamespace::TestFlowCoordinator::DidActivate(bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType){
    if(firstActivation){
        set_title(il2cpp_utils::createcsstr("TestFlowCoordinator"));
        showBackButton = true;
        ProvideInitialViewControllers(testViewController, nullptr, nullptr, nullptr, nullptr);
    }
}

void Il2CppNamespace::TestFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController){
    RET_V_UNLESS(UnityEngine::Object::FindObjectOfType<GlobalNamespace::MainFlowCoordinator*>())->DismissFlowCoordinator(this, nullptr, false);
}

HMUI::FlowCoordinator* flowCoordinator = nullptr;
void OnButtonClick(UnityEngine::UI::Button* button) {
    getLogger().info("OnButtonClick");
    if(!flowCoordinator) {
        flowCoordinator = CreateFlowCoordinator<Il2CppNamespace::TestFlowCoordinator*>();
    }
    GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator = RET_V_UNLESS(UnityEngine::Object::FindObjectOfType<GlobalNamespace::MainFlowCoordinator*>());
    mainFlowCoordinator->PresentFlowCoordinator(flowCoordinator, nullptr, false, false);
}

MAKE_HOOK_OFFSETLESS(MainFlowCoordinator_DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType) {
    MainFlowCoordinator_DidActivate(self, firstActivation, activationType);
}
TMPro::TextMeshProUGUI* textObject;
MAKE_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, void, GlobalNamespace::MainMenuViewController* self, bool firstActivation, HMUI::ViewController::ActivationType activationType) {
    MainMenuViewController_DidActivate(self, firstActivation, activationType);
    if(firstActivation){
        UnityEngine::UI::Button* settingsButton = (UnityEngine::UI::Button*)RET_V_UNLESS(il2cpp_utils::GetFieldValue(self, "_settingsButton"));
        UnityEngine::UI::Button* button = UnityEngine::Object::Instantiate(settingsButton);
        button->set_name(il2cpp_utils::createcsstr("TestButton"));
        button->get_transform()->SetParent(settingsButton->get_transform()->GetParent(), false);
        button->get_onClick()->AddListener(il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, OnButtonClick));
        textObject = (TMPro::TextMeshProUGUI*)CRASH_UNLESS(button->get_gameObject()->GetComponentInChildren(il2cpp_utils::GetSystemType("TMPro", "TextMeshProUGUI"), true));
    }
    textObject->set_text(il2cpp_utils::createcsstr("TestButton"));
}

extern "C" void setup(ModInfo& info) 
{
    modInfo.id = "CustomUI-Test";
    modInfo.version = "0.1.0";
    info = modInfo;
}

extern "C" void load() {
    getLogger().info("Starting CustomUI-Test installation...");
    custom_types::Register::RegisterType<Il2CppNamespace::TestViewController>();
    custom_types::Register::RegisterType<Il2CppNamespace::TestFlowCoordinator>();
    INSTALL_HOOK_OFFSETLESS(MainFlowCoordinator_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainFlowCoordinator", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(MainMenuViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));
    getLogger().info("Successfully installed CustomUI-Test!");
}