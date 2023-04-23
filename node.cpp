#include "node.h"
#include "constants.h"

void Node::set_texture(string texture_file_name) {
	texture.loadFromFile("assets/" + texture_file_name);
	node_sprite.setTexture(texture);
}

Node::Node(int x_pos, int y_pos, string texture_name) {
	is_held = false;
	node_sprite.setScale(constants::NODE_SCALE, constants::NODE_SCALE);
	node_sprite.setPosition(x_pos, y_pos);
	set_texture(texture_name);
}

Sprite Node::get_node_sprite() {
	return node_sprite;
}



void Node::toggle_pick_up(Vector2f player_position, float player_rotation) {

	if (!is_held) {
		is_held = true;
		node_sprite.setPosition(constants::off_screen);
	} else {
		is_held = false;
		node_sprite.setPosition(player_position);
		node_sprite.setRotation(player_rotation);
	}
}
