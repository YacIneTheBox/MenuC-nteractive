#include <iostream>
#include "raylib.h"
#include <vector>

using namespace std;

Color buttonColorCountour = WHITE;
Color buttonColorFill = BLACK;
Color textColor = WHITE;


void DrawingButtons(Rectangle cadre,string text);
int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;

    vector<Rectangle> buttons;
    Rectangle MenuButton_Start = {SCREEN_WIDTH/(float)2 - 150, SCREEN_HEIGHT/(float)3 - 50, 300, 80};
    buttons.push_back(MenuButton_Start);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Menu Interactive");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        // hovering
        for (int i = 0;i<buttons.size();i++){
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                buttonColorFill = WHITE;
                textColor = BLACK;
            }else{
                buttonColorFill = BLACK;
                textColor = WHITE;
            }
        }

        // drawing here
        BeginDrawing();
        ClearBackground(BLACK);

        DrawingButtons(MenuButton_Start, "Proceed");

        EndDrawing();
    }

    return 0;
}

void DrawingButtons(Rectangle cadre,string text){
    DrawRectangle(cadre.x, cadre.y, cadre.width, cadre.height, buttonColorCountour);
    DrawRectangle(cadre.x+5, cadre.y+5, cadre.width-10, cadre.height-10, buttonColorFill);
    DrawText(text.c_str(), cadre.x+60, cadre.y+20, 40, textColor);
}
