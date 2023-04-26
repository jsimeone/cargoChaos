#include "cargo_node.h"

Cargo_Node::Cargo_Node(int x_pos, int y_pos, int new_color_index) : Node(x_pos, y_pos) {
    color_index = new_color_index;
    set_texture(get_color());
}

String Cargo_Node::get_color() {
    return colors[color_index];
}

vector<string> Cargo_Node::colors = { "Red", "Green", "Blue" };
