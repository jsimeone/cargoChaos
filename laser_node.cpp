#include "laser_node.h"

Laser_Node::Laser_Node(int x_pos, int y_pos) : 
	Node(x_pos, y_pos), 
	red_laser(node_sprite.getPosition(), 0),
	green_laser(node_sprite.getPosition(), 1),
	blue_laser(node_sprite.getPosition(), 2)
{
	set_texture("Laser");
}

string Laser_Node::get_color() {
	return "Laser";
}

void Laser_Node::update(vector<Node*> nodes) {
	bool laser_on = false;
	for (Node* node : nodes) {
		if (node->get_is_held() && node->get_color() != "Laser") {
			string color = node->get_color();
			if (color == "Red") {
				red_laser.set_laser(true);
				green_laser.set_laser(false);
				blue_laser.set_laser(false);

				laser_on = true;
			}
			else if (color == "Green") {
				red_laser.set_laser(false);
				green_laser.set_laser(true);
				blue_laser.set_laser(false);

				laser_on = true;
			}
			else if (color == "Blue") {
				red_laser.set_laser(false);
				blue_laser.set_laser(true);
				green_laser.set_laser(false);

				laser_on = true;
			}
		}
	}
	if (!laser_on) {
		red_laser.set_laser(false);
		blue_laser.set_laser(false);
		green_laser.set_laser(false);
		node_sprite.setRotation(node_sprite.getRotation() + .5);
	}
	red_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	green_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	blue_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
}

void Laser_Node::render(RenderWindow* window) {
	Node::render(window);

	red_laser.render(window);
	green_laser.render(window);
	blue_laser.render(window);
}
