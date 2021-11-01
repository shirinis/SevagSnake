#pragma once

#include <windows.h>
class SevagSnake;

class Board
{
public:
	Board(COORD StartPosition, short height, short width);
	void PrintBoard();
	bool SnakeReachedWall(SevagSnake sevagSnake);
	const short& height() const;
	const short& width() const;
	const COORD& startPosition() const;
private:
	COORD startPosition_;
	short height_;
	short width_;
};

