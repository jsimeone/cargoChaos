/**
 * Project 08: Cargo Chaos Fried_Node class method definitions.
 * @file fried_node.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */
#include "fried_node.h"

/**
 * @brief: Constructor for a Fried_Node object at a certain x_pos, y_pos.
 * @param x_pos: The x-position, in pixels, that the node should be created at.
 * @param y_pos: The y-position, in pixels, that the node should be created at.
 */
Fried_Node::Fried_Node(int x_pos, int y_pos) : Node(x_pos, y_pos) {
	set_texture("Fried");
}

/**
 * @brief: Gets the color of the node.
 * @return: Always returns "Fried" for Fried_Nodes.
 */
string Fried_Node::get_color() {
	return "Fried";
}
