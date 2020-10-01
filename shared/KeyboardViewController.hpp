#pragma once
#include <sstream>
#include <string>
#include "CustomUIKeyboard.hpp"
#include "UnityEngine/GameObject.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ViewController_ActivationType.hpp"
#include "System/Action.hpp"
#include "System/Action_1.hpp"

#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(CustomUITest, KeyboardViewController, HMUI::ViewController,

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, keyboardGO);

    DECLARE_INSTANCE_FIELD(CustomUITest::CustomUIKeyboard*, keyboard);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, inputText);

    DECLARE_INSTANCE_FIELD(Il2CppString*, inputString);

    DECLARE_INSTANCE_FIELD(System::Action_1<Il2CppString*>*, confirmPressed);
    DECLARE_METHOD(void, add_confirmPressed, System::Action_1<Il2CppString*>* action);
    DECLARE_METHOD(void, remove_confirmPressed, System::Action_1<Il2CppString*>* action);

    DECLARE_INSTANCE_FIELD(System::Action*, cancelPressed);
    DECLARE_METHOD(void, add_cancelPressed, System::Action* action);
    DECLARE_METHOD(void, remove_cancelPressed, System::Action* action);

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2), bool firstActivation, HMUI::ViewController::ActivationType activationType);
    
    DECLARE_METHOD(void, UpdateInputText);
    DECLARE_METHOD(void, ClearInputText);

    REGISTER_FUNCTION(KeyboardViewController,
        REGISTER_FIELD(keyboardGO);
        REGISTER_FIELD(keyboard);
        REGISTER_FIELD(inputText);
        REGISTER_FIELD(inputString);
        REGISTER_FIELD(confirmPressed);
        REGISTER_METHOD(add_confirmPressed);
        REGISTER_METHOD(remove_confirmPressed);
        REGISTER_FIELD(cancelPressed);
        REGISTER_METHOD(add_cancelPressed);
        REGISTER_METHOD(remove_cancelPressed);

        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(UpdateInputText);
        REGISTER_METHOD(ClearInputText);
    )
)