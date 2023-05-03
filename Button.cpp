// Button.cpp
#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f position, const std::string& text, sf::Color buttonColor) {
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(buttonColor); // Set the button color

    font.loadFromFile("assets/VinaSans-Regular.ttf");
    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White); // Set the text color to white for better visibility
    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    label.setPosition(buttonShape.getPosition() + sf::Vector2f(buttonShape.getSize().x / 2.0f, buttonShape.getSize().y / 2.0f));
}

void Button::update_selected(bool selected) {
    if (selected) {
        buttonShape.setFillColor(sf::Color(255, 51, 0));
    }
    else {
        buttonShape.setFillColor(sf::Color(100, 100, 100));
    }
}

sf::RectangleShape Button::get_button_shape() {
    return buttonShape;
}

sf::Text Button::get_button_text() {
    return label;
}

bool Button::isClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return buttonShape.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }
    return false;
}
