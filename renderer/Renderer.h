#pragma once

#include <ostream>

#include "../Game.h"

class Game;
class Renderer
{
protected:
    virtual void renderOutput(const Game &game, bool withLightRadius) const = 0;

public:
    Renderer(){};
    ~Renderer(){};

    virtual void render(const Game &) const = 0;
};
