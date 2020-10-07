#include "CookieClickerViewController.hpp"

#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutRebuilder.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "Base64Sprite.hpp" 
#include <stdlib.h>

#include "customlogger.hpp"

#include <sstream>
#include <string>

using namespace QuestUI;

DEFINE_CLASS(CustomUITest::CookieClickerViewController);

void OnTestButtonClick(CustomUITest::CookieClickerViewController* viewController, UnityEngine::UI::Button* button) {
    if(!viewController->cookieSprite)
        viewController->cookieSprite = BeatSaberUI::Base64ToSprite(base64Sprite, 620, 620);
    viewController->cookiesTextMesh->set_text(il2cpp_utils::createcsstr("Cookies: " + std::to_string(++viewController->cookies)));
    UnityEngine::UI::Image* image = BeatSaberUI::CreateImage(viewController->get_rectTransform(), viewController->cookieSprite, UnityEngine::Vector2(rand()%(68*2)-68, rand()%(32*2)-32), UnityEngine::Vector2(8.0f, 8.0f));
    UnityEngine::Object::Destroy(image->get_gameObject(), 4);
}

void test(UnityEngine::GameObject* obj, int index) {

    getLogger().info("%d %s%s (%d)", index, std::string(index*2, '-').c_str(), to_utf8(csstrtostr(obj->get_name())).c_str(), obj->get_transform()->get_childCount());
    for(int i = 0;i<obj->get_transform()->get_childCount(); i++) {
        UnityEngine::Transform* transform = obj->get_transform()->GetChild(i);
        test(transform->get_gameObject(), index+1);
    }
}

void CustomUITest::CookieClickerViewController::DidActivate(bool firstActivation, HMUI::ViewController::ActivationType activationType){
    if(activationType == HMUI::ViewController::ActivationType::AddedToHierarchy && firstActivation) {
        /*BeatSaberUI::CreateText(get_rectTransform(), "CookieClicker", UnityEngine::Vector2(12.0f, 32.0f))->set_fontSize(8.0f);
        cookiesTextMesh = BeatSaberUI::CreateText(get_rectTransform(), "Cookies: 0", UnityEngine::Vector2(19.0f, 6.0f));
        cookiesTextMesh->set_fontSize(6.0f);
        cookieSprite = nullptr;
        cookies = 0;
        BeatSaberUI::CreateUIButton(get_rectTransform(), "OkButton", UnityEngine::Vector2(0.0f, -2.0f), UnityEngine::Vector2(28.0f, 10.0f), il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction*)), this, OnTestButtonClick), "Cookie", nullptr);
        */
        //UnityEngine::GameObject* toggle = BeatSaberUI::CreateToggle(get_rectTransform(), "Toggle", il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction_1<bool>>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction_1<bool>*)), this, +[](CustomUITest::CookieClickerViewController* viewController, bool toggle) { getLogger().info("toggle %d", toggle); }));
        //BeatSaberUI::AddHoverHint(toggle, "HoverHint");
        //BeatSaberUI::CreateIncrementSetting(get_rectTransform(), UnityEngine::Vector2(60.0f, -16.0f), "IncrementSetting", 2, 0.5f, 10.0f);

        /*UnityEngine::GameObject* container = BeatSaberUI::CreateScrollView(get_transform());
        auto button = BeatSaberUI::CreateUIButton(container->get_transform(), "OkButton", il2cpp_utils::MakeAction<UnityEngine::Events::UnityAction>(il2cpp_functions::class_get_type(classof(UnityEngine::Events::UnityAction*)), this, OnTestButtonClick), "Cookie", nullptr);
        auto inc = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "IncrementSetting", 2, 0.5f, 10.0f);
        //test(this->get_gameObject(), 0);

        auto* scrollView = container->GetComponent<QuestUI::ExternalComponents*>()->Get<HMUI::ScrollView*>();
        getLogger().info("contentHeight %f", scrollView->contentHeight);*/

        BeatSaberUI::CreateKeyboard(get_rectTransform())->GetComponent<QuestUI::ExternalComponents*>()->Get<UnityEngine::RectTransform*>()->get_gameObject()->SetActive(true);
    }
}

void CustomUITest::CookieClickerViewController::DidDeactivate(HMUI::ViewController::DeactivationType deactivationType) {
    cookieSprite = nullptr;
}