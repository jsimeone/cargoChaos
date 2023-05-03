/**
 * Project 08: Cargo Chaos Node class method definitions.
 * @file node.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#include "node.h"
#include "constants.h"

 /**
  * @brief: Sets the texture used by this node.
  * @param texture_file_name: The name of the texture, should be "Red", "Green", "Blue", 
  *							  "Laser", or "Fried".
  */
void Node::set_texture(string texture_file_name) {
	texture.loadFromFile("assets/" + texture_file_name + "_Node.png");
	node_sprite.setTexture(texture);
    node_sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
}

/**
 * @brief: Constructor for a Node object at a certain x_pos, y_pos.
 * @param x_pos: The x-position, in pixels, that the node should be created at.
 * @param y_pos: The y-position, in pixels, that the node should be created at.
 */
Node::Node(int x_pos, int y_pos) : 
	is_held(false)
{
	node_sprite.setScale(constants::NODE_SCALE, constants::NODE_SCALE);
	node_sprite.setPosition(x_pos, y_pos);
    
}

/**
 * @brief: Gets the sprite belonging to this node.
 * @return: A pointer to this node's sprite.
 */
Sprite* Node::get_node_sprite() {
	return &node_sprite;
}

/**
 * @brief: "Picks up" this node, moving it off screen.
 */
void Node::pick_up() {
	is_held = true;
	node_sprite.setPosition(constants::OFF_SCREEN);
}

/**
 * @brief: Puts this node down at the given position, maintaining the player's rotation.
 * @param placement_position: A Vector2f containing the x and y position the node should
 *							  be placed at.
 * @param player_rotation: The angle, in degrees, the node should be placed at.
 */
void Node::put_down(Vector2f placement_position, float player_rotation) {
	node_sprite.setPosition(placement_position);
	node_sprite.setRotation(player_rotation);
	is_held = false;
}

/**
 * @brief: Updates the node. Overridden by certain derived classes as needed.
 * @param nodes: A vector of pointers to all of the nodes in the play area.
 */
void Node::update(vector<Node*> nodes) {
	return;
}

/**
 * @brief: Renders the node to the window.
 * @param window: A pointer to the main game window.
 */
void Node::render(RenderWindow* window) {
	window->draw(node_sprite);
}

/**
 * @brief: Returns whether or not the node is currently held.
 * @return: Whether or not the node is currently held.
 */
bool Node::get_is_held() {
	return is_held;
}

/**
 * @brief: Gets the lasers owned by this node. Returns null pointers if no lasers are 
 *		   owned.
 * @return: Pointers to the lasers owned by this node. Returns nullptrs if none are 
 *			owned.
 */
vector<Laser*> Node::get_lasers() {
    return {nullptr, nullptr, nullptr};
}

/**
 * @brief: Renders any lasers owned by this node to the game window.
 * @param window: A pointer to the main game window.
 */
void Node::render_lasers(RenderWindow* window) {
    return;
}
