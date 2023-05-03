#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "Button.h"
#include "AudioConstants.h"
#include "main_menu.h"

enum class GameState {
    MainMenu,
    Playing,
    Instructions
};

int main() {
    GameState gameState = GameState::MainMenu;
    Main_Menu menu;
    
    //Load sounds
    AudioConstants::loadSounds();

    // Get the original size of the image

    // Calculate the scale factors for width and height

    // Scale the backgroundSprite using the calculated scale factors

    while (true) {
        if (gameState == GameState::MainMenu) {
            menu.render();
        } else if (gameState == GameState::Playing) {
            AudioConstants::backgroundMusic.stop();
            if (AudioConstants::gameplayMusic.getStatus() != sf::Music::Status::Playing) {
                AudioConstants::gameplayMusic.setLoop(true);
                AudioConstants::gameplayMusic.play();
            }

            Game game;

            game.spawn_cargo_node(500, 500, 0);
            game.spawn_cargo_node(400, 400, 1);
            game.spawn_cargo_node(300, 300, 2);
            game.spawn_laser_node(600, 600);

            while (game.is_running()) {
                game.update();
                game.render();
            }

            AudioConstants::gameplayMusic.stop(); // Stop the gameplay music when the game ends
            gameState = GameState::MainMenu;
//        } else if (gameState == GameState::Instructions) {
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed) {
//                    window.close();
//                }
//
//                if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)) {
//                    gameState = GameState::MainMenu;
//                }
//            }
//
//            window.clear();
//
//            sf::Font font;
//            font.loadFromFile("assets/VinaSans-Regular.ttf");
//            sf::Text instructionsText;
//            instructionsText.setFont(font);
//            instructionsText.setString("Instructions: \n\nWASD to move\nSpace to interact with objects\nComplete task by moving nodes to clear area to pickup points.");
//            instructionsText.setCharacterSize(24);
//            instructionsText.setFillColor(sf::Color::Red);
//            instructionsText.setPosition(250, 200);
//
//            window.draw(instructionsText);
//            backButton.render(window, false);
//            window.display();
        }
    }
            

    return 0;
}
