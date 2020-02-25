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
        /*Array<Canvas*>* allCanvasObjects = (Array<Canvas*>*)Resources::FindObjectsOfTypeAll("UnityEngine", "Canvas");
        for (int i = 0; i < allCanvasObjects->Length(); i++)
        {
            Canvas* currentCanvas = allCanvasObjects->values[i];
            if (strcmp(currentCanvas->get_name().c_str(), "MainScreen") == 0)
            {
                
                Image* imageComponent = (Image*)currentCanvas->get_gameObject()->GetComponent(GetSystemType("UnityEngine.UI", "Image"));
                log(INFO, "Canvas: %s %s", currentCanvas->get_name().c_str(), imageComponent->get_material()->get_name().c_str());
                break;
            }
            RectTransform* rectTransform = (RectTransform*)currentCanvas->get_gameObject()->GetComponent(GetSystemType("UnityEngine", "RectTransform"));
            Vector3 position = rectTransform->get_position();
            Vector3 rotation = rectTransform->get_localEulerAngles();
            log(INFO, "Position: %f %f %f", position.x, position.y, position.z);
            log(INFO, "Rotation: %f %f %f", rotation.x, rotation.y, rotation.z);
            Vector2 sizeDelta = rectTransform->get_sizeDelta();
            log(INFO, "SizeDelta: %f %f", sizeDelta.x, sizeDelta.y);
            Array<Component*>* allComponents = currentCanvas->get_gameObject()->GetComponents(GetSystemType("UnityEngine", "Component"));
            for (int j = 0; j < allComponents->Length(); j++)
            {
                Component* currentComponent = allComponents->values[j];
                log(INFO, "Component: %s %s", il2cpp_functions::class_get_namespace(il2cpp_functions::object_get_class(currentComponent)), il2cpp_functions::class_get_name(il2cpp_functions::object_get_class(currentComponent)));
            }
        }*/
        Array<Button*>* allButtonObjects = (Array<Button*>*)Resources::FindObjectsOfTypeAll("UnityEngine.UI", "Button");
        for (int i = 0; i < allButtonObjects->Length(); i++)
        {
            Button* currentButton = allButtonObjects->values[i];
            Image* imageComponent = (Image*)currentButton->get_image();
            if(imageComponent != nullptr){
                log(INFO, "Button: %s %s %s %s", currentButton->get_name().c_str(), imageComponent->get_name().c_str(), imageComponent->get_sprite()->get_name().c_str(), imageComponent->get_material()->get_name().c_str());
                Array<Image*>* allImageObjects = (Array<Image*>*)currentButton->get_gameObject()->GetComponentsInChildren(GetSystemType("UnityEngine.UI", "Image"));
                for (int j = 0; j < allImageObjects->Length(); j++){
                     log(INFO, "Image: %s %s %s", allImageObjects->values[j]->get_name().c_str(), allImageObjects->values[j]->get_sprite()->get_name().c_str(), allImageObjects->values[j]->get_material()->get_name().c_str());
                }
                //RectTransform* rectTransform = (RectTransform*)currentButton->get_transform();
                //Vector2 sizeDelta = rectTransform->get_sizeDelta();
                //log(INFO, "SizeDelta: %f %f", sizeDelta.x, sizeDelta.y);
            }
        }
        canvas = CreateCanvas();
        //Object::DontDestroyOnLoad(canvas);
        RectTransform* canvasRectTransform = (RectTransform*)canvas->get_transform();
        canvasRectTransform->set_position({-2.25f, 1.6f, 1.55f});
        canvasRectTransform->set_localEulerAngles({0.0f, 300.0f});
        canvasRectTransform->SetSize({120.0f, 80.0f});
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
        TextMeshProUGUI* text = CreateTextMeshProUGUI("CustomUI YEET!", canvasRectTransform, 10.0f);
        text->get_rectTransform()->set_localPosition({-24.0f, 36.0f, 0.0f});
        Button* button = CreateButton({23.15f, 8.8f}, canvasRectTransform);
        Button* uiButton = CreateUIButton(canvasRectTransform, "PlayButton", {0.0f, 0.0f}, {23.15f, 8.8f});
        
    }
    return returnVal;
}


extern "C" void load() {
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(SceneManager_SetActiveScene, FindMethod("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    log(INFO, "Installed all hooks!");
}