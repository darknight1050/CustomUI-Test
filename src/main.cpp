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
    QuestUI::Register::RegisterModSettingsViewController<CustomUITest::CookieClickerViewController*>(ModInfo{"TestMod", "0.0.1"}, "TestModSettings");
    getLogger().info("Successfully installed CustomUI-Test!");
}