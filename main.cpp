#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "game.h"
//#include "StartupPage.h"

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "cargoChaos");
    window.setFramerateLimit(60);

//    sf::Font font;
//    if (!font.loadFromFile("path/to/your/font.ttf")) {
//        std::cout << "Error loading font" << std::endl;
//        return -1;
//    }

//    StartupPage startupPage(font, window);
    Game game;

//    bool gameStarted = false;
    game.spawn_node(500, 500, "circle.png");

    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    if (startupPage.playButtonClicked()) {
//                        gameStarted = true;
//                        game.spawn_node(500, 500, "circle.png");
//                    }
//                }
//            }
//        }
//        if (!gameStarted) {
//            startupPage.draw(window);
//        } else {
        game.update();
        game.render();
//        }

        window.display();
    }

    return 0;
}
