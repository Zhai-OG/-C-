#pragma once
struct Position
{
	int x;
	int y;
	bool operator <(const Position& pos) const {
		if (x != pos.x) {
			return x < pos.x;
		}
		else {
			return y < pos.y;
		}
	}
};
class Chess
{
public:
	Chess();
	Chess(int color, Position pos);
	int getColor();
	Position getPosition();
	
private:
	int color=0;
	Position pos;
};

