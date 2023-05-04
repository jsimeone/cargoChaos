/**
 * Project 08: Cargo Chaos Laser class method definitions.
 * @file laser.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */
#include "laser.h"

 /**
  * @brief: The constructor for a Laser object.
  * @param node_pos: The position of the node this laser belongs to.
  * @param new_color_index: The color index of this laser.
  */
Laser::Laser(Vector2f node_pos, int new_color_index) :
    laser_on(false),
    color_index(new_color_index),
    rotation_offset(color_index * 120),
    length(0),
    width(5)
{
	set_texture(colors[color_index]);
}

/**
 * @brief: Destroys the laser. Useful for future development.
 */
Laser::~Laser() {
	return;
}

/**
 * @brief: Renders this laser to the game window.
 * @param window: A pointer to the game window.
 */
void Laser::render(RenderWindow* window) {
    if (laser_on) {
        window->draw(laser_sprite);
    }
}

/**
 * @brief: Sets the length of this laser.
 * @param new_length: The new length of this laser.
 */
void Laser::set_length(int new_length) {
    length = new_length;
}

/**
 * @brief: Sets whether the laser is on or off.
 * @param new_laser_on: A bool indicating whether the laser should be on or off.
 */
void Laser::set_laser(bool new_laser_on) {
    if (laser_on == !new_laser_on) {
        laser_on = new_laser_on;
        length = 0;
    }
}

/**
 * @brief: Checks if the laser is colliding with a node.
 * @param nodes: A vector of pointers to all of the nodes in the play area.
 * @param x_is_valid: A bool used to pass back whether or not the x position is valid.
 * @param y_is_valid: A bool used to pass back whether or not the y position is valid.
 * @param end_x: The location of the x location of the end point of the laser.
 * @param end_y: The location of the y location of the end point of the laser.
 * @param parent: The sprite of the parent node.
 */
void Laser::check_node_collisions(vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid, 
                                  float end_x, float end_y, Sprite parent) {
    for (Node* node : nodes) {
        if (!x_is_valid && !y_is_valid) {
            return;
        }
        Sprite node_sprite = *(node->get_node_sprite());
        Vector2<float> node_pos = node_sprite.getPosition();
        float x_dis = node_pos.x - end_x;
        float y_dis = node_pos.y - end_y;
        float distance = width + (node_sprite.getTexture()->getSize().x * 
                         node_sprite.getScale().x) / 2;
        if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance && 
            node_sprite.getGlobalBounds() != parent.getGlobalBounds()) 
        {
            if (pow(pow(node_pos.x - end_x, 2) + pow(y_dis, 2), 0.5) > distance) {
                x_is_valid = false;
            }
            else if (pow(pow(x_dis, 2) + pow(node_pos.y - end_y, 2), 0.5) > distance) {
                y_is_valid = false;
            }
            else {
                x_is_valid = false;
                y_is_valid = false;
                return;
            }
        }
    }
}

/**
 * @brief: Checks if the laser is colliding with a wall.
 * @param x_is_valid: A bool used to pass back whether or not the x position is valid.
 * @param y_is_valid: A bool used to pass back whether or not the y position is valid.
 * @param end_x: The location of the x location of the end point of the laser.
 * @param end_y: The location of the y location of the end point of the laser.
 */
void Laser::check_wall_collisions(bool& x_is_valid, bool& y_is_valid, 
                                  float end_x, float end_y) 
{
    if (end_x > 
        (constants::PLAY_AREA_WIDTH_BOUNDS[1] + 2 * constants::SCREEN_WIDTH) / 3) 
    {
        x_is_valid = false;
    }
    else if (end_x < constants::PLAY_AREA_WIDTH_BOUNDS[0] / 3) {
        x_is_valid = false;
    }
    if (end_y > 
        (constants::PLAY_AREA_HEIGHT_BOUNDS[1] + 2 * constants::SCREEN_HEIGHT) / 3) 
    {
        y_is_valid = false;
    }
    else if (end_y < constants::PLAY_AREA_HEIGHT_BOUNDS[0] / 3) {
        y_is_valid = false;
    }
}

/**
 * @brief: Updates the length of the laser, checking for wall and node collisions.
 * @param node_pos: The position of the node this laser belongs to.
 * @param node_rotation: The rotation of the node this laser belongs to.
 * @param nodes: A list of pointers to all the nodes in the play area.
 * @param parent: The sprite of the parent node.
 */
void Laser::update_length(Vector2f node_pos, float node_rotation, 
                          vector<Node*> nodes, Sprite parent) 
{
    direction = (node_rotation + rotation_offset + 90) * (constants::PI / 180);
    float end_x = node_pos.x + ((length - 50) * cos(direction));
    float end_y = node_pos.y + ((length - 50) * sin(direction));
    bool x_is_valid = true;
    bool y_is_valid = true;
    check_node_collisions(nodes, x_is_valid, y_is_valid, end_x, end_y, parent);
    if (!x_is_valid && !y_is_valid) {
        return; //no need to continue checking
    }
    //check walls:
    if (end_x > (constants::PLAY_AREA_WIDTH_BOUNDS[1] + 2*constants::SCREEN_WIDTH)/3) {
        x_is_valid = false;
    }
    else if (end_x < constants::PLAY_AREA_WIDTH_BOUNDS[0]/3) {
        x_is_valid = false;
    }
    if (end_y > (constants::PLAY_AREA_HEIGHT_BOUNDS[1] + 2*constants::SCREEN_HEIGHT)/3) {
        y_is_valid = false;
    }
    else if (end_y < constants::PLAY_AREA_HEIGHT_BOUNDS[0]/3) {
        y_is_valid = false;
    }
    check_wall_collisions(x_is_valid, y_is_valid, end_x, end_y);
    if (x_is_valid && y_is_valid) {
        length += constants::LASER_SPEED;
    }
    end_x = node_pos.x + length * cos(direction);
    end_y = node_pos.y + length * sin(direction);
    start_pos = node_pos;
    end_pos = {end_x, end_y};
}

/**
 * @brief: Updates the laser.
 * @param node_pos: The position of the node this laser belongs to.
 * @param node_rotation: The rotation of the node this laser belongs to.
 * @param nodes: A list of pointers to all the nodes in the play area.
 * @param parent: The sprite of the parent node.
 */
void Laser::update_laser(Vector2f node_pos, float node_rotation, 
                         vector<Node*> nodes, Sprite parent) 
{
    if (laser_on) {
        laser_sprite.setPosition(node_pos);
        laser_sprite.setRotation(node_rotation + rotation_offset);
        update_length(node_pos, node_rotation, nodes, parent);
        laser_sprite.setScale(1, length);
    }
	
}

/**
 * @brief: Sets the texture of the laser.
 * @param texture_name: The color to use for this laser's texture.
 */
void Laser::set_texture(string texture_name) {
	if (!texture.loadFromFile("assets/" + texture_name + "_Laser.png")) {
		cout << "Loading laser texture failed" << endl;
	}
	laser_sprite.setTexture(texture);
	laser_sprite.setOrigin(texture.getSize().x / 2.f, 0);
}

/**
 * @brief: Gets the sprite for this laser.
 */
Sprite* Laser::get_sprite() {
    return &laser_sprite;
}

/**
 * @brief: Gets the distance between two positions for laser collisions.
 * @param pos1: The position of the first point to measure.
 * @param pos2: The position of the second point to measure.
 */
float Laser::get_distance(Vector2<float> pos1, Vector2<float> pos2) {
    float x_dis = pos1.x - pos2.x;
    float y_dis = pos1.y - pos2.y;
    return sqrt( pow ( x_dis, 2 ) + pow ( y_dis , 2) );
}

/**
 * @brief: Gets whether or not this laser is colliding with the given player.
 * @param player: The player to check collision with
 * @return: Whether or not the player is colliding with this laser.
 */
bool Laser::colliding_with(Player player) {
    //Check if player ran into laser
    Vector2<float> player_pos = player.get_player_sprite().getPosition();
    float player_laser_angle = atan2(start_pos.y-player_pos.y, 
                                     start_pos.x - player_pos.x);
    float collision_angle = player_laser_angle = constants::PI/2;
    float collision_point_x = player_pos.x + player.player_body_radius * 
                              cos(collision_angle);
    float collision_point_y = player_pos.y + player.player_body_radius * 
                              sin(collision_angle);
    Vector2<float> collision_point = {collision_point_x, collision_point_y};
    if (get_distance(start_pos, collision_point) + 
        get_distance(end_pos, collision_point) - 
        get_distance(start_pos, end_pos) < constants::PLAYER_LASER_BUFFER) 
    {
        return true;
    }
    //Check if laser hit player
    if (get_distance(end_pos, player_pos) <= player.player_body_radius) {
        cout << "Laser hit Player!" << endl;
        return true;
    }
    
    
    return false;
}

/**
 * @brief: Gets whether or not the laser is turned on.
 */
bool Laser::get_laser_on() {
    return laser_on;
}

vector<string> Laser::colors = { "Red", "Green", "Blue" };
