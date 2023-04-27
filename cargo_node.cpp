#include "cargo_node.h"

Cargo_Node::Cargo_Node(int x_pos, int y_pos, int new_color_index) : Node(x_pos, y_pos) {
    color_index = new_color_index;
    set_texture(get_color());
}
