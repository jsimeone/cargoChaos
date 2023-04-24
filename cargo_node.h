#ifndef CARGO_NODE_H
#define CARGO_NODE_H

#include "node.h"

class Cargo_Node : public Node {
private:
	Cargo_Node() = delete;
	int color_index;
	static vector<string> colors;
public:
	Cargo_Node(int x_pos, int y_pos, int new_color_index);
	String get_color();

};

#endif //CARGO_NODE_H