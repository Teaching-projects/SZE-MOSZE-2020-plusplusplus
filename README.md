# RPG Game

## MOSZE - GKNB_INTM006 - 2020. Autumn

### Team: +++ (PlusPlusPlus)

![Test Workflow](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Test%20Workflow/badge.svg)
![Unit Tests](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Unit%20Tests/badge.svg)
![Documentation](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Documentation%20workflow/badge.svg)
[![Documentation](https://img.shields.io/badge/Documentation-Here!-blue)](https://teaching-projects.github.io/SZE-MOSZE-2020-plusplusplus/)

#### Team Members:

- Balogh Máté
- Baranyai Bence
- Karcag Tamás

### Make commands

`Make` is useful to have nice and easy commands to run applications. This is the list of commands we have:

- `make`:

  - `compile`: Builds the application (./build/game.out) (_default target_)
  - `run`: Executes the built binary (You should add the `MODE` and `FILE` parameters)
    - `make run MODE=scenario FILE=scenarios/scenario1.json`
    - `make run MODE=prepare FILE=prepare/prepare1.json`
  - `test`: Run all tests
  - `unittest`: Run unit tests
  - `documentation`: Generate the documentation
  - `memory_leak_check`: Run memory leak test
  - `static_code_analysis`: Run primary and secondary static code analysis
  - `clean`: Clean built files

### Executing application

#### Inputs:

Compiled application should be called with **2** parameters, first a game mode (_scenario_ or _prepare_), and a data file pointing to a `json` file with a scenario or a prepared scene.

This scenario is describing a hero object and his/her enemies (_monsters_) object.

```json
{
  "hero": "path/to/hero.json",
  "monsters": [
    "path/to/monster1.json",
    "path/to/monster2.json",
    "path/to/monster3.json"
  ]
}
```

The prepared file also includes a map and the monsters can be numbered, the map here can be also marked.

```json
{
  "map": "maps/map2.txt",
  "hero": "units/Dark_Wanderer.json",
  "monster-1": "units/Fallen.json",
  "monster-2": "units/Zombie.json",
  "monster-3": "units/Blood_Raven.json"
}
```

The `hero` object is containing a path to the hero's `json` object what is containing all data for the hero.

Data:

- Name (_name_)
- Base health points - **HP** (_base_health_points_)
- Damage - **DMG** (_damage_) (optional - default 0)
- Damage - **MAGIC DMG** (_magical_damage_) (optional - default 0)
- Base attack cooldown - **CD** (_base_attack_cooldown_)
- Experience per level (_experience_per_level_)
- Health point bonus per level - **HP BONUS** (_health_point_bonus_per_level_)
- Damage bonus per level - **DMG BONUS** (_damage_bonus_per_level_) (optional - default 0)
- Magical damage bonus per level - **MAGIC DMG BONUS** (_magical_damage_bonus_per_level_) (optional - default 0)
- Cooldown multiplier per level - **CD BONUS** (_cooldown_multiplier_per_level_)
- Defense - **DEF** (_defense_)
- Defense bonus per level - **DEF BONUS** (_defense_bonus_per_level_)
- Light radius - **Visual Range** (_light_radius_)
- Light radius per level - **Visual Range BONUS** (_light_radius_bonus_per_level_) (default 1)

```json
{
  "name": "Hero",
  "base_health_points": 100,
  "damage": 10,
  "magical_damage": 4,
  "base_attack_cooldown": 12.3,
  "experience_per_level": 8,
  "health_point_bonus_per_level": 10,
  "damage_bonus_per_level": 2,
  "magical_damage_bonus_per_level": 1,
  "cooldown_multiplier_per_level": 0.2,
  "defense": 4,
  "defense_bonus_per_level": 1,
  "light_radius": 3,
  "light_radius_bonus_per_level": 1
}
```

The `monsters` array is containing one or more paths for monster `json` objects.

Data:

- Name (_name_)
- Health points - **HP** (_base_health_point_)
- Damage - **DMG** (_damage_) (optional - default 0)
- Magical damage - **MAGIC DMG** (_magical_damage_) (optional - default 0)
- Attack cooldown - **CD** (_attack_cooldown_)
- Defense - **DEF** (_defense_)

```json
{
  "name": "Monster",
  "health_points": 100,
  "damage": 10,
  "magical_damage": 9,
  "attack_cooldown": 12.3,
  "defense": 7
}
```

Example command: `./a.out scenario scenarios/scenario1.json`

All predefined scenario for the testing can be foind in the `scenarios` folder.
All predefined hero/monster for testing can be found in the `units` folder.

### Marked Map

A Map with the extra ability to define the hero and monster positions. Monsters are marked with numbers (0-9) and the hero will be in the `H` position.

```
##############
# H #  ####  #
# ####22##  #
# 12# 3##  #
###1# ##  #
#     1   #
#########
```

### Game Modes

- Scenario: Only hero and a list of monsters can be given. Map and positions are hardcoded.
- Prepare: Map can be selected and it can contain the position definitions **[Recommended mode]**.

### How it works:

The program read in the given `scenario` and read in the defined `hero` and `monster`.
The user can navigate through the map using the right keywords, displayed in first round.
The hero start fight with each monster until death, if they step on the same field.
If the hero can kill every monster without death, he will be the winner. If he dies, the game is over.

#### Fight:

Every player has a attack cooldown what is defining the time between two hit.

Every player is gaining **XP** (_experience points_) after each hit. The gained **XP** is equal with the dealed damage.

Every unit is hit the other with his **DMG** and **MAGICAL DMG** amount, but the attacked unit has possiblity to decrease the **DMG** amount with his **DEF** points.

After an X amount of **XP** the character is leveling up. The new level will give him more base **HP**, **DMG**, **MAGICAL DMG** refill the his/her current **HP** to maximum and reduce the **CD**.

#### Leveling:

Using the predefined main function the `Hero` class handles the logic, using the `Json` class for file parsing.

#### END:

The program prints to the output, whether the hero won or not.

#### Json parser

We use a _bit_ complex regex matcher to find all key/value pairs. It is looping until it finds new pairs and returns error if more data exists beyond that point. It also parses json arrays with a separate regex matcher, and its values are parsed the same way the normal values (string, int, double).

3 types of parameters can be used with the parse:

- filename
- istream
- string (containing json)

#### Rendering

It supports multiple rendering methods, which can be set for the `Game` classes with `registerRenderer` function.

_Currently_ It writes **HeroTextRenderer** to the console output and **ObserverTextRenderer** to log.txt file.

Supported renderers:

- `HeroTextRenderer`
- `ObserverTextRenderer`
- `HeroSVGRenderer` (_coming soon_)
- `ObserverSVGRenderer` (_coming soon_)

### Output test:

There are predefined players in the `units/` folder and a `expected_results.csv` file. The variations in the `csv` file can be executed automatically using the `./run_all.sh` script. If a test fails (results not equal) the script quits with error code.

### Unit tests

Under the `tests/` folder cpp test file can be found. The tests use the GTest testing framework and cmake for building.

Usage (without `make`):

- `cd tests`
- `cmake .`
- `make`
- `./tests`

### SCA tests

A workflow automatically runs SCA on the repository with two levels using `cppcheck`. These can be run (without `make`) with the `run_code_analysis_primary.sh` and `run_code_analysis_primary.sh`.

- Primary
  - Check for errors and warnings
- Secondary
  - Check for style and preformance issues

### Memory leak check

`run_memory_leak_check.sh` executes `valgrind` to check for memory leaks.

### Code documentation

Doxygen automatically generates the documentation for the master branch and it is deployed on GH Pages.

> Url of the Doxygen code documentation: [Go to documentation](https://teaching-projects.github.io/SZE-MOSZE-2020-plusplusplus/).

#### Manual Generation

- Install doxygen and graphviz pacakages
- Run the next command: `doxygen doxygenconf`
- Use the generated documents from the `/docs`
