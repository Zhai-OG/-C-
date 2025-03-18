#include "Player.h"
Chess Player::play_chess() {
	Chess chess;
	return chess;
}
Player::Player() {
	this->color = 0;
}
Player::Player(string name, int color) {
	this->name = name;
	this->color = color;
}
string Player::getname() {
	return name;
}
void Player::setName(string name) {
	this->name = name;
}
int Player::getcolor() {
	return color;
}
void Player::setcolor(int color) {
	this->color = color;
}