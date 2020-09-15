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
#include "loop.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 7)
    {
        std::cout << "Please give two players. Example: ./executable Maple 150 10 Sally 45 30\n";

        return 1;
    }

    Loop loop = Loop(argv);
    loop.ShowPlayers();
    loop.Play();
    loop.ShowWinner();

    return 0;
};