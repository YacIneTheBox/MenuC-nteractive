#include <iostream>
#include "raylib.h"
#include <vector>
using namespace std;


class Button {
public:
    Rectangle rectangle;
    string text;
    Color colorCountour;
    Color colorFill;
    Color textColor;
    Sound sfxClick;
    int scene;

    Button(Rectangle rect, string txt, Color countour, Color fill, Color text,Sound sfx, int scene)
        : rectangle(rect), text(txt), colorCountour(countour), colorFill(fill), textColor(text) ,sfxClick(sfx), scene(scene){}

    bool WhenHoovered(){
        if (CheckCollisionPointRec(GetMousePosition(),rectangle)){
            colorFill = WHITE;
            textColor = BLACK;
            return true;
        }else{
            colorFill = BLACK;
            textColor = WHITE;
            return false;
        }
    }

    int WhenClicked(){
        if (CheckCollisionPointRec(GetMousePosition(),rectangle)
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            PlaySound(sfxClick);
            return scene;
        }
        return 0;
    }


    void Draw(){
        DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, colorCountour);
        DrawRectangle(rectangle.x+5, rectangle.y+5, rectangle.width-10, rectangle.height-10, colorFill);
        DrawText(text.c_str(), rectangle.x+60, rectangle.y+20, 40, textColor);
    }
};



int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
    int currentScene = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Interactive");
    InitAudioDevice();
    SetTargetFPS(60);

    Music baseSound = LoadMusicStream("Audio/baseSound.mp3");
    Music mainAltSound = LoadMusicStream("Audio/mainAltSound.mp3");
    Music settingsAltSound = LoadMusicStream("Audio/settingsAltSound.mp3");
    Sound sfxClick = LoadSound("Audio/Click.mp3");
    PlayMusicStream(baseSound);
    PlayMusicStream(mainAltSound);
    PlayMusicStream(settingsAltSound);
    SetMusicVolume(baseSound, 1.0f);
    SetSoundVolume(sfxClick,0.7f);



    vector<Button> buttons;
    Rectangle MenuButton_Start = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)3 - 50, 300, 80};
    Button MenuButton_Start_Button(MenuButton_Start, "Proceed", WHITE, BLACK, WHITE,sfxClick,1);
    buttons.push_back(MenuButton_Start_Button);

    Rectangle MenuButton_Settings = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)2 - 50, 300, 80};
    Button MenuButton_Settings_Button(MenuButton_Settings,"Settings",WHITE,BLACK,WHITE,sfxClick,2);
    buttons.push_back(MenuButton_Settings_Button);

    Rectangle MenuButton_Exit = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)1.5f - 50, 300, 80};
    Button MenuButton_Exit_Button(MenuButton_Exit,"Exit",WHITE,BLACK,WHITE,sfxClick,3);
    buttons.push_back(MenuButton_Exit_Button);

    bool isClicked = false;
    bool isHoovered = false;

    float baseVol = 1.0f, baseTarget = 1.0f;
    float mainVol = 0.0f, mainTarget = 0.0f;
    float settingsVol = 0.0f, settingsTarget = 0.0f;

    float fadeSpeed = 0.01f; // plus petit = plus lent


    while(!WindowShouldClose()){
        UpdateMusicStream(baseSound);
        UpdateMusicStream(mainAltSound);
        UpdateMusicStream(settingsAltSound);

        bool anyHoovered = false;

        if (IsKeyPressed(KEY_SPACE)){
            currentScene = 0;
        }

        // drawing here
        BeginDrawing();
        float target;
        cout << "Current Scene: " << currentScene << endl;
        switch (currentScene) {
            case 0:
                ClearBackground(BLACK);
                baseTarget = 1.0f;
                mainTarget = 0.0f;
                settingsTarget = 0.0f;
                for (int i = 0;i<buttons.size();i++){
                    buttons[i].Draw();
                    isHoovered = buttons[i].WhenHoovered();
                    if (isHoovered) anyHoovered = true;
                    currentScene = buttons[i].WhenClicked();
                    if (currentScene != 0)break;
                }
                break;
            case 1:
                ClearBackground(WHITE);
                baseTarget = 1.0f;
                mainTarget = 1.0f;
                settingsTarget = 0.0f;
                break;
            case 2:
                ClearBackground(GREEN);
                baseTarget = 1.0f;
                mainTarget = 0.0f;
                settingsTarget = 1.0f;
                break;
            default:
                ClearBackground(RED);
        }

        auto lerp = [](float current, float target, float speed) {
            return current + (target - current) * speed;
        };

        baseVol     = lerp(baseVol,     baseTarget,     fadeSpeed);
        mainVol     = lerp(mainVol,     mainTarget,     fadeSpeed);
        settingsVol = lerp(settingsVol, settingsTarget, fadeSpeed);

        SetMusicVolume(baseSound,     baseVol);
        SetMusicVolume(mainAltSound,  mainVol);
        SetMusicVolume(settingsAltSound, settingsVol);


        EndDrawing();
    }


    UnloadMusicStream(baseSound);
    UnloadMusicStream(mainAltSound);
    UnloadMusicStream(settingsAltSound);
    UnloadSound(sfxClick);
    CloseAudioDevice();

    return 0;
}
