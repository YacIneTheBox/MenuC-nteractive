#pragma once

#include "raylib.h"

enum class SceneType {
    Menu = 0,
    Main = 1,
    Settings = 2,
    Credits = 3
};

class AudioManager {
public:
    Music baseSound;
    Music mainAltSound;
    Music settingsAltSound;

    float baseVol = 1.0f, baseTarget = 1.0f;
    float mainVol = 0.0f, mainTarget = 0.0f;
    float settingsVol = 0.0f, settingsTarget = 0.0f;

    float fadeSpeed = 0.025f; // plus petit = plus lent

    void Init() {
        InitAudioDevice();
        baseSound      = LoadMusicStream("Audio/baseSound.mp3");
        mainAltSound   = LoadMusicStream("Audio/mainAltSound.mp3");
        settingsAltSound = LoadMusicStream("Audio/settingsAltSound.mp3");

        PlayMusicStream(baseSound);
        PlayMusicStream(mainAltSound);
        PlayMusicStream(settingsAltSound);

        SetMusicVolume(baseSound,     baseVol);
        SetMusicVolume(mainAltSound,  mainVol);
        SetMusicVolume(settingsAltSound, settingsVol);
    }

    void ShutDown() {
        UnloadMusicStream(baseSound);
        UnloadMusicStream(mainAltSound);
        UnloadMusicStream(settingsAltSound);
        CloseAudioDevice();
    }

    void SetScene(SceneType scene) {
        switch (scene) {
            case SceneType::Menu:
                baseTarget     = 1.0f;
                mainTarget     = 0.0f;
                settingsTarget = 0.0f;
                break;
            case SceneType::Main:
                baseTarget     = 1.0f;
                mainTarget     = 1.0f;
                settingsTarget = 0.0f;
                break;
            case SceneType::Settings:
                baseTarget     = 1.0f;
                mainTarget     = 0.0f;
                settingsTarget = 1.0f;
                break;
            case SceneType::Credits:
                baseTarget     = 1.0f;
                mainTarget     = 0.0f;
                settingsTarget = 0.0f;
                break;
        }
    }

    void Update() {
        UpdateMusicStream(baseSound);
        UpdateMusicStream(mainAltSound);
        UpdateMusicStream(settingsAltSound);

        auto lerp = [](float current, float target, float speed) {
            return current + (target - current) * speed;
        };

        baseVol     = lerp(baseVol,     baseTarget,     fadeSpeed);
        mainVol     = lerp(mainVol,     mainTarget,     fadeSpeed);
        settingsVol = lerp(settingsVol, settingsTarget, fadeSpeed);

        SetMusicVolume(baseSound,       baseVol);
        SetMusicVolume(mainAltSound,    mainVol);
        SetMusicVolume(settingsAltSound, settingsVol);
    }
};
