/**
 * Project 08: Cargo Chaos Laser_Node class method definitions.
 * @file laser_node.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */
#include "laser_node.h"

/**
 * @brief: Constructor for a Laser_Node object at a certain x_pos, y_pos.
 * @param x_pos The x-position, in pixels, that the node should be created at.
 * @param y_pos The y-position, in pixels, that the node should be created at.
 */
Laser_Node::Laser_Node(int x_pos, int y_pos) : Node(x_pos, y_pos), 
	red_laser(node_sprite.getPosition(), 0),
	green_laser(node_sprite.getPosition(), 1),
	blue_laser(node_sprite.getPosition(), 2)
{
	set_texture("Laser");
}

/**
 * @brief: Gets the color of the node.
 * @return: Always returns "Laser" for Laser_Nodes.
 */
string Laser_Node::get_color() {
	return "Laser";
}

/**
 * @brief: Activates the correct lasers for this node.
 * @param nodes A vector of pointers to all of the nodes in the play area.
 * @return: True if a laser is on, false otherwise.
 */
bool Laser_Node::update_lasers_on(vector<Node*> nodes) {
	bool laser_on = false;
	for (Node* node : nodes) {
		if (node->get_is_held() && node->get_color() != "Laser") {
			string color = node->get_color();
			if (color == "Red") {
				red_laser.set_laser(true);
				laser_on = true;
			}
			else if (color == "Green") {
				green_laser.set_laser(true);
				laser_on = true;
			}
			else if (color == "Blue") {
				blue_laser.set_laser(true);
				laser_on = true;
			}
		}
	}
	return laser_on;
}

/**
 * @brief: Updates this node and its lasers.
 * @param nodes A vector of pointers to all of the nodes in the play area.
 */
void Laser_Node::update(vector<Node*> nodes) {
	if (!update_lasers_on(nodes)) {
		red_laser.set_laser(false);
		blue_laser.set_laser(false);
		green_laser.set_laser(false);
		node_sprite.setRotation(node_sprite.getRotation() + .5);
	}
	red_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	green_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	blue_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
}

/**
 * @brief: Renders the lasers that this node owns.
 * @param window A pointer to the game's window.
 */
void Laser_Node::render_lasers(RenderWindow* window) {
    red_laser.render(window);
    green_laser.render(window);
    blue_laser.render(window);
}

/**
 * @brief: Gets the lasers owned by this node. Returns null pointers if no lasers are
 *		   owned.
 * @return: Pointers to the lasers owned by this node. Returns nullptrs if none are
 *			owned.
 */
vector<Laser*> Laser_Node::get_lasers() {
    return {&red_laser, &green_laser, &blue_laser};
}
