#include "Game.h"


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
			break;
		case Event::MouseButtonPressed:
			break;
		}
	}
}

Game::Game() {
	init_variables();
	init_window();
}

Game::~Game() {
	delete window;
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

void Game::update_player()
{
//	player.update_player_velocity();
//	player.update_player_position();
    
    player.update(nodes);
}

void Game::update() {
	poll_events();
	update_player();
}

void Game::render_player() {
	window->draw(player.get_player_sprite());
}

void Game::render_nodes()
{
	for (Node* node : nodes) {
		window->draw(node->get_node_sprite());
	}
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
	render_player();
	render_nodes();
	window->display();
}
