// Button.h
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f position, const std::string& text, sf::Color buttonColor);

    void update_selected(bool selected);
    bool isClicked(sf::RenderWindow& window);
    sf::RectangleShape get_button_shape();
    sf::Text get_button_text();

private:
    sf::RectangleShape buttonShape;
    sf::Text label;
    sf::Font font;
};
