#include "CookieClickerViewController.hpp"

#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "BeatSaberUI.hpp"
#include "Base64Sprite.hpp" 
#include <stdlib.h>

UnityEngine::Sprite* cookieSprite;
TMPro::TextMeshProUGUI* cookiesTextMesh;
int cookies = 0;
void OnTestButtonClick(CustomUITest::CookieClickerViewController* viewController, UnityEngine::UI::Button* button) {
    if(!cookieSprite)
        cookieSprite = BeatSaberUI::Base64ToSprite(base64Sprite, 620, 620);
    cookiesTextMesh->set_text(il2cpp_utils::createcsstr("Cookies: " + std::to_string(++cookies)));
    UnityEngine::UI::Image* image = BeatSaberUI::CreateImage(viewController->get_rectTransform(), cookieSprite, UnityEngine::Vector2(rand()%(68*2)-68, rand()%(32*2)-32), UnityEngine::Vector2(8.0f, 8.0f));
    UnityEngine::Object::Destroy(image->get_gameObject(), 4);
}

void CustomUITest::CookieClickerViewController::DidActivate(bool firstActivation, HMUI::ViewController::ActivationType activationType){
    if(firstActivation){
        BeatSaberUI::CreateText(get_rectTransform(), "CookieClicker", UnityEngine::Vector2(12.0f, 32.0f))->set_fontSize(8.0f);
        cookiesTextMesh = BeatSaberUI::CreateText(get_rectTransform(), "Cookies: 0", UnityEngine::Vector2(19.0f, 6.0f));
        cookiesTextMesh->set_fontSize(6.0f);
        BeatSaberUI::CreateUIButton(get_rectTransform(), "OkButton", UnityEngine::Vector2(0.0f, -2.0f), UnityEngine::Vector2(28.0f, 10.0f), il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction*)), this, OnTestButtonClick), "Cookie", nullptr);
    }
}

void CustomUITest::CookieClickerViewController::DidDeactivate(HMUI::ViewController::DeactivationType deactivationType) {
    cookieSprite = nullptr;
}