#define RAPIDJSON_HAS_STDSTRING 1

#include "main.hpp"

using namespace QuestUI;

static ModInfo modInfo;

const Logger& getLogger() {
    static const Logger logger(modInfo, LoggerOptions(false, true));
    return logger;
}

extern "C" void setup(ModInfo& info) {
    modInfo.id = "CustomUI-Test";
    modInfo.version = "0.1.0";
    info = modInfo;
}

extern "C" void load() {
    getLogger().info("Starting CustomUI-Test installation...");
    QuestUI::Init();
    custom_types::Register::RegisterType<CustomUITest::CookieClickerViewController>();
    custom_types::Register::RegisterType<CustomUITest::TestFlowCoordinator>();
    QuestUI::Register::RegisterModSettingsFlowCoordinator<CustomUITest::TestFlowCoordinator*>(modInfo);
    //#define TestMods
    #ifdef TestMods
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod1", "0.0.1"}, "TestModSettings1");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod2", "0.0.1"}, "TestModSettings2");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod3", "0.0.1"}, "TestModSettings3");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod4", "0.0.1"}, "TestModSettings4");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod5", "0.0.1"}, "TestModSettings5");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod6", "0.0.1"}, "TestModSettings6");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod7", "0.0.1"}, "TestModSettings7");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod8", "0.0.1"}, "TestModSettings8");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod9", "0.0.1"}, "TestModSettings9");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod10", "0.0.1"}, "TestModSettings10");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod11", "0.0.1"}, "TestModSettings11");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod12", "0.0.1"}, "TestModSettings12");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod13", "0.0.1"}, "TestModSettings13");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod14", "0.0.1"}, "TestModSettings14");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod15", "0.0.1"}, "TestModSettings15");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod16", "0.0.1"}, "TestModSettings16");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod17", "0.0.1"}, "TestModSettings17");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod18", "0.0.1"}, "TestModSettings18");
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod19", "0.0.1"}, "TestModSettings19");
    #endif
    getLogger().info("Successfully installed CustomUI-Test!");
}