#pragma once
#include "UnityEngine/Color.hpp"
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    CONFIG_VALUE(ModBool, bool, "ModConfigBool", true, "Some bool setting");
    CONFIG_VALUE(ModInt, int, "ModConfignt", 1337, "Some int setting");
    CONFIG_VALUE(ModFloat, float, "ModConfigFloat", 10.0f, "Some float setting");
    CONFIG_VALUE(ModString, std::string, "ModConfigString", "hi", "Some string setting");
    CONFIG_VALUE(ModColor, UnityEngine::Color, "ModConfigColor", UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.0f), "Some color setting");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(ModBool);
        CONFIG_INIT_VALUE(ModInt);
        CONFIG_INIT_VALUE(ModFloat);
        CONFIG_INIT_VALUE(ModString);
        CONFIG_INIT_VALUE(ModColor);
    )
)
