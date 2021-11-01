#pragma once

#include <random>

class Board;
class SevagSnake;

class Food
{
public:
	Food(const int SCORE, Board& Board,
		std::random_device& RandomDevice);
	int getScore();
	void generate(SevagSnake Snake);
	bool isEaten(short SnakeHeadX, short snakeHeadY);

private:
	const int SCORE_;
	Board Board_;
	std::mt19937 mt_;
	std::uniform_int_distribution<short> distributionX_;
	std::uniform_int_distribution<short> distributionY_;
	short x_;
	short y_;
};

