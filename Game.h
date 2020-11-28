#include <iostream>
#include <list>
#include <map>

#include "Map.h"
#include "Hero.h"
#include "Monster.h"

/**
 * @class Game
 *
 * @brief It defines a Game board.
 *
 * It contains the map, the placed Hero and the Monster(s).
 *
 * The Hero can move on the free fields of the map.
 * If the Hero meets a Monster they attack each other.
 *
 * @author +++ Team
 *
 * @version 1.0
 *
 * @date 2020-11-28
 *
 * Created on: 2020-11-28
 *
*/
class Game
{
private:
	/**
	 * Enum type for the gameboard icon definitions.
	 */
	enum Icon
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		HORIZONTAL,
		VERTICAL,
		FREE_FIELD,
		WALL_FIELD,
		HERO,
		MONSTER,
		MONSTERS
	};

	/**
	 * Enum type for the move direction definitons.
	 */
	enum Direction
	{
		NORTH,
		EAST,
		WEST,
		SOUTH
	};

	/**
	 * Type definition for the mapped Directions.
	 */
	typedef std::map<std::string, Direction> directionKeyMap;

	/**
	 * Type definition for the mapped Icons.
	 */
	typedef std::map<Icon, std::string> iconKeyMap;

	/**
	 * The Directions mapped with their key.
	 */
	inline static const directionKeyMap directions = {
		{"north", Direction::NORTH},
		{"east", Direction::EAST},
		{"west", Direction::WEST},
		{"south", Direction::SOUTH}};

	/**
	 * The Icons mapped with their key.
	 */
	inline static const iconKeyMap icons = {
		{Icon::TOP_LEFT, "\u2554"},
		{Icon::TOP_RIGHT, "\u2557"},
		{Icon::BOTTOM_LEFT, "\u255A"},
		{Icon::BOTTOM_RIGHT, "\u255D"},
		{Icon::HORIZONTAL, "\u2550\u2550"},
		{Icon::VERTICAL, "\u2551"},
		{Icon::FREE_FIELD, "\u2591\u2591"},
		{Icon::WALL_FIELD, "\u2588\u2588"},
		{Icon::HERO, "\u2523\u252B"},
		{Icon::MONSTER, "\u004D\u2591"},
		{Icon::MONSTERS, "\u004D\u004D"}};

	/**
	 * The map of the game.
	 */
	Map *map;

	/**
	 * The Hero of the game.
	 */
	Hero *hero;

	/**
	 * The Monster(s) of the game.
	 */
	std::list<Monster> monsters;

	/**
	 * The state of the game.
	 */
	bool isGameInProgress;

	/**
	 * Get the count of Monster(s) in an actual on a field located at the position provided by the indicies.
	 * @param x The horizontal position (index) on the map to be checked.
	 * @param y The vertical position (index) on the map to be checked.
	 * @return Count of the Monster(s) located at the actual field.
	 */
	unsigned int getMonsterCountInField(const int x, const int y) const;

public:
	/**
	 * Game constructor.
	 * It creates an empty Game object.
	 * @param name Name of Unit.
	 * @param hp Health points of Unit.
	 * @param damage Attack damage of Unit.
	 * @param attackCooldown Attack cooldown of Unit. **Minimum** time intervall between two attack.
	 * @param xp Starter experience point of the character.
	 */
	Game() : map(nullptr), hero(nullptr), isGameInProgress(false){};

	/**
	 * Game constructor.
	 * It creates a Unit object with a map from the given parameters.
	 * @param mapfilename Name of the file of the map.
	 */
	explicit Game(const std::string &mapfilename) : map(new Map(mapfilename)), hero{nullptr}, isGameInProgress(false){};

	/**
	 * Game copy constructor.
	 * It creates a new Unit object with the values of the given Game object.
	 * @param mapfilename Name of the file of the map.
	 */
	Game(const Game &game) : map(new Map(*game.map)), hero(new Hero(*game.hero)), isGameInProgress(game.isGameInProgress){};

	/**
	 * Game copy assignment.
	 * It assigns new values of the given Game object to this Game object.
	 * @param game The other Game object.
	 */
	Game &operator=(const Game &game)
	{
		if (this != &game)
		{
			if (map != nullptr)
				delete map;
			if (hero != nullptr)
				delete hero;

			this->map = new Map(*game.map);
			this->hero = new Hero(*game.hero);
			this->isGameInProgress = game.isGameInProgress;
		}

		return *this;
	};

	/**
	 * Game destructor.
	 * It destructs the Game object
	 */
	~Game()
	{
		if (this->map != nullptr)
			delete this->map;
		if (this->hero != nullptr)
			delete this->hero;
	};

	/**
	 * Set map for the game.
	 * @param map The map to be set.
	 * @throw Game::GameAlreadyStartedException When the game has started.
	 * @throw Game::AlreadyHasUnitsException When there are unit(s) in the map.
	 */
	void setMap(const Map &map);

	/**
	 * Put Hero to the map.
	 * @param hero The Hero to be put to the map.
	 * @param x The horizontal position (index) of the Hero on the map.
	 * @param y The vertical position (index) of the Hero on the map.
	 * @throw Map::WrongIndexException When the provided position of the Hero is a Wall block, a not existing one or no map is set.
	 * @throw Game::AlreadyHasHeroException When there is another Hero on the map.
	 * @throw Game::GameAlreadyStartedException When the game has started.
	 */
	void putHero(const Hero &hero, const int x, const int y);

	/**
	 * Put Monster to the map.
	 * @param monster The Monster to be put to the map.
	 * @param x The horizontal position (index) of the Monster on the map.
	 * @param y The vertical position (index) of the Monster on the map.
	 * @throw Map::WrongIndexException When the provided position of the Monster is a Wall block, a not existing one or no map is set.
	 */
	void putMonster(Monster monster, const int x, const int y);

	/**
	 * Remove the hero from the map and from the game.
	 */
	void removeHero();

	/**
	 * Remove the fallen Monster(s) from the map and from the game.
	 * 
	 */
	void removeFallenMonsters();

	/**
	 * Check whether the block located on the provided index positions is available or not.
	 * @param x The horizontal position (index) on the map to be checked.
	 * @param y The vertical position (index) on the map to be checked.
	 * @throw Map::WrongIndexException When the block of the map on the provided index positions is a Wall block, a not existing one or no map is set.
	 */
	void checkFieldAvailability(const int x, const int y) const;

	/**
	 * Start the running of the game.
	 * @throw Game::NotInitializedException When no Hero or no Monster has been put on the map.
	 */
	void run();

	/**
	 * Handle one loop of the game.
	 */
	void loop();

	/**
	 * Move the Hero on the map.
	 * @param direction The direction where the Hero should move to.
	 */
	void move(const Game::Direction direction);

	/**
	 * Show the actual state of the game with the set map and the placed Hero, Monster(s) on it.
	 * @param stream The destination output stream.
	 */
	void print(std::ostream &stream) const;

	/**
	 * @class OccupiedException
	 * @brief Occupied exception to be called when a field is occupied by a wall object
	 */
	class OccupiedException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor which takes a description as parameter.
		 * @param description Description of wrong index error.
		*/
		explicit OccupiedException(const std::string &description) : std::runtime_error("OccupiedException" + description) {}
	};

	/**
	 * @class OccupiedException
	 * @brief Already Has Hero exception to be called when permitted operations are about to be run while there are still Hero on the map. 
	*/
	class AlreadyHasHeroException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor.
		*/
		explicit AlreadyHasHeroException() : std::runtime_error("Already has hero") {}
	};

	/**
	 * @class OccupiedException
	 * @brief Already Has Units exception to be called when permitted operations are about to be run while there are still units on the map. 
	*/
	class AlreadyHasUnitsException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor.
		*/
		explicit AlreadyHasUnitsException() : std::runtime_error("Already has units") {}
	};
	/**
	* @class OccupiedException
	* @brief Not Initialized exception to be called when permitted operations are about to be run before the game has been initialized.
	*/
	class NotInitializedException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor of the exception.
		*/
		explicit NotInitializedException() : std::runtime_error("Game is not initialized. It cannot be started.") {}
	};

	/**
	* @class GameAlreadyStartedException
	* @brief Game Already Started exception to be called when permitted operations are about to be run after the game has been started.
	*/
	class GameAlreadyStartedException : virtual public std::runtime_error
	{
	public:
		/**
		 * Constructor of the exception.
		*/
		explicit GameAlreadyStartedException() : std::runtime_error("Game already has been started.") {}
	};
};