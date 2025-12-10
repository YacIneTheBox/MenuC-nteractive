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

    Button(Rectangle rect, string txt, Color countour, Color fill, Color text,Sound sfx)
        : rectangle(rect), text(txt), colorCountour(countour), colorFill(fill), textColor(text) ,sfxClick(sfx){}

    void WhenHoovered(){
        if (CheckCollisionPointRec(GetMousePosition(),rectangle)){
            colorFill = WHITE;
            textColor = BLACK;
        }else{
            colorFill = BLACK;
            textColor = WHITE;
        }
    }

    void WhenClicked(){
        if (CheckCollisionPointRec(GetMousePosition(),rectangle)
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            PlaySound(sfxClick);
        }
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

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Interactive");
    InitAudioDevice();
    SetTargetFPS(60);

    Music bgMusic = LoadMusicStream("Audio/bg_music.mp3");
    Sound sfxClick = LoadSound("Audio/Click.mp3");
    PlayMusicStream(bgMusic);


    vector<Button> buttons;
    Rectangle MenuButton_Start = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)3 - 50, 300, 80};
    Button MenuButton_Start_Button(MenuButton_Start, "Proceed", WHITE, BLACK, WHITE,sfxClick);
    buttons.push_back(MenuButton_Start_Button);

    Rectangle MenuButton_Settings = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)2 - 50, 300, 80};
    Button MenuButton_Settings_Button(MenuButton_Settings,"Settings",WHITE,BLACK,WHITE,sfxClick);
    buttons.push_back(MenuButton_Settings_Button);

    Rectangle MenuButton_Exit = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)1.5f - 50, 300, 80};
    Button MenuButton_Exit_Button(MenuButton_Exit,"Exit",WHITE,BLACK,WHITE,sfxClick);
    buttons.push_back(MenuButton_Exit_Button);


    while(!WindowShouldClose()){
        UpdateMusicStream(bgMusic);
        // hovering
        for (int i = 0;i<buttons.size();i++){
            buttons[i].WhenHoovered();
        }

        // drawing here
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0;i<buttons.size();i++){
            buttons[i].WhenClicked();
            buttons[i].Draw();
        }

        EndDrawing();
    }


    UnloadMusicStream(bgMusic);
    UnloadSound(sfxClick);
    CloseAudioDevice();

    return 0;
}
