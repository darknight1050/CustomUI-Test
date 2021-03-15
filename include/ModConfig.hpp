#pragma once
#include "UnityEngine/Color.hpp"
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,

    DECLARE_VALUE(ModBool, bool, "ModConfigBool", true, "Some bool setting");
    DECLARE_VALUE(ModInt, int, "ModConfignt", 1337, "Some int setting");
    DECLARE_VALUE(ModFloat, float, "ModConfigFloat", 10.0f, "Some float setting");
    DECLARE_VALUE(ModString, std::string, "ModConfigString", "hi", "Some string setting");
    DECLARE_VALUE(ModColor, UnityEngine::Color, "ModConfigColor", UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.0f), "Some color setting");

    INIT_FUNCTION(
        INIT_VALUE(ModBool);
        INIT_VALUE(ModInt);
        INIT_VALUE(ModFloat);
        INIT_VALUE(ModString);
        INIT_VALUE(ModColor);
    )
)
