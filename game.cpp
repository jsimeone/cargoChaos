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
				player.is_sprinting = true;
			break;
		case Event::KeyReleased:
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
			break;
		case Event::MouseButtonPressed:
			break;
		}
	}
}

Game::Game() {
	init_variables();
	init_window();
    get_backdrop();
    frame_counter = 0;
}

Game::~Game() {
	delete window;
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
    
    if (!scorebox_texture.loadFromFile("assets/scorebox.png")) {
        cout << "Failed to load scorebox asset" << endl;
    }
    scorebox_sprite.setTexture(scorebox_texture, true);
    scorebox_sprite.setPosition(1324, 0);
}

void Game::render_backdrop() {
    window->draw(backdrop_sprite);
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

void Game::update_screen_shake() {
    if (new_shake_intensity > 0) {
        screen_shake(new_shake_intensity);
        new_shake_intensity = 0;
    }
}

void Game::update_player()
{
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
    //implement updating the score
}

void Game::render_player() {
	window->draw(player.get_player_sprite());
}

void Game::render_nodes()
{
	for (Node* node : nodes) {
		node->render(window);
		window->draw(node->get_node_sprite());
	}
}

void Game::render_conveyor(int frames) {
    window->draw(conveyor.get_conveyor_sprite(frames));
}

void Game::render_scorebox() {
    window->draw(scorebox_sprite);
    //render the scorebox text here
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
	render_scorebox();
	window->display();
    
	frame_counter += 1;
}
