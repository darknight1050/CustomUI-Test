#include "CookieClickerViewController.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "Base64Sprite.hpp" 
#include <stdlib.h>

#include "customlogger.hpp"
#include "ModConfig.hpp"

#include <sstream>
#include <string>
#include <vector>

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;
using namespace TMPro;

DEFINE_TYPE(CustomUITest, CookieClickerViewController);

void TestCanvas() {
    GameObject* canvas = BeatSaberUI::CreateCanvas();
    canvas->AddComponent<CurvedCanvasSettings*>()->SetRadius(130);
    RectTransform* transform = canvas->GetComponent<RectTransform*>();
    transform->set_position(UnityEngine::Vector3(0.0f, 0.1f, 2.2f));
    transform->set_eulerAngles(UnityEngine::Vector3(60.0f, 0.0f, 0.0f));
    VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(transform);
    GameObject* layoutGameObject = layout->get_gameObject();
    layoutGameObject->GetComponent<ContentSizeFitter*>()->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    layoutGameObject->AddComponent<Backgroundable*>()->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    layout->set_padding(UnityEngine::RectOffset::New_ctor(3, 4, 2, 2));
    TextMeshProUGUI* modInfoText = BeatSaberUI::CreateText(layout->get_transform(), "TestText");
    modInfoText->set_alignment(TextAlignmentOptions::Center);
    modInfoText->set_fontSize(4.8f);
}

void CustomUITest::CookieClickerViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation) {
        TestCanvas();

        get_gameObject()->AddComponent<Touchable*>();

        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        cookiesTextMesh = BeatSaberUI::CreateText(container->get_transform(), "Cookies: 0", UnityEngine::Vector2(19.0f, 6.0f));
        cookiesTextMesh->set_fontSize(6.0f);
        cookieSprite = nullptr;
        cookies = 0;

        Button* cookieButton = BeatSaberUI::CreateUIButton(container->get_transform(), "Cookie", 
            [this]() {
                if(!this->cookieSprite)
                    this->cookieSprite = BeatSaberUI::Base64ToSprite(base64Sprite);
                this->cookiesTextMesh->set_text(il2cpp_utils::createcsstr("Cookies: " + std::to_string(++this->cookies)));
                Image* image = BeatSaberUI::CreateImage(this->get_rectTransform(), this->cookieSprite, UnityEngine::Vector2(rand()%(68*2)-68, rand()%(32*2)-32), UnityEngine::Vector2(8.0f, 8.0f));
                Object::Destroy(image->get_gameObject(), 4);
            });
        BeatSaberUI::AddHoverHint(cookieButton->get_gameObject(), "Get a cookie");
        
        BeatSaberUI::CreateIncrementSetting(container->get_transform(), "TestIncrementSetting", 2, 0.5f, 10.0f, 5.0f, 15.0f,
            [](float value) { 
                getLogger().info("questui TestIncrementSetting: %f", value); 
            });
        
        BeatSaberUI::CreateToggle(container->get_transform(), "TestToggle", true,
            [](bool value) { 
                getLogger().info("questui TestToggle: %d", value);  
            });

        BeatSaberUI::CreateColorPicker(container->get_transform(), "TestColorPicker", UnityEngine::Color::get_green(), 
            [](UnityEngine::Color color, GlobalNamespace::ColorChangeUIEventType eventType) { 
                getLogger().info("questui TestColorPicker: %f %f %f %d", color.r, color.g, color.b, eventType); 
            });

        BeatSaberUI::CreateStringSetting(container->get_transform(), "TestStringSetting", "", 
            [](std::string value) { 
                getLogger().info("questui TestStringSetting: %s", value.c_str()); 
            });
        
        std::vector<std::string> values = {"Value 1", "Value 2", "Value 3", "Value 4", "Value 5", "Value 6"};
        BeatSaberUI::CreateDropdown(container->get_transform(), "TestDropdown", values[3], values,  
            [](std::string value) { 
                getLogger().info("questui TestDropdown: %s", value.c_str()); 
            });

        //config-utils macros
        AddConfigValueToggle(container->get_transform(), getModConfig().ModBool);
        AddConfigValueIncrementInt(container->get_transform(), getModConfig().ModInt, 2, -1337, 1337);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ModFloat, 1, 0.5f, 0.0f, 420.0f);
        AddConfigValueStringSetting(container->get_transform(), getModConfig().ModString);
        AddConfigValueColorPicker(container->get_transform(), getModConfig().ModColor);

    }
}

void CustomUITest::CookieClickerViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    cookieSprite = nullptr;
}