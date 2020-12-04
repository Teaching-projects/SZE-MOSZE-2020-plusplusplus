#pragma once

#include <ostream>

#include "Renderer.h"

class TextRenderer : public Renderer
{
protected:
    std::ostream *output = &std::cout;

    void renderOutput(bool withLightRadius) const;

public:
    TextRenderer(){};
    TextRenderer(std::ostream *output)
    {
        setOutputStream(output);
    };

    virtual void render(const Game &) const;
    void setOutputStream(std::ostream *output)
    {
        this->output = output;
    };
};
