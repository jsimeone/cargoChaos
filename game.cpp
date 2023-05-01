#include "game.h"


void Game::init_variables() {
	window = nullptr;
}

void Game::init_window() {
	videoMode.height = constants::SCREEN_HEIGHT;
	videoMode.width = constants::SCREEN_WIDTH;

	window = new sf::RenderWindow(videoMode, "CargoChaos", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
    
    view = View({constants::SCREEN_WIDTH/2, constants::SCREEN_HEIGHT/2}, {constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT});
    window->setView(view);

	window->setKeyRepeatEnabled(false);
}

void Game::key_press_checker() {
    if (event.key.code == Keyboard::Escape)
        window->close();
    if (event.key.code == Keyboard::W)
        player.set_moving_up(true);
    if (event.key.code == Keyboard::S)
        player.set_moving_down(true);
    if (event.key.code == Keyboard::A)
        player.set_moving_left(true);
    if (event.key.code == Keyboard::D)
        player.set_moving_right(true);
    if (event.key.code == Keyboard::Space)
        player.toggle_pick_up(nodes);
    if (event.key.code == Keyboard::T)
        screen_shake(2);
    if (event.key.code == Keyboard::LShift)
        player.is_sprinting = true;
}

void Game::key_release_checker() {
    if (event.key.code == Keyboard::W)
        player.set_moving_up(false);
    if (event.key.code == Keyboard::S)
        player.set_moving_down(false);
    if (event.key.code == Keyboard::A)
        player.set_moving_left(false);
    if (event.key.code == Keyboard::D)
        player.set_moving_right(false);
    if (event.key.code == Keyboard::LShift)
        player.is_sprinting = false;
}

void Game::poll_events() {
	//Event polling
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
            key_press_checker();
			break;
		case Event::KeyReleased:
            key_release_checker();
			break;
		case Event::MouseButtonPressed:
			break;
        default:
            break;
		}
	}
}

Game::Game() {
	init_variables();
	init_window();
    get_backdrop();
    get_scorebox();
    frame_counter = 0;
    score = 100;
}

Game::~Game() {
	delete window;
}

void Game::get_scorebox() {
    if (!scorebox_texture.loadFromFile("assets/scorebox.png")) {
        cout << "Failed to load scorebox asset" << endl;
    }
    scorebox_sprite.setTexture(scorebox_texture, true);
    scorebox_sprite.setPosition(1324, 0);

    if (!scorebox_font.loadFromFile("assets/copperplate.otf")) {
        cout << "Failed to load scorebox font" << endl;
    }
    scorebox_text.setFont(scorebox_font);
    scorebox_text.setCharacterSize(50);
    scorebox_text.setFillColor(Color(47, 47, 47));
}

void Game::get_backdrop() {
    if (!backdrop_texture.loadFromFile("assets/backdrop.png")) {
        cout<< "Load failed" << endl;
        system("pause");
    }
    backdrop_sprite.setTexture(backdrop_texture, true);
    backdrop_sprite.setScale(1, 1);
    backdrop_sprite.setOrigin((sf::Vector2f)backdrop_texture.getSize() / 2.f);
    backdrop_sprite.setPosition(constants::SCREEN_WIDTH/2, constants::SCREEN_HEIGHT/2);
    
    if (!backdrop_walls_texture.loadFromFile("assets/backdrop_walls.png")) {
        cout << "Failed to load scorebox asset" << endl;
    }
    backdrop_walls_sprite.setTexture(backdrop_walls_texture, true);
    backdrop_walls_sprite.setScale(1, 1);
    backdrop_walls_sprite.setOrigin((sf::Vector2f)backdrop_walls_texture.getSize() / 2.f);
    backdrop_walls_sprite.setPosition(constants::SCREEN_WIDTH/2, constants::SCREEN_HEIGHT/2);
}

void Game::render_backdrop() {
    window->draw(backdrop_sprite);
}

void Game::render_backdrop_walls() {
    window->draw(backdrop_walls_sprite);
}

void Game::screen_shake(float intensity) {
    current_screen_shake = intensity * 10;
}

bool Game::is_running() {
	return this->window->isOpen();
}

void Game::spawn_cargo_node(int x_pos, int y_pos, int color_index) {
	nodes.push_back(new Cargo_Node(x_pos, y_pos, color_index));
}

void Game::spawn_fried_node(int x_pos, int y_pos) {
	nodes.push_back(new Fried_Node(x_pos, y_pos));
}

void Game::spawn_laser_node(int x_pos, int y_pos) {
	nodes.insert(nodes.begin(), new Laser_Node(x_pos, y_pos));
}

//Not sure if this will be needed but if the user scoring is handled somewhere that's not the game class, will come in handy
void Game::increment_score(int value) {
    score += value;
}

void Game::update_screen_shake() {
    if (new_shake_intensity > 0) {
        screen_shake(new_shake_intensity);
        new_shake_intensity = 0;
    }
}

void Game::update_player() {
    player.update(nodes);
}

void Game::update_nodes() {
	for (Node* node : nodes) {
		node->update(nodes);
	}
}

void Game::update() {
	poll_events();
	update_nodes();
	update_player();
    update_screen_shake();
}

void Game::render_player() {
	window->draw(player.get_player_sprite());
}

void Game::render_nodes()
{
	for (Node* node : nodes) {
		node->render(window);
	}
}

void Game::render_conveyor(int frames) {
    window->draw(conveyor.get_conveyor_sprite(frames));
}

void Game::render_scorebox() {
    scorebox_text.setString(to_string(score));
    scorebox_text.setPosition(1463 - (scorebox_text.getGlobalBounds().width / 2) - (0.1 * score), 65); //The 0.1 will change depending how high the score should feasibly go. Or this can be changed entirely
    
    window->draw(scorebox_sprite);
    window->draw(scorebox_text);
    
}

void Game::render_screen_shake() {

    
    if (current_screen_shake > 1) {
        view.setCenter({constants::SCREEN_WIDTH/2 - current_screen_shake*shake_direction, constants::SCREEN_HEIGHT/2 - current_screen_shake*shake_direction});
        window->setView(view);
        current_screen_shake /= 2;
        shake_direction *= -1;
    } else {
        current_screen_shake = 0;
        window->setView(window->getDefaultView());
    }
}

void Game::render() {
	render_screen_shake();
	window->clear();
	render_backdrop();
	render_nodes();
    render_conveyor(frame_counter);
	render_player();
    render_backdrop_walls();
	render_scorebox();
	window->display();
    
	frame_counter += 1;
}
