#ifndef LASER_H
#define LASER_H

#include "node.h"
#include "player.h"

class Laser {
private:
	Texture texture;
	Sprite laser_sprite;
	int color_index;
	bool laser_on;
	float rotation_offset;
	float length;
	float width;
    float direction;
	static vector<string> colors;
	void update_length(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent);
	void set_texture(string texture_name);
	void set_length(int new_length);
    Vector2<float> start_pos;
    Vector2<float> end_pos;
    float get_distance(Vector2<float> pos1, Vector2<float> pos2);

public:
	Laser(Vector2f node_pos, int color_index);
	~Laser();

	void update_laser(Vector2f node_pos, float node_rotation, vector<Node*> nodes, Sprite parent);
	void render(RenderWindow* window);
	void set_laser(bool new_laser_on);
	void check_node_collisions(vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid, float end_x, float end_y, Sprite parent);
	void check_wall_collisions(bool& x_is_valid, bool& y_is_valid, float end_x, float end_y);
	Sprite* get_sprite();
    bool colliding_with(Player player);
    bool get_laser_on();
};

#endif //LASER_H
