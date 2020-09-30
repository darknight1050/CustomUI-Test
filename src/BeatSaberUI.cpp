#include "BeatSaberUI.hpp"

namespace BeatSaberUI {
    
    GlobalNamespace::MainFlowCoordinator* getMainFlowCoordinator() {
        static GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator = nullptr;
        if(!mainFlowCoordinator)
            mainFlowCoordinator = UnityEngine::Object::FindObjectOfType<GlobalNamespace::MainFlowCoordinator*>();
        return mainFlowCoordinator;
    }

    TMPro::TMP_FontAsset* getMainTextFont() {
        static TMPro::TMP_FontAsset* mainTextFont = nullptr;
        if(!mainTextFont){
            mainTextFont = ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<TMPro::TMP_FontAsset*>(), [](TMPro::TMP_FontAsset* x) { return to_utf8(csstrtostr(x->get_name())) == "Teko-Medium SDF No Glow"; });
        }
        return mainTextFont;
    }

    TMPro::TextMeshProUGUI* CreateText(UnityEngine::RectTransform* parent, std::string text, UnityEngine::Vector2 anchoredPosition) {
        return CreateText(parent, text, anchoredPosition, UnityEngine::Vector2(60.0f, 10.0f));
    }

    TMPro::TextMeshProUGUI* CreateText(UnityEngine::RectTransform* parent, std::string text, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta) {
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
        rectTransform->set_anchoredPosition(anchoredPosition);
        rectTransform->set_sizeDelta(sizeDelta);

        gameObj->SetActive(true);
        return textMesh;
    }

    void SetButtonText(UnityEngine::UI::Button* button, std::string text) {
        Polyglot::LocalizedTextMeshProUGUI* localizer = button->GetComponentInChildren<Polyglot::LocalizedTextMeshProUGUI*>();
        if (localizer)
            UnityEngine::Object::Destroy(localizer);
        TMPro::TextMeshProUGUI* textMesh = button->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
        if(textMesh)
            textMesh->set_text(il2cpp_utils::createcsstr(text));
    }

    void SetButtonTextSize(UnityEngine::UI::Button* button, float fontSize) {
        TMPro::TextMeshProUGUI* textMesh = button->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
        if(textMesh)
            textMesh->set_fontSize(fontSize);
    }

    void ToggleButtonWordWrapping(UnityEngine::UI::Button* button, bool enableWordWrapping) {
        TMPro::TextMeshProUGUI* textMesh = button->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
        if(textMesh)
            textMesh->set_enableWordWrapping(enableWordWrapping);
    }

    void SetButtonIcon(UnityEngine::UI::Button* button, UnityEngine::Sprite* icon) {
        auto* array = button->GetComponentsInChildren<UnityEngine::UI::Image*>();
        if(array->Length() > 1)
            ArrayUtil::First(array, [](UnityEngine::UI::Image* x) { return to_utf8(csstrtostr(x->get_name())) == "Icon";})->set_sprite(icon);
    }

    void SetButtonBackground(UnityEngine::UI::Button* button, UnityEngine::Sprite* background) {
        auto* array = button->GetComponentsInChildren<UnityEngine::UI::Image*>();
        if(array->Length() > 0)
            array->values[0]->set_sprite(background);
    }

    UnityEngine::UI::Button* CreateUIButton(UnityEngine::RectTransform* parent, std::string buttonTemplate, UnityEngine::Vector2 anchoredPosition, UnityEngine::Vector2 sizeDelta, UnityEngine::Events::UnityAction* onClick, std::string buttonText, UnityEngine::Sprite* icon){
        UnityEngine::UI::Button* button = CreateUIButton(parent, buttonTemplate, anchoredPosition, onClick, buttonText, icon);
        ((UnityEngine::RectTransform*)button->get_transform())->set_sizeDelta(sizeDelta);
        return button;
    }

    UnityEngine::UI::Button* CreateUIButton(UnityEngine::RectTransform* parent, std::string buttonTemplate, UnityEngine::Vector2 anchoredPosition, UnityEngine::Events::UnityAction* onClick, std::string buttonText, UnityEngine::Sprite* icon){
        UnityEngine::UI::Button* button = CreateUIButton(parent, buttonTemplate, onClick, buttonText, icon);
        ((UnityEngine::RectTransform*)button->get_transform())->set_anchoredPosition(anchoredPosition);
        return button;
    }

    UnityEngine::UI::Button* CreateUIButton(UnityEngine::RectTransform* parent, std::string buttonTemplate, UnityEngine::Events::UnityAction* onClick, std::string buttonText, UnityEngine::Sprite* icon){
        UnityEngine::UI::Button* button = UnityEngine::Object::Instantiate(ArrayUtil::Last(UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::UI::Button*>(), [&buttonTemplate](UnityEngine::UI::Button* x) { return to_utf8(csstrtostr(x->get_name())) == buttonTemplate; }), parent, false);
        button->set_onClick(*il2cpp_utils::New<UnityEngine::UI::Button::ButtonClickedEvent*>());
        if(onClick)
            button->get_onClick()->AddListener(onClick);
    
        button->set_name(il2cpp_utils::createcsstr("CustomUIButton"));

        UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)button->get_transform();
        rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));

        SetButtonText(button, buttonText);
        if(icon)
            SetButtonIcon(button, icon);
        return button;
    }
}