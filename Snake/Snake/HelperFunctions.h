#pragma once

#include <windows.h>

namespace consoleservice {
    void PrintChar(COORD position, char chr);
    void setCursorLocationToEnd(short width, short height);
    void setCursorLocation(COORD pos);
    void setConsoleFont();
}

namespace containerservice {
    template <typename Container>
    bool contains(Container const& c, typename Container::const_reference v);
}