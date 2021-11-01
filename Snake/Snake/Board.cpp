#include "Board.h"
#include "windows.h"
#include <iostream>
#include "HelperFunctions.h"
#include "SevagSnake.h"

Board::Board(COORD StartPosition, short height, short width) {
	startPosition_ = StartPosition;
	height_ = height;
	width_ = width;
}

const COORD& Board::startPosition() const {
    return this->startPosition_; 
}

const short& Board::height() const {
    return height_;
}

const short& Board::width() const {
    return width_;
}

void Board::PrintBoard() {
    consoleservice::setConsoleFont();

    for (short i = 0; i < this->height_; i++) {
        consoleservice::setCursorLocation({this->startPosition_.X, this->startPosition_.Y + i
    });
        for (short j = 0; j < this->width_; j++) {
            if (i == 0 || j == 0 || i == this->height_ - 1 || j == this->width_ - 1) {
                std::cout << "#";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}


bool Board::SnakeReachedWall(SevagSnake SevagSnake) {
    switch (SevagSnake.getDirection()) {
    case SevagSnake::Direction::right:
        if (SevagSnake.headX() >= startPosition_.X + width_ - 1 ) {
            return true;
        }
        break;
    case SevagSnake::Direction::left:
        if (SevagSnake.headX() <= startPosition_.X) {
            return true;
        }
        break;
    case SevagSnake::Direction::down:
        if (SevagSnake.headY() >= startPosition_.Y + height_ - 1) {
            return true;
        }
        break;
    case SevagSnake::Direction::up:
        if (SevagSnake.headY() <= startPosition_.Y ) {
            return true;
        }
        break;
    }

    return false;
}