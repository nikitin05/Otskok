//
// Created by nikitinf05 on 13.11.2022.
//

#ifndef OTSKOK_ENGINE_H
#define OTSKOK_ENGINE_H


#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Circle.h"
#include <bits/stdc++.h>

using namespace sf;


class Engine
{
private:
    Clock clock;

    Vector2f Resolution;
    Vector2f event_resolution;
    RenderWindow m_Window;

    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    Texture ball;
    Font font;

    Ball m_Ball;
    Circle m_Circle;

    float target;
    Text target_text;

    int game_speed = 100;

    enum physicOverlay { physicOverlay_Open, physicOverlay_Close };
    const char* physicOverlay_names[2] = { "Вкл", "Выкл"};
    int condition_physicOverlay = physicOverlay_Close;

    enum game { game_Open, game_Close };
    const char* game_names[2] = { "Вкл", "Выкл"};
    int condition_game = game_Close;

    enum mode { game_12, game_16 };
    const char* game_mode_names[2] = { "12", "16"};
    int  game_mode = game_16;

    int menu();
    void setLevel();


    bool checkWin();

    void input();
    void update(float dtAsSeconds);
    void draw();
    void impact_draw();
    void endEvent(int type_of_damage);

    void saveToFile();
    void ShowFiles();

    void event(int event_id);
    int event_id = 0;

public:

    Engine();
    void start();
    void studing();
};


#endif //OTSKOK_ENGINE_H
