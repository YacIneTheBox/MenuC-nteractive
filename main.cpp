#include <iostream>
#include "raylib.h"

#include "AudioManager.h"
#include "Button.h"
#include "MenuScene.h"

using namespace std;

int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;

    SceneType currentScene = SceneType::Menu;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Interactive");
    SetTargetFPS(60);

    AudioManager audio;
    audio.Init();

    Sound sfxClick = LoadSound("Audio/Click.mp3");
    SetSoundVolume(sfxClick, 0.5f);

    MenuScene menu;
    menu.Init(sfxClick, SCREEN_WIDTH, SCREEN_HEIGHT);   // une seule fois

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            currentScene = SceneType::Menu;
        }

        audio.SetScene(currentScene);
        audio.Update();

        BeginDrawing();

        switch (currentScene) {
            case SceneType::Menu: {
                SceneType next = menu.UpdateAndDraw();
                if (next == SceneType::Main)      currentScene = SceneType::Main;
                else if (next == SceneType::Settings) currentScene = SceneType::Settings;
                else if (next == SceneType::Credits) currentScene = SceneType::Credits;
            } break;

            case SceneType::Main:
                ClearBackground(WHITE);
                break;

            case SceneType::Settings:
                ClearBackground(GREEN);
                break;

            case SceneType::Credits:
                ClearBackground(BLUE);
                break;

            default:
                ClearBackground(RED);
                break;
        }

        EndDrawing();
    }

    UnloadSound(sfxClick);
    audio.ShutDown();
    CloseWindow();
    return 0;
}
