/**
 * @file main.cpp
 *
 * @brief This file contains the 'main' function. Program execution begins and ends there.
 *
 * @author +++ Team
 *  https://github.com/msze-plusplusplus
 *  - Balogh Máté
 *  - Baranyai Bence
 *  - Karcag Tamás
 *
 * For: MOSZE - GKNB_INTM006
 * 
*/
#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Map.h"
#include "Game.h"
#include "PreparedGame.h"

#include "renderer/HeroTextRenderer.h"
#include "renderer/ObserverTextRenderer.h"

const std::map<int, std::string> error_messages = {
    {1, "Bad number of arguments. Operation mode and data file should be provided."},
    {2, "The provided mode is invalid (scenario / prepare)"},
    {3, "The provided data file is not accessible."},
    {4, "The provided data file is invalid."},
    {5, "JSON parsing error."}};

enum mode
{
    Scenario,
    Prepare
};

const std::map<std::string, mode> modes = {
    {"scenario", mode::Scenario},
    {"prepare", mode::Prepare},
};

void bad_exit(int exitcode)
{
    std::cerr
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

void scenarioMode(std::string scenarioFile)
{
    std::string hero_file;
    std::list<std::string> monster_files;

    try
    {
        JSON scenario = JSON::parseFromFile(scenarioFile);
        if (!(scenario.count("hero") && scenario.count("monsters")))
            bad_exit(4);
        else
        {
            hero_file = scenario.get<std::string>("hero");
            JSON::list monster_file_list = scenario.get<JSON::list>("monsters");
            for (auto monster_file : monster_file_list)
                monster_files.push_back(std::get<std::string>(monster_file));
        }
    }
    catch (const JSON::ParseException &e)
    {
        bad_exit(5);
    }

    try
    {
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto &monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));

        // Create map from file
        Map map("maps/map1.txt");

        // Create the empty game
        Game game;

        // Set map for the game
        game.setMap(map);

        // Put the Hero to the gameboard
        game.putHero(hero, 1, 0);

        // Put a Monster to the gameboard
        game.putMonster(monsters.front(), 4, 0);
        if (monsters.size() >= 4)
        {
            monsters.pop_front();
            monsters.pop_front();
            game.putMonster(monsters.front(), 3, 0);
        }

        game.registerRenderer(new HeroTextRenderer());
        auto out = std::ofstream("log.txt");
        game.registerRenderer(new ObserverTextRenderer(out));

        // Start the game
        game.run();
    }
    catch (const JSON::ParseException &e)
    {
        bad_exit(5);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        bad_exit(1);
    }

    if (!modes.count(argv[1]))
    {
        bad_exit(2);
    }

    if (!std::filesystem::exists(argv[2]))
    {
        bad_exit(3);
    }

    switch (modes.at(argv[1]))
    {
    case mode::Scenario:
        scenarioMode(argv[2]);
        break;

    case mode::Prepare:
        PreparedGame game(argv[2]);

        game.registerRenderer(new HeroTextRenderer());
        auto out = std::ofstream("log.txt");
        game.registerRenderer(new ObserverTextRenderer(out));

        game.run();
        break;
    }

    return 0;
}
