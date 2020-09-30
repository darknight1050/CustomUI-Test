#pragma once
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_ActivationType.hpp"
#include "HMUI/ViewController_DeactivationType.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, CookieClickerViewController, HMUI::ViewController,


    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2), bool firstActivation, HMUI::ViewController::ActivationType activationType);

    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 1), HMUI::ViewController::DeactivationType deactivationType);

    REGISTER_FUNCTION(CookieClickerViewController,
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)