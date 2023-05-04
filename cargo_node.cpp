/**
 * Project 08: Cargo Chaos Cargo_Node class method definitions.
 * @file cargo_node.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#include "cargo_node.h"

/**
 * @brief: Constructor for a Cargo_Node object at a certain x_pos, y_pos with a certain 
           color.
 * @param x_pos The x-position, in pixels, that the node should be created at.
 * @param y_pos The y-position, in pixels, that the node should be created at.
 * @param new_color_index The index representation of the color this node should be. 
                           0->Red, 1->Green, 3->Blue.
 */
Cargo_Node::Cargo_Node(int x_pos, int y_pos, int new_color_index) : Node(x_pos, y_pos),
    color_index(new_color_index)
{
    set_texture(get_color());
}

vector<string> Cargo_Node::colors = { "Red", "Green", "Blue" };

/**
 * @brief: Gets the color of the node.
 * @return: Returns the correct color of this node, "Red", "Green", or "Blue".
 */
string Cargo_Node::get_color() {
    return colors[color_index];
}



