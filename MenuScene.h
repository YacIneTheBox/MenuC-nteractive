#pragma once

#include "Button.h"
#include <vector>

using namespace std;

class MenuScene {
public:
    vector<Button> buttons;

    void Init(Sound clickSound, int screenWidth, int screenHeight) {
        buttons.clear();

        Rectangle MenuButton_Start = { screenWidth/2.0f - 150, screenHeight/3.0f - 50, 300, 80 };
        Button MenuButton_Start_Button(MenuButton_Start, "Proceed", WHITE, BLACK, WHITE, clickSound, SceneType::Main);
        buttons.push_back(MenuButton_Start_Button);

        Rectangle MenuButton_Settings = { screenWidth/2.0f - 150, screenHeight/2.0f - 50, 300, 80 };
        Button MenuButton_Settings_Button(MenuButton_Settings, "Settings", WHITE, BLACK, WHITE, clickSound, SceneType::Settings);
        buttons.push_back(MenuButton_Settings_Button);

        Rectangle MenuButton_Exit = { screenWidth/2.0f - 150, screenHeight/1.5f - 50, 300, 80 };
        Button MenuButton_Exit_Button(MenuButton_Exit, "Exit", WHITE, BLACK, WHITE, clickSound, SceneType::Credits);
        buttons.push_back(MenuButton_Exit_Button);
    }

    SceneType UpdateAndDraw() {
        ClearBackground(BLACK);

        SceneType nextScene = SceneType::Menu;

        for (Button& button : buttons) {
            SceneType res = button.Update();
            button.Draw();
            if (res != SceneType::Menu) {
                nextScene = res;
                break;
            }
        }

        return nextScene;
    }
};
