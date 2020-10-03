#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/FlowCoordinator_ActivationType.hpp"

#include "CookieClickerViewController.hpp"
#include "questui/shared/CustomTypes/ViewControllers/KeyboardViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, TestFlowCoordinator, HMUI::FlowCoordinator,

    DECLARE_INSTANCE_FIELD(CustomUITest::CookieClickerViewController*, CookieClickerViewController);
    DECLARE_INSTANCE_FIELD(QuestUI::KeyboardViewController*, KeyboardViewController);


    DECLARE_METHOD(void, Awake);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 2), bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType);

    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(TestFlowCoordinator,
        REGISTER_FIELD(CookieClickerViewController);
        REGISTER_FIELD(KeyboardViewController);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)