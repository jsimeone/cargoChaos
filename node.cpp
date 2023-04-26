#include "node.h"
#include "constants.h"

void Node::set_texture(string texture_file_name) {
	texture.loadFromFile("assets/" + texture_file_name + "_Node.png");
	node_sprite.setTexture(texture);
    node_sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
}

Node::Node(int x_pos, int y_pos) {
	is_held = false;
	node_sprite.setScale(constants::NODE_SCALE, constants::NODE_SCALE);
	node_sprite.setPosition(x_pos, y_pos);
    
}

Sprite Node::get_node_sprite() {
	return node_sprite;
}



void Node::pick_up(Vector2f player_position, float player_rotation) {
	is_held = true;
	node_sprite.setPosition(constants::off_screen);
}

void Node::put_down(Vector2f player_position, float player_rotation) {
	node_sprite.setPosition(player_position);
	node_sprite.setRotation(player_rotation);
	is_held = false;
}
