#include "laser.h"

Laser::Laser(Vector2f node_pos, int new_color_index) :
    laser_on(false),
    color_index(new_color_index),
    rotation_offset(color_index * 120),
    length(0),
    width(5)
{
	set_texture(colors[color_index]);
}

Laser::~Laser() {
	return;
}

void Laser::render(RenderWindow* window) {
    if (laser_on) {
        window->draw(laser_sprite);
    }
}

void Laser::set_length(int new_length) {
    length = new_length;
}

void Laser::set_laser(bool new_laser_on) {
    if (laser_on == !new_laser_on) {
        laser_on = new_laser_on;
        length = 0;
    }
}

void Laser::check_node_collisions(vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid, float end_x, float end_y, Sprite parent) {
    for (Node* node : nodes) {
        if (!x_is_valid && !y_is_valid) {
            return;
        }
        Sprite node_sprite = *(node->get_node_sprite());
        Vector2<float> node_pos = node_sprite.getPosition();
        float x_dis = node_pos.x - end_x;
        float y_dis = node_pos.y - end_y;
        float distance = width + (node_sprite.getTexture()->getSize().x * node_sprite.getScale().x) / 2;
        if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance && node_sprite.getLocalBounds() != parent.getLocalBounds()) {
            if (pow(pow(node_pos.x - end_x, 2) + pow(y_dis, 2), 0.5) > distance) {
                x_is_valid = false;
            }
            else if (pow(pow(x_dis, 2) + pow(node_pos.y - end_y, 2), 0.5) > distance) {
                y_is_valid = false;
            }
            else {
                x_is_valid = false;
                y_is_valid = false;
                return;
            }
        }
    }
}

void Laser::check_wall_collisions(bool& x_is_valid, bool& y_is_valid, float end_x, float end_y) {
    if (end_x > (constants::PLAY_AREA_WIDTH_BOUNDS[1] + 2 * constants::SCREEN_WIDTH) / 3) {
        x_is_valid = false;
    }
    else if (end_x < constants::PLAY_AREA_WIDTH_BOUNDS[0] / 3) {
        x_is_valid = false;
    }
    if (end_y > (constants::PLAY_AREA_HEIGHT_BOUNDS[1] + 2 * constants::SCREEN_HEIGHT) / 3) {
        y_is_valid = false;
    }
    else if (end_y < constants::PLAY_AREA_HEIGHT_BOUNDS[0] / 3) {
        y_is_valid = false;
    }
}

void Laser::update_length(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent) {
	float end_x = node_pos.x + ((length - 50) * cos((node_rotation + rotation_offset + 90) * (constants::PI / 180)));
	float end_y = node_pos.y + ((length - 50) * sin((node_rotation + rotation_offset + 90) * (constants::PI / 180)));
    bool x_is_valid = true;
    bool y_is_valid = true;
    check_node_collisions(nodes, x_is_valid, y_is_valid, end_x, end_y, parent);
    if (!x_is_valid && !y_is_valid) {
        return; //no need to continue checking
    }
    //check walls:
    if (end_x > (constants::PLAY_AREA_WIDTH_BOUNDS[1] + 2*constants::SCREEN_WIDTH)/3) {
        x_is_valid = false;
    }
    else if (end_x < constants::PLAY_AREA_WIDTH_BOUNDS[0]/3) {
        x_is_valid = false;
    }
    if (end_y > (constants::PLAY_AREA_HEIGHT_BOUNDS[1] + 2*constants::SCREEN_HEIGHT)/3) {
        y_is_valid = false;
    }
    else if (end_y < constants::PLAY_AREA_HEIGHT_BOUNDS[0]/3) {
        y_is_valid = false;
    }
    check_wall_collisions(x_is_valid, y_is_valid, end_x, end_y);
    if (x_is_valid && y_is_valid) {
        length += 10;
    }
}

void Laser::update_laser(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent) {
    if (laser_on) {
        laser_sprite.setPosition(node_pos);
        laser_sprite.setRotation(node_rotation + rotation_offset);
        update_length(node_pos, node_rotation, nodes, parent);
        laser_sprite.setScale(1, length);
    }
	
}

void Laser::set_texture(string texture_name) {
	if (!texture.loadFromFile("assets/" + texture_name + "_Laser.png")) {
		cout << "Loading laser texture failed" << endl;
	}
	laser_sprite.setTexture(texture);
	laser_sprite.setOrigin(texture.getSize().x / 2.f, 0);
}

vector<string> Laser::colors = { "Red", "Green", "Blue" };
