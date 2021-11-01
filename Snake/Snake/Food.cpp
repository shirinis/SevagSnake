#include "Board.h"
#include "Food.h"
#include "SevagSnake.h"
#include "HelperFunctions.h"

Food::Food(const int SCORE, Board& Board, std::random_device& RandomDevice) :
    SCORE_(SCORE),
    Board_(Board),
    distributionY_(
        Board_.startPosition().Y + 1,
        Board_.startPosition().Y + Board_.height() - 2),
    distributionX_(
        Board_.startPosition().X + 1,
        Board_.startPosition().X + Board_.width() - 2)
{
    x_ = -1;
    y_ = -1;

    mt_.seed(RandomDevice());
};

int Food::getScore() {
    return SCORE_;
}

void Food::generate(SevagSnake Snake) {
    const char FOOD_SYMBOL = '*';

    x_ = distributionX_(mt_);
    y_ = distributionY_(mt_);

    if (!(Snake.occupiesPosition({ x_,y_ }))) {
        consoleservice::PrintChar({ x_,y_ }, FOOD_SYMBOL);
    }
    else {
        generate(Snake);
    }
}
        

bool Food::isEaten(short SnakeHeadX, short snakeHeadY) {
    return SnakeHeadX == x_ && snakeHeadY == y_;
}
