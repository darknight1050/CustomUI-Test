#pragma once
#include "UnityEngine/Sprite.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/ViewController.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, CookieClickerViewController, HMUI::ViewController,

    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, cookieSprite);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, cookiesTextMesh);
    DECLARE_INSTANCE_FIELD(int, cookies);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidDeactivate>::get(), bool removedFromHierarchy, bool screenSystemDisabling);

)