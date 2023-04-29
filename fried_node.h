#ifndef FRIED_NODE_H
#define FRIED_NODE_H

#include "node.h"

class Fried_Node : public Node {
private:
	Fried_Node() = delete;
public:
	Fried_Node(int x_pos, int y_pos);
	~Fried_Node();
	string get_color();
};

#endif //FRIED_NODE_H
