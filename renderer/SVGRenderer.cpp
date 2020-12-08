#include <fstream>

#include "SVGRenderer.h"
#include "Corner.h"

void SVGRenderer::renderOutput(const Game &game, bool withLightRadius) const
{
    const Location topLeft = Corner::Get(Corner::Type::TOP_LEFT, withLightRadius, game);
    const Location topRight = Corner::Get(Corner::Type::TOP_RIGHT, withLightRadius, game);
    const Location bottomLeft = Corner::Get(Corner::Type::BOTTOM_LEFT, withLightRadius, game);
    const Location bottomRight = Corner::Get(Corner::Type::BOTTOM_RIGHT, withLightRadius, game);

    const int width = (topRight.x - topLeft.x + 1) * 10;
    const int height = (bottomLeft.y - topLeft.y + 1) * 10;

    std::ofstream file(outFile);
    file << "<svg viewBox=\"0 0 " << width << ' ' << height << "\" xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\">";

    for (int y = topLeft.y; y <= bottomLeft.y; y++)
    {
        for (int x = topLeft.x; x <= bottomRight.x; x++)
        {
            const int left = (x - topLeft.x) * 10;
            const int top = (y - topLeft.y) * 10;

            std::string img = "";
            const unsigned int monsterCountInField = game.getMonsterCountInField(x, y);
            if (game.hero != nullptr && game.hero->isAlive() && game.hero->getLocation() == Location(x, y))
            {
                img = game.hero->getTexture();
            }
            else if (monsterCountInField != 0)
            {
                img = game.getMonsterTextureInField(x, y);
            }
            else
            {
                img = game.map->getFieldType(x, y) == Map::Wall ? game.getWallTexture()
                                                                : game.getFreeTexture();
            }

            if (img != "")
            {
                file << "<image x=\"" << left << "\" y=\"" << top << "\" width=\"10\" height=\"10\" href=\""
                     << img
                     << "\" />";
            }
            else
            {
                file << "<rect fill=\"black\" x=\"" << left << "\" y=\"" << top << "\" width=\"10\" height=\"10\" />";
            }
        }
    }

    file << "</svg>";
    file.close();
}