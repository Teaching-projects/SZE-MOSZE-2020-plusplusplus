#include "../renderer/Corner.h"
#include "../renderer/HeroTextRenderer.h"
#include "../renderer/ObserverTextRenderer.h"
#include "../Game.h"

#include <gtest/gtest.h>

TEST(RendererTest, Corner)
{
    Game g("../maps/map1.txt");

    ASSERT_EQ(Corner::Get(Corner::Type::TOP_LEFT, false, g), Location(0, 0));
    ASSERT_EQ(Corner::Get(Corner::Type::TOP_LEFT, true, g), Location(0, 0));

    ASSERT_EQ(Corner::Get(Corner::Type::TOP_RIGHT, false, g), Location(g.map->getWidth() - 1, 0));
    ASSERT_EQ(Corner::Get(Corner::Type::TOP_RIGHT, true, g), Location(g.map->getWidth() - 1, 0));

    ASSERT_EQ(Corner::Get(Corner::Type::BOTTOM_LEFT, false, g), Location(0, g.map->getHeight() - 1));
    ASSERT_EQ(Corner::Get(Corner::Type::BOTTOM_LEFT, true, g), Location(0, g.map->getHeight() - 1));

    ASSERT_EQ(Corner::Get(Corner::Type::BOTTOM_RIGHT, false, g), Location(g.map->getWidth() - 1, g.map->getHeight() - 1));
    ASSERT_EQ(Corner::Get(Corner::Type::BOTTOM_RIGHT, true, g), Location(g.map->getWidth() - 1, g.map->getHeight() - 1));
}

TEST(RendererTest, PrintGameBoard)
{
    Game g1("../maps/map1.txt");
    std::string expect1("\n╔════════════════════════════╗\n║██░░░░░░░░░░░░░░████░░░░████║\n║██░░░░████░░░░░░░░██████░░░░║\n║████░░░░██░░░░░░██░░░░██░░░░║\n║██████░░░░░░░░░░░░░░██░░░░░░║\n║████░░░░░░░░░░░░░░░░░░██░░░░║\n╚════════════════════════════╝\n");
    std::stringstream res1;
    g1.registerRenderer(new HeroTextRenderer(res1));
    g1.print();
    ASSERT_EQ(res1.str(), expect1);

    Game g2("../maps/map2.txt");
    std::string expect2("\n╔════════════════════════════╗\n║████████████████████████████║\n║██░░░░░░██░░░░████████░░░░██║\n║██░░████████░░░░████░░░░██░░║\n║██░░░░░░██░░░░████░░░░██░░░░║\n║██████░░██░░████░░░░██░░░░░░║\n║██░░░░░░░░░░░░░░░░░░██░░░░░░║\n║██████████████████░░░░░░░░░░║\n╚════════════════════════════╝\n");
    std::stringstream res2;
    g2.registerRenderer(new HeroTextRenderer(res2));
    g2.print();
    ASSERT_EQ(res2.str(), expect2);
}

TEST(RendererTest, PrintHeroVisionFromCenter)
{
    Game g("../maps/map3.txt");
    Damage dmg;
    Hero h("H", 100, dmg, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, "");
    g.putHero(h, 2, 2);

    std::string expect("\n╔══════╗\n║░░░░░░║\n║░░┣┫░░║\n║░░██░░║\n╚══════╝\n");
    std::string expect2("\n╔════════════╗\n║████████░░██║\n║██░░░░░░░░██║\n║░░░░┣┫░░░░██║\n║██░░██░░░░██║\n║██░░░░░░░░██║\n║████░░████░░║\n╚════════════╝\n");

    std::stringstream res, res2;
    g.registerRenderer(new HeroTextRenderer(res));
    g.registerRenderer(new ObserverTextRenderer(res2));
    g.print();
    ASSERT_EQ(res.str(), expect);
    ASSERT_EQ(res2.str(), expect2);
}

TEST(RendererTest, PrintHeroVisionFromBorder)
{
    Game g("../maps/map3.txt");
    Damage dmg;
    Hero h("H", 100, dmg, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, "");
    g.putHero(h, 0, 2);

    std::string expect("\n╔════╗\n║██░░║\n║┣┫░░║\n║██░░║\n╚════╝\n");
    std::stringstream res;
    g.registerRenderer(new HeroTextRenderer(res));
    g.print();
    ASSERT_EQ(res.str(), expect);

    Game g2("../maps/map3.txt");
    g2.putHero(h, 2, 5);

    std::string expect2("\n╔══════╗\n║░░░░░░║\n║██┣┫██║\n╚══════╝\n");
    std::stringstream res2;
    g2.registerRenderer(new HeroTextRenderer(res2));
    g2.print();
    ASSERT_EQ(res2.str(), expect2);

    Game g3("../maps/map3.txt");
    g3.putHero(h, 4, 0);

    std::string expect3("\n╔══════╗\n║██┣┫██║\n║░░░░██║\n╚══════╝\n");
    std::stringstream res3;

    g3.registerRenderer(new HeroTextRenderer(res3));
    g3.print();
    ASSERT_EQ(res3.str(), expect3);
}

TEST(RendererTest, PrintHeroVisionFromCorner)
{
    Game g("../maps/map3.txt");
    Damage dmg;
    Hero h("H", 100, dmg, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, "");
    g.putHero(h, 5, 5);

    std::string expect("\n╔════╗\n║░░██║\n║██┣┫║\n╚════╝\n");
    std::string expect2("\n╔════════════╗\n║████████░░██║\n║██░░░░░░░░██║\n║░░░░░░░░░░██║\n║██░░██░░░░██║\n║██░░░░░░░░██║\n║████░░████┣┫║\n╚════════════╝\n");

    std::stringstream res, res2;
    g.registerRenderer(new HeroTextRenderer(res));
    g.registerRenderer(new ObserverTextRenderer(res2));
    g.print();
    ASSERT_EQ(res.str(), expect);
    ASSERT_EQ(res2.str(), expect2);
}