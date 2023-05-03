/**
 * Project 08: Cargo Chaos Cargo_Node class declaration.
 * @file Cargo_Node.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

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
