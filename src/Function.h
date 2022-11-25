//
// Created by nikitinfs.24 on 15.11.2022.
//

#ifndef OTSKOK_FUNCTION_H
#define OTSKOK_FUNCTION_H

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics.hpp>
#include "cmath"
#include <iostream>

using namespace sf;


Vector2f rotation(Vector2f a, double angle);

float scalar(Vector2f a, Vector2f b);

float max(float a, float b);

#endif //OTSKOK_FUNCTION_H
