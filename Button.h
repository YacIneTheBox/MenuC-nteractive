#pragma once

#include "AudioManager.h"
#include "raylib.h"
#include <string>

using namespace std;

class Button {
public:
    Rectangle rectangle;
    string text;
    Color colorCountour;
    Color colorFill;
    Color textColor;
    Sound sfxClick;
    SceneType scene;

    Button(Rectangle r, const string& t, Color border, Color fill,
           Color textCol, Sound sfx, SceneType s)
        : rectangle(r), text(t), colorCountour(border), colorFill(fill),
          textColor(textCol), sfxClick(sfx), scene(s) {}

    bool IsHovered() const {
        return CheckCollisionPointRec(GetMousePosition(), rectangle);
    }

    // return Scene
    SceneType Update() {
        // visuel
        if (IsHovered()) {
            colorFill = WHITE;
            textColor = BLACK;
        } else {
            colorFill = BLACK;
            textColor = WHITE;
        }

        // clic
        if (IsHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(sfxClick);
            return scene;
        }

        return SceneType::Menu;
    }

    void Draw() const {
        DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, colorCountour);
        DrawRectangle(rectangle.x + 5, rectangle.y + 5, rectangle.width - 10, rectangle.height - 10, colorFill);
        DrawText(text.c_str(), rectangle.x + 60, rectangle.y + 20, 40, textColor);
    }
};
