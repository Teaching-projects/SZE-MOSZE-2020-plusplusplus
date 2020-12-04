#pragma once

#include <ostream>

#include "../Game.h"

class Renderer
{
protected:
    virtual void renderOutput(bool withLightRadius) const;

public:
    Renderer(){};
    ~Renderer(){};

    virtual void render(const Game &) const;
};
