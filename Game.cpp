#include <algorithm>

#include "Game.h"
#include "Hero.h"
#include "Map.h"

using namespace std;

unsigned int Game::getMonsterCountInField(const int x, const int y) const
{
	return count_if(monsters.begin(), monsters.end(),
					[x, y](const Monster *monster) { return monster->getX() == x && monster->getY() == y; });
}

void Game::setMap(const Map &map)
{
	if (this->gameState == Game::GameState::started)
	{
		throw Game::GameAlreadyStartedException();
	}
	else if (hero != nullptr || !monsters.empty())
	{
		throw Game::AlreadyHasUnitsException();
	}

	// Delete map
	if (this->map != nullptr)
		delete this->map;

	// Set map
	this->map = new Map(map);
}

void Game::putHero(Hero &hero, const int x, const int y)
{
	// Check the availability of the field located at the provided location
	checkFieldAvailability(x, y);

	if (this->gameState == Game::GameState::started)
	{
		throw Game::GameAlreadyStartedException();
	}
	else if (this->hero != nullptr)
	{
		throw Game::AlreadyHasHeroException();
	}
	else
	{
		this->hero = &hero;
		this->hero->setLocation(Unit::Location(x, y));
	}
}

void Game::putMonster(Monster &monster, const int x, const int y)
{
	// Check the availability of the field located at the provided location
	checkFieldAvailability(x, y);

	monster.setLocation(Unit::Location(x, y));
	monsters.push_back(&monster);
}

void Game::removeHero()
{
	if (this->hero != nullptr)
		this->hero = nullptr;
}

void Game::removeFallenMonsters()
{
	this->monsters.remove_if([](Monster *monster) { return !monster->isAlive(); });
}

void Game::checkFieldAvailability(const int x, const int y) const
{
	if (map == nullptr)
	{
		throw Map::WrongIndexException("No map is set!");
	}
	else if (map->getFieldType(x, y) == Map::Wall)
	{
		throw Game::OccupiedException("There is a wall object that blocking at the provided indicies.");
	}
}

void Game::run()
{
	string resultString;

	// Check whether the hero or map is unsset
	if (hero == nullptr || map == nullptr)
	{
		throw Game::NotInitializedException();
	}

	// Show untouched game board
	print(cout);

	// Start the game loop
	loop();

	// After loop is ended check for survived Units
	if (hero->isAlive())
	{
		// Result of the game
		resultString = hero->getName() + " has cleared the map.";
	}
	else
	{
		// Result of the game
		resultString = "The hero died.";

		// Remove the hero from the game
		removeHero();
	}

	// Change game state
	setGameState(Game::GameState::notStarted);

	// Show the result of the game
	cout << resultString << endl;
}

void Game::loop()
{
	// Change game state
	setGameState(Game::GameState::started);

	string directionKey;
	cout << "Move the Hero with the following commands:"
		 << endl
		 << "north\tMove up"
		 << endl
		 << "south\tMove down"
		 << endl
		 << "west\tMove left"
		 << endl
		 << "east\tMove right" << endl;

	while (hero->isAlive() && !this->monsters.empty())
	{
		// Get direction
		do
		{
			cout << "Move to direction:";
			cin >> directionKey;

		} while (directions.count(directionKey) == 0);

		// Move Hero
		move(directions.at(directionKey));

		// Show Game board
		print(cout);
	}
}

void Game::move(const Game::Direction direction)
{
	int x, y;

	// Move to direction
	switch (direction)
	{
	case Game::Direction::NORTH:
	{
		y = hero->getY() - 1;

		if (y >= 0 && map->isFieldFree(hero->getX(), y))
			hero->setY(y);
		break;
	}

	case Game::Direction::SOUTH:
	{
		y = hero->getY() + 1;

		if (y < map->getHeight() && map->isFieldFree(hero->getX(), y))
			hero->setY(y);
		break;
	}

	case Game::Direction::WEST:
	{
		x = hero->getX() - 1;

		if (x >= 0 && map->isFieldFree(x, hero->getY()))
			hero->setX(x);
		break;
	}

	case Game::Direction::EAST:
	{
		x = hero->getX() + 1;

		if (x < map->getWidth() && map->isFieldFree(x, hero->getY()))
			hero->setX(x);
		break;
	}

	default:
		break;
	}

	// Fight
	for (Monster *monster : this->monsters)
	{
		if (monster->getLocation() == hero->getLocation())
		{
			this->hero->fightTilDeath(*monster);
		}
	}

	// Remove fallen units
	removeFallenMonsters();
}

void Game::print(ostream &stream) const
{
	// Top border
	stream << endl
		   << icons.at(Game::Icon::TOP_LEFT);

	for (int x = 0; x < map->getWidth(); x++)
	{
		stream << icons.at(Game::Icon::HORIZONTAL);
	}
	stream << icons.at(Game::Icon::TOP_RIGHT) << endl;

	// Side borders and Game board
	for (int y = 0; y < map->getHeight(); y++)
	{
		stream << icons.at(Game::Icon::VERTICAL);
		for (int x = 0; x < map->getWidth(); x++)
		{
			const unsigned int monsterCountInField = getMonsterCountInField(x, y);
			if (hero != nullptr && hero->isAlive() && hero->getLocation() == Unit::Location(x, y))
			{
				stream << icons.at(Game::Icon::HERO);
			}
			else if (monsterCountInField != 0)
			{
				stream << (monsterCountInField > 1 ? icons.at(Game::Icon::MONSTERS) : icons.at(Game::Icon::MONSTER));
			}
			else
				stream << (map->getFieldType(x, y) == Map::Wall ? icons.at(Game::Icon::WALL_FIELD) : icons.at(Game::Icon::FREE_FIELD));
		}
		stream << icons.at(Game::Icon::VERTICAL) << endl;
	}

	// Bottom border
	stream << icons.at(Game::Icon::BOTTOM_LEFT);

	for (int x = 0; x < map->getWidth(); x++)
	{
		stream << icons.at(Game::Icon::HORIZONTAL);
	}
	stream << icons.at(Game::Icon::BOTTOM_RIGHT) << endl;
}