#define RAPIDJSON_HAS_STDSTRING 1

#include "main.hpp"
#include "ModConfig.hpp"

using namespace QuestUI;

static ModInfo modInfo;

Logger& getLogger() {
    static auto logger = new Logger(modInfo, LoggerOptions(false, false));
    return *logger;
}

DEFINE_CONFIG(ModConfig);

extern "C" void setup(ModInfo& info) {
    modInfo.id = "CustomUI-Test";
    modInfo.version = "0.1.0";
    info = modInfo;
    getModConfig().Init(modInfo);
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    getLogger().info("DidActivate: %p, %d, %d, %d", self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

extern "C" void load() {
    getLogger().info("Starting CustomUI-Test installation...");
    il2cpp_functions::Init();
    QuestUI::Init();
    custom_types::Register::RegisterTypes<
        CustomUITest::CookieClickerViewController, 
        CustomUITest::TestFlowCoordinator
        >();
        
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(modInfo);
    //QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);
    //QuestUI::Register::RegisterModSettingsFlowCoordinator<CustomUITest::TestFlowCoordinator*>(ModInfo{"TestFlowCoordinator", "0.0.1"});
    //#define TestMods
    #ifdef TestMods
    for(int i = 1; i <= 29; i++)
      QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod" + std::to_string(i), "0.0.1"}, "TestModSettings"  + std::to_string(i));
    #endif
    getLogger().info("Successfully installed CustomUI-Test!");
}