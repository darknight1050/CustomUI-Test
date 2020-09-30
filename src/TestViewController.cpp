#include "TestViewController.hpp"

#include "UnityEngine/Vector2.hpp"
#include "BeatSaberUI.hpp"

void CustomUITest::TestViewController::Awake(){

}

void CustomUITest::TestViewController::DidActivate(bool firstActivation, HMUI::ViewController::ActivationType activationType){
    if(firstActivation){
        BeatSaberUI::CreateText(get_rectTransform(), "TestText", UnityEngine::Vector2(0.0f, 0.0f));
    }
}

void CustomUITest::TestViewController::DidDeactivate(HMUI::ViewController::DeactivationType deactivationType){
}