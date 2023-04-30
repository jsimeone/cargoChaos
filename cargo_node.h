#ifndef CARGO_NODE_H
#define CARGO_NODE_H

#include "node.h"

class Cargo_Node : public Node {
private:
	int color_index;
	Cargo_Node() = delete;
public:
	static vector<string> colors;

	Cargo_Node(int x_pos, int y_pos, int new_color_index);
	string get_color();
};

#endif //CARGO_NODE_H
