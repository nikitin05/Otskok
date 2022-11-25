#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "Engine.h"
#include "iostream"
#include "cmath"
#include "iomanip"

int main()
{
    std::cout << std::setprecision(10);
    srand(time( 0 ));
    Engine engine;
    engine.start();
    return 0;
}