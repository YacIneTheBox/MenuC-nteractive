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

    Button(Rectangle rect, string txt, Color countour, Color fill, Color text)
        : rectangle(rect), text(txt), colorCountour(countour), colorFill(fill), textColor(text) {}

    void WhenHoovered(){
        if (CheckCollisionPointRec(GetMousePosition(),rectangle)){
            colorFill = WHITE;
            textColor = BLACK;
        }else{
            colorFill = BLACK;
            textColor = WHITE;
        }
    }

    void Draw(){
        DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, colorCountour);
        DrawRectangle(rectangle.x+5, rectangle.y+5, rectangle.width-10, rectangle.height-10, colorFill);
        DrawText(text.c_str(), rectangle.x+60, rectangle.y+20, 40, textColor);
    }
};


void DrawingButtons(Rectangle cadre,string text);
int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;

    vector<Button> buttons;
    Rectangle MenuButton_Start = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)3 - 50, 300, 80};
    Button MenuButton_Start_Button(MenuButton_Start, "Proceed", WHITE, BLACK, WHITE);
    buttons.push_back(MenuButton_Start_Button);

    Rectangle MenuButton_Settings = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)2 - 50, 300, 80};
    Button MenuButton_Settings_Button(MenuButton_Settings,"Settings",WHITE,BLACK,WHITE);
    buttons.push_back(MenuButton_Settings_Button);

    Rectangle MenuButton_Exit = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)1.5f - 50, 300, 80};
    Button MenuButton_Exit_Button(MenuButton_Exit,"Exit",WHITE,BLACK,WHITE);
    buttons.push_back(MenuButton_Exit_Button);


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Interactive");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        // hovering
        for (int i = 0;i<buttons.size();i++){
            buttons[i].WhenHoovered();
        }

        // drawing here
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0;i<buttons.size();i++){
            buttons[i].Draw();
        }

        EndDrawing();
    }

    return 0;
}
