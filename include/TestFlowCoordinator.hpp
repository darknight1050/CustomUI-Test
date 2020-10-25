#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "CookieClickerViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, TestFlowCoordinator, HMUI::FlowCoordinator,

    DECLARE_INSTANCE_FIELD(CustomUITest::CookieClickerViewController*, CookieClickerViewController);


    DECLARE_METHOD(void, Awake);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(TestFlowCoordinator,
        REGISTER_FIELD(CookieClickerViewController);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)