/**
 * Project 08: Cargo Chaos Button class declaration.
 * @file Button.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f position, 
           const std::string& text, sf::Color buttonColor);

    void render(sf::RenderWindow& window, bool selected);
    bool isClicked(sf::RenderWindow& window);

private:
    sf::RectangleShape buttonShape;
    sf::Text label;
    sf::Font font;
};
#endif //BUTTON_H
