#include "Game.h"

void Game::init_variables() {
	window = nullptr;
}

void Game::init_window() {
	videoMode.height = constants::SCREEN_HEIGHT;
	videoMode.width = constants::SCREEN_WIDTH;

	window = new sf::RenderWindow(videoMode, "Final Project", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(60);
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
			if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
				player.set_moving_up(true);
			if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
				player.set_moving_down(true);
			if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
				player.set_moving_left(true);
			if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
				player.set_moving_right(true);
			if (event.key.code == Keyboard::Space)
				for (Node* node : nodes) {
					if (player.get_player_sprite().getGlobalBounds().intersects(node->get_node_sprite().getGlobalBounds())) {
						node->toggle_pick_up(player.get_player_sprite().getPosition(), player.get_player_sprite().getRotation());
					}

				}
			break;
		case Event::KeyReleased:
			if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
				player.set_moving_up(false);
			if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
				player.set_moving_down(false || event.key.code == Keyboard::A);
			if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
				player.set_moving_left(false);
			if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
				player.set_moving_right(false);
			break;
		case Event::MouseButtonPressed:
			player.set_target_position(Mouse::getPosition(*window));
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


bool Game::is_running() {
	return this->window->isOpen();
}

void Game::spawn_node(int x_pos, int y_pos, string texture_name)
{
	nodes.push_back(new Node(x_pos, y_pos, texture_name));
	nodes[nodes.size() - 1]->set_texture(texture_name);

}

void Game::update_player()
{
	player.update_player_velocity();
	player.update_player_position();
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

void Game::render() {
	window->clear();
	render_player();
	render_nodes();
	window->display();
}