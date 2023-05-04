/**
 * Project 08: Cargo Chaos button class method definitions.
 * @file button.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#include "Button.h"

 /**
  * @brief: Constructor for a button object.
  * @param size The desired length and width of the button in pixels.
  * @param position The x and y position of the button in pixels.
  * @param text the text to be displayed on the button.
  * @param buttonColor The desired color of the button.
  */
Button::Button(sf::Vector2f size, sf::Vector2f position, 
               const std::string& text, sf::Color buttonColor) {
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(buttonColor);

    font.loadFromFile("assets/VinaSans-Regular.ttf");
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, 
                    textRect.top + textRect.height / 2.0f);
    label.setPosition(buttonShape.getPosition() + 
                      sf::Vector2f(buttonShape.getSize().x / 2.0f, 
                      buttonShape.getSize().y / 2.0f));
}

/**
 * @brief: Renders the button to the menu window.
 * @param window The window to render the button to.
 * @param selected A boolean indicating whether or not the button is currently selected.
 */
void Button::render(sf::RenderWindow& window, bool selected) {
    if (selected) {
        buttonShape.setFillColor(sf::Color(255, 51, 0));
    }
    else {
        buttonShape.setFillColor(sf::Color(100, 100, 100));
    }
    window.draw(buttonShape);
    window.draw(label);
}

/**
 * @brief: Returns whether or not the button is being clicked.
 * @param window The window the button is currently rendered to.
 * @return: True if the button is clicked, false otherwise.
 */
bool Button::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return buttonShape.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }
    return false;
}
