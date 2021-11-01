#pragma once

#include <list>
#include <Windows.h>
class Board;

class SevagSnake {
public:
	enum class Direction { up, down, left, right, noDirection};
	SevagSnake(Board& Board, short VELOCITY_PIXELS_PER_100MS);
	const Direction& getDirection() const;
	void displaySnake();
	void grow();
	void moveRight();
	void moveUp();
	void moveLeft();
	void moveDown();
	void keepMoving();
	const short& headX() const;
	const short& headY() const;
	bool occupiesPosition(COORD position);
	bool isHit();
private:
	const char HEAD_ = '0';
	const char BODY_ = 'o';
	std::list<COORD> snake_;
	int len_;
	short velocityPixelsPer100ms_;
	Board &Board_;
	Direction direction_;
	COORD head() const;
	COORD tail() const;
	COORD tailNext() const;
	void move(Direction direction);
	bool hitSelf() const;
};
