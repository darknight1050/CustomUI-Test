#pragma once
#include "UnityEngine/Sprite.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_ActivationType.hpp"
#include "HMUI/ViewController_DeactivationType.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, CookieClickerViewController, HMUI::ViewController,

    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, cookieSprite);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, cookiesTextMesh);
    DECLARE_INSTANCE_FIELD(int, cookies);


    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2), bool firstActivation, HMUI::ViewController::ActivationType activationType);

    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 1), HMUI::ViewController::DeactivationType deactivationType);

    REGISTER_FUNCTION(CookieClickerViewController,
        REGISTER_FIELD(cookieSprite);
        REGISTER_FIELD(cookiesTextMesh);
        REGISTER_FIELD(cookies);

        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(DidDeactivate);
    )
)