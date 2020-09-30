#include "TestViewController.hpp"

#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "BeatSaberUI.hpp"

TMPro::TextMeshProUGUI* cookiesTextMesh;
int cookies = 0;
void OnTestButtonClick(UnityEngine::UI::Button* button) {
    cookiesTextMesh->set_text(il2cpp_utils::createcsstr("Cookies: " + std::to_string(++cookies)));
}

void CustomUITest::TestViewController::Awake(){

}

void CustomUITest::TestViewController::DidActivate(bool firstActivation, HMUI::ViewController::ActivationType activationType){
    if(firstActivation){
        BeatSaberUI::CreateText(get_rectTransform(), "TestText", UnityEngine::Vector2(-32.0f, 24.0f))->set_fontSize(8.0f);
        cookiesTextMesh = BeatSaberUI::CreateText(get_rectTransform(), "Cookies: 0", UnityEngine::Vector2(19.0f, 6.0f));
        cookiesTextMesh->set_fontSize(6.0f);
        BeatSaberUI::CreateUIButton(get_rectTransform(), "OkButton", UnityEngine::Vector2(0.0f, -2.0f), UnityEngine::Vector2(28.0f, 10.0f), il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction*)), (Il2CppObject*)nullptr, OnTestButtonClick), "Cookie", nullptr);
    }
}

void CustomUITest::TestViewController::DidDeactivate(HMUI::ViewController::DeactivationType deactivationType){
}