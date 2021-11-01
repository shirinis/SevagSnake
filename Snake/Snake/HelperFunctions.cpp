#ifdef _WIN32
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include "HelperFunctions.h"
#include <iostream>
#include <windows.h>
#include <cwchar>


namespace consoleservice {
    void PrintChar(COORD position, char chr) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(console, position);
        std::cout << chr;
    }

    void setCursorLocationToEnd(short width, short height) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);;
        SetConsoleCursorPosition(console, { width, height });
   }

    void setCursorLocation(COORD pos) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);;
        SetConsoleCursorPosition(console, pos);
    }

    void setConsoleFont() {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 12;                   // Width of each character in the font
        cfi.dwFontSize.Y = 12;                  // Height
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }
}




