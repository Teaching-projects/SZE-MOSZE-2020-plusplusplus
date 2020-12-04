#pragma once

#include <ostream>

#include "../Game.h"

class Renderer
{
protected:
    virtual void renderOutput(const Game &game, bool withLightRadius) const;

public:
    Renderer(){};
    ~Renderer(){};

    virtual void render(const Game &) const;
};
