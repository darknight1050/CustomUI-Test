#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"

using namespace il2cpp_utils;
using namespace CustomUI;
using namespace CustomUI::UnityEngine;
using namespace CustomUI::UnityEngine::UI;
using namespace CustomUI::TMPro;

MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, int scene)
{
    bool returnVal = SceneManager_SetActiveScene(scene);
    Il2CppString* nameObject;
    RunMethod(&nameObject, GetClassFromName("UnityEngine.SceneManagement", "Scene"), "GetNameInternal", &scene);
    const char* name = to_utf8(csstrtostr(nameObject)).c_str();
    log(INFO, "Scene: %s", name);
    if(strcmp(name, "MenuViewControllers") == 0) {
        Array<TextMeshProUGUI*>* allTextObjects = (Array<TextMeshProUGUI*>*)Resources::FindObjectsOfTypeAll("TMPro", "TextMeshProUGUI");
        int textMatch = -1;
        for (int i = 0; i < allTextObjects->Length(); i++)
        {
            if (strcmp(allTextObjects->values[i]->get_text().c_str(), "Solo") == 0)
            {
                textMatch = i;
                break;
            }
        }
        if (textMatch == -1)
        {
            return returnVal;
        }
        TextMeshProUGUI* text = CreateTextMeshProUGUI("Hello!", allTextObjects->values[textMatch]->get_transform()->GetParent(), 10.0f);
        text->get_rectTransform()->set_localPosition({-10.0f, 26.0f, 0.0f});
        //Button* button = CreateButton();
        //button->get_transform()->SetParent(allTextObjects->values[textMatch]->get_transform(), false);
    }
    return returnVal;
}


extern "C" void load() {
    log(INFO, "Installing hooks...");
    INSTALL_HOOK_OFFSETLESS(SceneManager_SetActiveScene, FindMethod("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    log(INFO, "Installed all hooks!");
}