#include "CookieClickerViewController.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutRebuilder.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "Base64Sprite.hpp" 
#include <stdlib.h>

#include "customlogger.hpp"

#include <sstream>
#include <string>

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

DEFINE_CLASS(CustomUITest::CookieClickerViewController);

void OnTestButtonClick(CustomUITest::CookieClickerViewController* viewController, Button* button) {
    if(!viewController->cookieSprite)
        viewController->cookieSprite = BeatSaberUI::Base64ToSprite(base64Sprite, 620, 620);
    viewController->cookiesTextMesh->set_text(il2cpp_utils::createcsstr("Cookies: " + std::to_string(++viewController->cookies)));
    Image* image = BeatSaberUI::CreateImage(viewController->get_rectTransform(), viewController->cookieSprite, UnityEngine::Vector2(rand()%(68*2)-68, rand()%(32*2)-32), UnityEngine::Vector2(8.0f, 8.0f));
    Object::Destroy(image->get_gameObject(), 4);
}
void CustomUITest::CookieClickerViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation) {
        /*UnityEngine::GameObject* container = BeatSaberUI::CreateScrollView(get_transform());
        auto button = BeatSaberUI::CreateUIButton(container->get_transform(), "OkButton", il2cpp_utils::MakeDelegate<UnityAction*>(classof(UnityAction*), this, OnTestButtonClick), "Cookie", nullptr);
        auto inc = BeatSaberUI::CreateIncrementSetting(container->get_transform(), "IncrementSetting", 2, 0.5f, 10.0f);
        //test(this->get_gameObject(), 0);

        auto* scrollView = container->GetComponent<QuestUI::ExternalComponents*>()->Get<HMUI::ScrollView*>();
        getLogger().info("contentHeight %f", scrollView->contentHeight);*/
        BeatSaberUI::CreateText(get_rectTransform(), "CookieClicker", UnityEngine::Vector2(12.0f, 32.0f))->set_fontSize(8.0f);

        VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(get_rectTransform());
		layout->set_spacing(3.5f);
		layout->get_gameObject()->AddComponent<Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
        layout->get_gameObject()->GetComponent<ContentSizeFitter*>()->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
		layout->set_padding(UnityEngine::RectOffset::New_ctor(3, 3, 2, 2));


        cookiesTextMesh = BeatSaberUI::CreateText(layout->get_transform(), "Cookies: 0", UnityEngine::Vector2(19.0f, 6.0f));
        cookiesTextMesh->set_fontSize(6.0f);
        cookieSprite = nullptr;
        cookies = 0;
        Button* cookieButton = BeatSaberUI::CreateUIButton(layout->get_transform(), "Cookie", il2cpp_utils::MakeDelegate<UnityAction*>(classof(UnityAction*), this, OnTestButtonClick));
        BeatSaberUI::AddHoverHint(cookieButton->get_gameObject(), "Get a cookie");
        BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "TestIncrementSetting", 2, 0.5f, 10.0f, il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), this, +[](CookieClickerViewController* view, float value) { getLogger().info("questui TestIncrementSetting: %f", value); }));
        BeatSaberUI::CreateToggle(layout->get_transform(), "TestToggle", il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this, +[](CookieClickerViewController* view, bool value) { getLogger().info("questui TestToggle: %d", value);  }));
        BeatSaberUI::CreateStringSetting(layout->get_transform(), "TestStringSetting", "", il2cpp_utils::MakeDelegate<UnityAction_1<Il2CppString*>*>(classof(UnityAction_1<Il2CppString*>*), this, +[](CustomUITest::CookieClickerViewController* self, Il2CppString* value) { getLogger().info("questui TestStringSetting: %s", to_utf8(csstrtostr(value)).c_str()); }));
    }
}

void CustomUITest::CookieClickerViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    cookieSprite = nullptr;
}