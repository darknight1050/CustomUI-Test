#include "shared/BeatSaberUI.hpp"

namespace BeatSaberUI {

    
    GlobalNamespace::MainFlowCoordinator* getMainFlowCoordinator(){
        static GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator = nullptr;
        if(!mainFlowCoordinator)
            mainFlowCoordinator = UnityEngine::Object::FindObjectOfType<GlobalNamespace::MainFlowCoordinator*>();
        return mainFlowCoordinator;
    }

    TMPro::TMP_FontAsset* getMainTextFont(){
        static TMPro::TMP_FontAsset* mainTextFont = nullptr;
        if(!mainTextFont){
            auto* array = UnityEngine::Resources::FindObjectsOfTypeAll<TMPro::TMP_FontAsset*>();
            for (int i = 0; i < array->Length(); i++) {
                TMPro::TMP_FontAsset* textFont = array->values[i];
                if (to_utf8(csstrtostr(textFont->get_name())) == "Teko-Medium SDF No Glow") {
                    mainTextFont  = textFont;
                    break;
                }
            }
        }
        return mainTextFont;
    }

    TMPro::TextMeshProUGUI* CreateText(UnityEngine::RectTransform* parent, std::string text, UnityEngine::Vector2 anchoredPosition)
    {
        return CreateText(parent, text, anchoredPosition, UnityEngine::Vector2(60.0f, 10.0f));
    }

    TMPro::TextMeshProUGUI* CreateText(UnityEngine::RectTransform* parent, std::string text, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta)
    {
        UnityEngine::GameObject* gameObj = RET_0_UNLESS(il2cpp_utils::New<UnityEngine::GameObject*>(il2cpp_utils::createcsstr("CustomUIText")));
        gameObj->SetActive(false);

        TMPro::TextMeshProUGUI* textMesh = gameObj->AddComponent<TMPro::TextMeshProUGUI*>();
        UnityEngine::RectTransform* rectTransform = textMesh->get_rectTransform();
        textMesh->set_font(getMainTextFont());
        rectTransform->SetParent(parent, false);
        textMesh->set_text(il2cpp_utils::createcsstr(text));
        textMesh->set_fontSize(4.0f);
        textMesh->set_color(UnityEngine::Color::get_white());

        rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_sizeDelta(sizeDelta);
        rectTransform->set_anchoredPosition(anchoredPosition);

        gameObj->SetActive(true);
        return textMesh;
    }
}