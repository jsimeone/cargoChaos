#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Button.h"

enum class GameState {
    MainMenu,
    Playing,
    Instructions
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cargo Chaos");
    window.setFramerateLimit(60);

    GameState gameState = GameState::MainMenu;

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/backdrop.png")) {
        std::cout << "Error loading bacsskground image!" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Get the original size of the image
    sf::Vector2u backgroundSize = backgroundTexture.getSize();

    // Calculate the scale factors for width and height
    float scaleX = static_cast<float>(window.getSize().x) / backgroundSize.x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundSize.y;

    // Scale the backgroundSprite using the calculated scale factors
    backgroundSprite.setScale(scaleX, scaleY);

    // Initialize buttons
     // Create the "Play" button
    Button playButton(sf::Vector2f(100, 50), sf::Vector2f(350, 275), "Play", sf::Color(0, 128, 128));

    // Create the "Instructions" button
    Button instructionsButton(sf::Vector2f(150, 50), sf::Vector2f(325, 350), "Intructions", sf::Color(0, 128, 128));

    // Create the "Exit" button
    Button exitButton(sf::Vector2f(100, 50), sf::Vector2f(350, 425), "Exit", sf::Color(0, 128, 128));


    // Create the "Back" button for the instructions page
    Button backButton(sf::Vector2f(100, 50), sf::Vector2f(350, 500), "Back", sf::Color(0, 128, 128));
    std::vector<Button*> mainMenuButtons = { &playButton, &instructionsButton, &exitButton };
    int selectedButton = 0;

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/soundtrack.wav")) {
        std::cout << "Error loading sountrack!" << std::endl;
        return 1;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    while (window.isOpen()) {
        sf::Event event;

        if (gameState == GameState::MainMenu) {
            if (backgroundMusic.getStatus() != sf::Music::Status::Playing) {
                backgroundMusic.play();
            }
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (gameState != GameState::MainMenu) {
                    backgroundMusic.stop();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        if (selectedButton > 0) {
                            selectedButton--;
                        }
                    }
                    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        if (selectedButton < mainMenuButtons.size() - 1) {
                            selectedButton++;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                        if (selectedButton == 0) {
                            gameState = GameState::Playing;
                        }
                        else if (selectedButton == 1) {
                            gameState = GameState::Instructions;
                        }
                        else if (selectedButton == 2) {
                            window.close();
                        }
                    }
                }
            }

            window.clear();
            window.draw(backgroundSprite); // Render the background image
            
            for (int i = 0; i < mainMenuButtons.size(); i++) {
                mainMenuButtons[i]->render(window, i == selectedButton);
            }
            window.display();
        }
        else if (gameState == GameState::Playing) {
            Game game;

            game.spawn_node(500, 500, "circle.png");

            while (game.is_running()) {
                game.update();
                game.render();
            }
            gameState = GameState::MainMenu;
        }
        else if (gameState == GameState::Instructions) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)) {
                    gameState = GameState::MainMenu;
                }
            }

            window.clear();

            sf::Font font;
            font.loadFromFile("assets/VinaSans-Regular.ttf");
            sf::Text instructionsText;
            instructionsText.setFont(font);
            instructionsText.setString("Instructions: \n\nWASD to move\nE to interact with objects\nComplete tasks to win the game");
            instructionsText.setCharacterSize(24);
            instructionsText.setFillColor(sf::Color::Red);
            instructionsText.setPosition(250, 200);

            window.draw(instructionsText);
            backButton.render(window, false);
            window.display();
        }
    }

    return 0;
}