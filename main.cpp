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
    if (argc != 3)
    {
        std::cout << "Please give two players. Example: ./executable player1.json player2.json\n";

        return 1;
    }

    try
    {
        Loop loop = Loop(argv);
        loop.Play();
        loop.ShowWinner();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }

    return 0;
};