#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "game.h"

using namespace sf;

int main() {
    Game game;
    game.spawn_node(500, 500, "circle.png");
    while (game.is_running()) {
        game.update();
        game.render();
    }

    return 0;
}

