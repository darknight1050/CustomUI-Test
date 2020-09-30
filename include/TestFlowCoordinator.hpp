#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/FlowCoordinator_ActivationType.hpp"

#include "TestViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, TestFlowCoordinator, HMUI::FlowCoordinator,

    DECLARE_INSTANCE_FIELD(CustomUITest::TestViewController*, testViewController);


    DECLARE_METHOD(void, Awake);

    DECLARE_INTERFACE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 2), bool firstActivation, HMUI::FlowCoordinator::ActivationType activationType);

    DECLARE_INTERFACE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);

    REGISTER_FUNCTION(TestFlowCoordinator,
        REGISTER_FIELD(testViewController);

        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(BackButtonWasPressed);
    )
)