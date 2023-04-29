#ifndef LASER_H
#define LASER_H

#include "node.h"

class Laser {
private:
	Texture texture;
	Sprite laser_sprite;
	vector<float> start_pos;
	vector<float> end_pos;
	int color_index;
	bool laser_on;
	float rotation_offset;
	float length;
	float width;
	static vector<string> colors;
	void update_length(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent);
public:
	Laser(Vector2f node_pos, int color_index);
	~Laser();

	void set_texture(string texture_name);
	void update_laser(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent);
	void render(RenderWindow* window);
	void set_laser(bool new_laser_on);
	void set_length(int new_length);
};

#endif //LASER_H