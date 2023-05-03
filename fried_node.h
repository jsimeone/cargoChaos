/**
 * Project 08: Cargo Chaos Fried_Node class declaration.
 * @file fried_node.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#ifndef FRIED_NODE_H
#define FRIED_NODE_H

#include "node.h"

class Fried_Node : public Node {
private:
	Fried_Node() = delete;
public:
	Fried_Node(int x_pos, int y_pos);
	string get_color();
};

#endif //FRIED_NODE_H
