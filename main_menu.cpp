//
//  main_menu.cpp
//  SFMLPromisingTest
//
//  Created by Joseph Simeone on 5/3/23.
//

#include "main_menu.h"
#include "Button.h"
#include "AudioConstants.h"

Main_Menu::Main_Menu() {
    init_window();
    init_textures();
    init_buttons();
}

void Main_Menu::init_window() {
    //Make the window
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Cargo Chaos");
    window->setFramerateLimit(60);
}

void Main_Menu::init_textures() {
    // Load the background image
    if (!background_texture.loadFromFile("assets/backdrop.png")) {
        std::cout << "Error loading background image!" << std::endl;
    }
    
    sf::Vector2u backgroundSize = background_texture.getSize();
    sf::Sprite backgroundSprite(background_texture);
    
    //Calculate scale factors
    float scaleX = static_cast<float>(window->getSize().x) / backgroundSize.x;
    float scaleY = static_cast<float>(window->getSize().y) / backgroundSize.y;
    
    background_sprite.setScale(scaleX, scaleY);

    
    // Load Logo Sprite and Set Position
    if (!logo_texture.loadFromFile("assets/Cargo-Chaos.png")) {
        std::cout << "Error loading logo texture! " << std::endl;
    }
    logo_sprite.setTexture(logo_texture);
    // Set the scale
    logo_sprite.setScale(0.8f, 0.8f);

    // Set the position
    float logoX = window->getSize().x / 2.0f - logo_sprite.getGlobalBounds().width / 2.0f;
    float logoY = window->getSize().y * 0.25f - logo_sprite.getGlobalBounds().height / 2.0f;
    logo_sprite.setPosition(logoX, logoY);
}

void Main_Menu::init_buttons() {
    // Initialize buttons
    Button playButton(sf::Vector2f(100, 50), sf::Vector2f(350, 275), "Play", sf::Color(255, 51, 0));
    Button instructionsButton(sf::Vector2f(150, 50), sf::Vector2f(325, 350), "Intructions", sf::Color(255, 51, 0));
    Button exitButton(sf::Vector2f(100, 50), sf::Vector2f(350, 425), "Exit", sf::Color(255, 51, 0));

    // Create the "Back" button for the instructions page
    Button backButton(sf::Vector2f(100, 50), sf::Vector2f(350, 500), "Back", sf::Color(255, 51, 0));
    main_menu_buttons = { &playButton, &instructionsButton, &exitButton };
    selected_button = 0;
}

void Main_Menu::update() {
    if (AudioConstants::backgroundMusic.getStatus() != sf::Music::Status::Playing) {
        AudioConstants::backgroundMusic.setLoop(true);
        AudioConstants::backgroundMusic.play();
    }
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        
        if (event.type == sf::Event::KeyPressed) {
            AudioConstants::selectSound.play();
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                if (selected_button > 0) {
                    selected_button--;
                }
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                AudioConstants::selectSound.play();
                if (selected_button < main_menu_buttons.size() - 1) {
                    selected_button++;
                }
            }
            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                if (selected_button == 0) {
                    AudioConstants::clickSound.play();
                    //TODO: gameState = GameState::Playing;
                    
                }
                else if (selected_button == 1) {
                    //TODO: gameState = GameState::Instructions;
                }
                else if (selected_button == 2) {
                    window->close();
                }
            }
        }
    }
}

void Main_Menu::render() {
    cout << "Hit render function" << endl;
    window->clear();
    cout << "Ran window clear" << endl;
    window->draw(background_sprite); // Render the background image
    cout << "Draw sprite" << endl;
    window->draw(logo_sprite); // Logo
    cout << "Draw logo sprite" << endl;
    
    for (int i = 0; i < main_menu_buttons.size(); i++) {
        main_menu_buttons[i]->update_selected(i == selected_button);
        window->draw(main_menu_buttons[i]->get_button_shape());
        window->draw(main_menu_buttons[i]->get_button_text());
    }
    cout << "Drew buttons" << endl;
    
    window->display();
    cout << "Display window" << endl;
}

void Main_Menu::key_press_checker() {
    
}
