#include "Chess.h"
Chess::Chess() {
	this->color = 0;
}
Chess::Chess(int color, Position pos) {
	this->color = color;
	this->pos = pos;
} 
int Chess::getColor() {
	return color;
}
Position Chess::getPosition() {
	return pos;
}