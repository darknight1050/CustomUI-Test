#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_ActivationType.hpp"
#include "HMUI/ViewController_DeactivationType.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, TestViewController, HMUI::ViewController,

    DECLARE_METHOD(void, Awake);

    DECLARE_INTERFACE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2), bool firstActivation, HMUI::ViewController::ActivationType activationType);

    DECLARE_INTERFACE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 1), HMUI::ViewController::DeactivationType deactivationType);

    REGISTER_FUNCTION(TestViewController,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)