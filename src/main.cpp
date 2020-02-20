#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"

using namespace il2cpp_utils;
using namespace CustomUI;
using namespace CustomUI::UnityEngine;
using namespace CustomUI::UnityEngine::UI;
using namespace CustomUI::TMPro;

Canvas* canvas;

MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, int scene)
{
    bool returnVal = SceneManager_SetActiveScene(scene);
    Il2CppString* nameObject;
    RunMethod(&nameObject, GetClassFromName("UnityEngine.SceneManagement", "Scene"), "GetNameInternal", scene);
    const char* name = to_utf8(csstrtostr(nameObject)).c_str();
    log(INFO, "Scene: %s", name);
    if(strcmp(name, "MenuViewControllers") == 0 && canvas == nullptr) {
        canvas = CreateCanvas();
        RectTransform* rectTransform = (RectTransform*)canvas->get_gameObject()->GetComponent(GetSystemType("UnityEngine", "RectTransform"));
        rectTransform->set_position({-2.25f, 1.6f, 1.55f});
        rectTransform->set_localEulerAngles({0.0f, 300.0f});
        rectTransform->SetSize({120.0f, 80.0f});
        Image* imageComponent = (Image*)canvas->get_gameObject()->AddComponent(GetSystemType("UnityEngine.UI", "Image"));
        Array<Sprite*>* allSpriteObjects = (Array<Sprite*>*)Resources::FindObjectsOfTypeAll("UnityEngine", "Sprite");
        Sprite* spriteMatch = nullptr;
        for (int i = 0; i < allSpriteObjects->Length(); i++)
        {
            if (strcmp(allSpriteObjects->values[i]->get_name().c_str(), "MainScreenMask") == 0)
            {
                spriteMatch = allSpriteObjects->values[i];
                break;
            }
        }
        if (spriteMatch == nullptr)
        {
            log(DEBUG, "Could not find matching Sprite!");
            return returnVal;
        }
        Array<Material*>* allMaterialObjects = (Array<Material*>*)Resources::FindObjectsOfTypeAll("UnityEngine", "Material");
        Material* materialMatch = nullptr;
        for (int i = 0; i < allMaterialObjects->Length(); i++)
        {
            if (strcmp(allMaterialObjects->values[i]->get_name().c_str(), "UIFogBG") == 0)
            {
                materialMatch = allMaterialObjects->values[i];
                break;
            }
        }
        if (materialMatch == nullptr)
        {
            log(DEBUG, "Could not find matching Material!");
            return returnVal;
        }
        imageComponent->set_sprite(spriteMatch);
        imageComponent->set_material(materialMatch);
        imageComponent->set_type(Image::Type::Sliced);

        Array<TextMeshProUGUI*>* allTextObjects = (Array<TextMeshProUGUI*>*)Resources::FindObjectsOfTypeAll("TMPro", "TextMeshProUGUI");
        TextMeshProUGUI* text = CreateTextMeshProUGUI("CustomUI YEET!", canvas->get_transform(), 10.0f);
        text->get_rectTransform()->set_localPosition({-24.0f, 36.0f, 0.0f});
        //Button* button = CreateButton();
        //button->get_transform()->SetParent(canvas->get_transform(), false);
    }
    return returnVal;
}


extern "C" void load() {
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(SceneManager_SetActiveScene, FindMethod("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    log(INFO, "Installed all hooks!");
}