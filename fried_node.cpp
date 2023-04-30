#include "fried_node.h"

Fried_Node::Fried_Node(int x_pos, int y_pos) : Node(x_pos, y_pos) {
	set_texture("Fried");
}

Fried_Node::~Fried_Node() {
	return;
}

string Fried_Node::get_color()
{
	return "Fried";
}

//void Fried_Node::pick_up(Vector2f player_position, float player_rotation) {
//	return;
//}
