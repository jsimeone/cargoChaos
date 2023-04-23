#include "player.h"
#include "constants.h"


Player::Player() {
	texture.loadFromFile("assets/player.png");

	player_sprite.setTexture(texture);
	player_sprite.setScale(constants::PLAYER_SCALE, constants::PLAYER_SCALE);
	player_sprite.setPosition((constants::SCREEN_WIDTH - get_player_width()) / 2, (constants::SCREEN_HEIGHT - get_player_height()) / 2);

	moving_left = false;
	moving_right = false;
	moving_up = false;
	moving_down = false;
	velocity = {0, 0};
	target_position = (Vector2i)player_sprite.getPosition();
}

Player::~Player() {
	return;
}

Sprite Player::get_player_sprite() {
	return player_sprite;
}

int Player::get_player_height() {
	return player_sprite.getTexture()->getSize().y * constants::PLAYER_SCALE;
}

int Player::get_player_width() {
	return player_sprite.getTexture()->getSize().x * constants::PLAYER_SCALE;
}

void Player::update_player_velocity() {
	if (moving_down && !moving_up) {
		velocity[1] += .2;
	} 
	if (moving_up && !moving_down){
		velocity[1] += -.2;
	}
	if (moving_down == moving_up || moving_up && velocity[1] > 0 || moving_down && velocity[1] < 0) {
		velocity[1] -= velocity[1] / 3;
	}

	if (moving_left && !moving_right) {
		velocity[0] += -.2;
	} 
	if (moving_right && !moving_left) {
		velocity[0] += .2;
	}
	if (moving_left == moving_right || moving_left && velocity[0] > 0 || moving_right && velocity[0] < 0) {
		velocity[0] -= velocity[0] / 3;
	}
	//velocity[0] += (target_position.x - player_sprite.getPosition().x) * .025;
	//velocity[1] += (target_position.y - player_sprite.getPosition().y) * .025;
}

void Player::update_player_position() {
	player_sprite.move(velocity[0], velocity[1]);
}

void Player::set_moving_up(bool new_up) {
	moving_up = new_up;
}

void Player::set_moving_down(bool new_down) {
	moving_down = new_down;
}

void Player::set_moving_right(bool new_right) {
	moving_right = new_right;
}

void Player::set_target_position(Vector2i new_target) {
	target_position = new_target;
}

void Player::set_moving_left(bool new_left) {
	moving_left = new_left;
}
