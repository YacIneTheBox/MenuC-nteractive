#include <iostream>
#include "raylib.h"

using namespace std;

int main() {
    InitWindow(1200,800,"Menu Interactive");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    return 0;
}
