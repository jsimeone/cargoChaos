#include "game.h"
#include <random>


void Game::init_variables() {
	window = nullptr;
    srand(time(0));
    exit_rectangle.setPosition({constants::EXIT_AREA_RECT.left,constants::EXIT_AREA_RECT.top});
    exit_rectangle.setSize({constants::EXIT_AREA_RECT.width,constants::EXIT_AREA_RECT.height});
    colors = {Color(200, 0, 0, 100), Color(0, 200, 0, 100), Color(0, 0, 200, 100)};
    exit_color = random_color();
    exit_rectangle.setFillColor(exit_color);
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
    if (event.key.code == Keyboard::Space) {
        if (player.get_player_sprite().getPosition().x < constants::CONVEYOR_PICK_UP_BOUNDS[0] && player.get_player_sprite().getPosition().y < constants::CONVEYOR_PICK_UP_BOUNDS[1]) {
            conveyor_pick_up();
        }
        player.toggle_pick_up(nodes);
    }
    if (event.key.code == Keyboard::T)
        conveyor.spawn_random_node();
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

Color Game::random_color() {
    return colors[rand() % 3];
}

void Game::conveyor_pick_up() {
    if (!player.is_holding) {
        String node_type = conveyor.pick_up_node();
        if (node_type == "Laser") {
            spawn_laser_node(constants::OFF_SCREEN.x, constants::OFF_SCREEN.y);
            player.pick_up_from_conveyor(nodes[0]);
        }
        else if (node_type == "Red") {
            spawn_cargo_node(constants::OFF_SCREEN.x, constants::OFF_SCREEN.y, 0);
            player.pick_up_from_conveyor(nodes[nodes.size() - 1]);
        }
        else if (node_type == "Green") {
            spawn_cargo_node(constants::OFF_SCREEN.x, constants::OFF_SCREEN.y, 1);
            player.pick_up_from_conveyor(nodes[nodes.size() - 1]);
        }
        else if (node_type == "Blue") {
            spawn_cargo_node(constants::OFF_SCREEN.x, constants::OFF_SCREEN.y, 2);
            player.pick_up_from_conveyor(nodes[nodes.size() - 1]);
        }
        else {
            return;
        }
        
    }
    
}

Game::Game() {
	init_variables();
	init_window();
    get_backdrop();
    get_scorebox();
    frame_counter = 0;
    score = 0;
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
    if (!player.is_holding) {
        return;
    }
    for (Node* node : nodes) {
        if (node->get_color() == "Laser") {
            for (Laser* laser : node->get_lasers()) {
                if (laser->get_laser_on() && laser->colliding_with(player)) {
                    Vector2<float> fried_node_pos = player.put_down_fried_node(nodes);
                    spawn_fried_node(fried_node_pos.x, fried_node_pos.y);
                    new_shake_intensity = constants::HIT_SHAKE;
                    return;
                }
            }
        }
    }
}

void Game::update_nodes() {
	for (Node* node : nodes) {
		node->update(nodes);
        if (node->get_color() == "Laser") {
            continue;
        }
        Vector2<float> node_pos =  node->get_node_sprite()->getPosition();
        if (constants::EXIT_AREA_RECT.contains(node_pos)) {
            string node_color = node->get_color();
            if ((node_color == "Blue" && exit_color == (colors[2])) ||
                (node_color == "Red" && exit_color == (colors[0])) ||
                (node_color == "Green" && exit_color == (colors[1]))) {
                
                increment_score(constants::SCORE_INCREMENT);
                node->get_node_sprite()->setPosition(constants::OFF_SCREEN.x, constants::OFF_SCREEN.y);
                exit_color = random_color();
                exit_rectangle.setFillColor(exit_color);
            }
//
        }
	}
    
}

void Game::random_spawn() {
    if (frame_counter % 300 == 0) {
        conveyor.spawn_random_node();
    }
}


void Game::update() {
    random_spawn();
	poll_events();
	update_nodes();
	update_player();
    update_screen_shake();
    conveyor.update();
}

void Game::render_player() {
	window->draw(player.get_player_sprite());
}

void Game::render_nodes() {
	for (Node* node : nodes) {
		node->render(window);
	}
}

void Game::render_conveyor(int frames) {
    conveyor.render(window, frames);
}

void Game::render_scorebox() {
    scorebox_text.setString(to_string(score));
    scorebox_text.setPosition(1453 - (scorebox_text.getGlobalBounds().width / 2), 65);
    
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
    window->draw(exit_rectangle);
	render_nodes();
    render_conveyor(frame_counter);
	render_player();
    render_backdrop_walls();
	render_scorebox();
    
    
	window->display();
    
	frame_counter += 1;
}
