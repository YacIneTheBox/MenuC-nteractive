#include <iostream>
#include "raylib.h"
#include <vector>

using namespace std;

int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;

    Color buttonColorCountour = WHITE;
    Color buttonColorFill = BLACK;
    Color textColor = WHITE;

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
        DrawRectangle(MenuButton_Start.x, MenuButton_Start.y, MenuButton_Start.width, MenuButton_Start.height, buttonColorCountour);
        DrawRectangle(MenuButton_Start.x+5, MenuButton_Start.y+5, MenuButton_Start.width-10, MenuButton_Start.height-10, buttonColorFill);
        DrawText("Proceed", MenuButton_Start.x+60, MenuButton_Start.y+20, 40, textColor);

        EndDrawing();
    }

    return 0;
}
