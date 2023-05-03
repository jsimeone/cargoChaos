#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include "Button.h"
#include "AudioConstants.h"

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
        std::cout << "Error loading background image!" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Load Logo Sprite and Set Position
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    if (!logoTexture.loadFromFile("assets/Cargo-Chaos.png")) {
        std::cout << "Error loading logo texture! " << std::endl;
    }
    logoSprite.setTexture(logoTexture);
    // Set the scale
    logoSprite.setScale(0.8f, 0.8f);

    // Set the position
    float logoX = window.getSize().x / 2.0f - logoSprite.getGlobalBounds().width / 2.0f;
    float logoY = window.getSize().y * 0.25f - logoSprite.getGlobalBounds().height / 2.0f;
    logoSprite.setPosition(logoX, logoY);




    // Get the original size of the image
    sf::Vector2u backgroundSize = backgroundTexture.getSize();

    // Calculate the scale factors for width and height
    float scaleX = static_cast<float>(window.getSize().x) / backgroundSize.x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundSize.y;

    // Scale the backgroundSprite using the calculated scale factors
    backgroundSprite.setScale(scaleX, scaleY);

    // Initialize buttons
    Button playButton(sf::Vector2f(100, 50), sf::Vector2f(350, 275), "Play", sf::Color(255, 51, 0));
    Button instructionsButton(sf::Vector2f(150, 50), sf::Vector2f(325, 350), "Intructions", sf::Color(255, 51, 0));
    Button exitButton(sf::Vector2f(100, 50), sf::Vector2f(350, 425), "Exit", sf::Color(255, 51, 0));

    // Create the "Back" button for the instructions page
    Button backButton(sf::Vector2f(100, 50), sf::Vector2f(350, 500), "Back", sf::Color(255, 51, 0));
    std::vector<Button*> mainMenuButtons = { &playButton, &instructionsButton, &exitButton };
    int selectedButton = 0;



    sf::Music backgroundMusic;
    AudioConstants::loadSounds();
    if (!backgroundMusic.openFromFile("assets/soundtrack.wav")) {
        std::cout << "Error loading sountrack!" << std::endl;
        return 1;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    if (!AudioConstants::gameplayMusic.openFromFile("assets/Gameplay.wav")) {
        std::cout << "Error loading gameplay music!" << std::endl;
    }


    while (window.isOpen()) {
        sf::Event event;
        GameState prevState = gameState;

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
                    AudioConstants::selectSound.play();
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        if (selectedButton > 0) {
                            selectedButton--;
                        }
                    }
                    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        AudioConstants::selectSound.play();
                        if (selectedButton < mainMenuButtons.size() - 1) {
                            selectedButton++;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                        if (selectedButton == 0) {
                            AudioConstants::clickSound.play();
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
            window.draw(logoSprite); // Logo

            for (int i = 0; i < mainMenuButtons.size(); i++) {
                mainMenuButtons[i]->render(window, i == selectedButton);
            }
            window.display();
        }
        else if (gameState == GameState::Playing) {
            backgroundMusic.stop();
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
            instructionsText.setString("Instructions: \n\nWASD to move\nSpace to interact with objects\nComplete task by moving nodes to clear area to pickup points.");
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
