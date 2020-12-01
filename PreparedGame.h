#pragma once

#include "Game.h"
#include "MarkedMap.h"

class PreparedGame : private Game
{
private:
public:
    PreparedGame(const std::string &file);
    void run();
};
