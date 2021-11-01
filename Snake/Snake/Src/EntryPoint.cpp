#include <iostream>
#include <conio.h> // For Gettings Keyboard Strikes
#include <Windows.h>// For Setting Console Cursor Position

#include "SevagSnake.h"
#include "HelperFunctions.h"
#include "Board.h"
#include "Food.h"

const short HEIGHT_PIXELS = 25;
const short WIDTH_PIXELS=  25;
const COORD START_POSITION = { 10,0 };
const int VELOCITY_PIXELS_PER_100MS = 1;
const int FOOD_SCORE = 10;
int score = 0;

int main()
{
    Board Board(START_POSITION, HEIGHT_PIXELS, WIDTH_PIXELS);
    Board.PrintBoard();

    SevagSnake Snake(Board, VELOCITY_PIXELS_PER_100MS);
    Snake.displaySnake();

    std::random_device RandomDevice;
    Food Food(FOOD_SCORE, Board, RandomDevice);
    Food.generate(Snake);
    
    while (!Snake.isHit()) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'd':
                    Snake.moveRight();
                    break;
                case 'w':
                    Snake.moveUp();
                    break;
                case 's':
                    Snake.moveDown();
                    break;
                case 'a':
                    Snake.moveLeft();
                    break;
                default:
                    break;
            } 
        }
        else {
            Snake.keepMoving();
        }

        if (Food.isEaten(Snake.headX(), Snake.headY())) {
            score += Food.getScore();
            Snake.grow();
            Food.generate(Snake);
        }
    }
        
    consoleservice::setCursorLocationToEnd(WIDTH_PIXELS, HEIGHT_PIXELS);
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
  
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
