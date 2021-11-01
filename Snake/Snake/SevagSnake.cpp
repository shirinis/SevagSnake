#include "SevagSnake.h"
#include "HelperFunctions.h"
#include <vector>
#include <chrono>
#include "Board.h"
#include <list>
#include <thread> //sleep_for()
#include <iostream>

SevagSnake::SevagSnake(Board &Board, short velocityPixelsPer100ms) :Board_(Board) {
	snake_ = {
		{Board.startPosition().X + Board.width() / 2,
		Board.startPosition().Y +  Board.height() / 2},
		{Board.startPosition().X + Board.width() / 2 + 1, 
		Board.startPosition().Y + Board.height() / 2 } 
	};

	velocityPixelsPer100ms_ = velocityPixelsPer100ms;
	Board_ = Board;
	direction_ = Direction::noDirection;
}

const SevagSnake::Direction& SevagSnake::getDirection() const {
	return direction_;
}

const short& SevagSnake::headX() const {
	return head().X;
}

const short& SevagSnake::headY() const {
	return head().Y;
}

 COORD SevagSnake::head() const {
	return *--snake_.end();

}

 COORD SevagSnake::tail() const {
	 return snake_.front();
 }

 COORD SevagSnake::tailNext() const {
	 auto it = snake_.begin();
	 return *++it;
 }

void SevagSnake::displaySnake() {

	for (auto it = snake_.begin(); it != --snake_.end() ;++it) {
		consoleservice::PrintChar(*it, BODY_);
	}
	consoleservice::PrintChar(snake_.back(), HEAD_);
}


bool SevagSnake::isHit() {
	return Board_.SnakeReachedWall(*this) || hitSelf();
}

bool SevagSnake::hitSelf() const {
	short count = 0;

	for ( auto it = snake_.begin(); it != snake_.end(); ++it) {
		COORD pos = *it;
		if(pos.X == headX() && pos.Y == headY()) {
			if (count >= 1) {
				return true;
			}
			else {
				count += 1;
			}
		}
	}
	return false;
}

void SevagSnake::grow() {
	if (tail().X - tailNext().X == 1) {
		snake_.push_front({ tail().X + 1, tail().Y });
	}
	else if (tail().X - tailNext().X == -1) {
		snake_.push_front({ tail().X - 1, tail().Y });
	}
	else if (tail().Y - tailNext().Y == 1) {
		snake_.push_front({ tail().X , tail().Y + 1 });
	}
	else {
		snake_.push_front({ tail().X , tail().Y - 1 });
	}

	displaySnake();
}

bool SevagSnake::occupiesPosition(COORD position) {
	for (const COORD& pos : snake_) {
		if (pos.X == position.X && pos.Y == position.Y) {
			return true;
		}
	}
	return false;
}


void SevagSnake::moveRight() {
	move(Direction::right);
}
void SevagSnake::moveUp() {
	move(Direction::up);
}
void SevagSnake::moveLeft() {
	move(Direction::left);
}
void SevagSnake::moveDown() {
	move(Direction::down);
}

void SevagSnake::move(Direction direction) {
	//if AreOppositeDirections(direction, direction_ ) then break

	direction_ = direction;

	if (!isHit()) {
		consoleservice::PrintChar(snake_.front(), ' '); //erase tail from screen
		snake_.pop_front(); //remove old tail from container

		switch (direction_){
		case Direction::right:
			snake_.push_back({ snake_.back().X + 1 , snake_.back().Y });
			break;
		case Direction::up:
			snake_.push_back({ snake_.back().X , snake_.back().Y - 1 });
			break;
		case Direction::left:
			snake_.push_back({ snake_.back().X -1 , snake_.back().Y });
			break;
		case Direction::down:
			snake_.push_back({ snake_.back().X , snake_.back().Y + 1 });
			break;
		}
		
		this->displaySnake();

		std::this_thread::sleep_for(std::chrono::milliseconds(100 / this->velocityPixelsPer100ms_));
	}
}

void SevagSnake::keepMoving() {
	if (direction_ != Direction::noDirection) {
		move(direction_);
	}
}

