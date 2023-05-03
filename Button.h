// Button.h
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f position, const std::string& text, sf::Color buttonColor);

    void render(sf::RenderWindow& window, bool selected);
    bool isClicked(sf::RenderWindow& window);

private:
    sf::RectangleShape buttonShape;
    sf::Text label;
    sf::Font font;
};
