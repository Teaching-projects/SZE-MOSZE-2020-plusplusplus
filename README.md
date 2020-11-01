# RPG Game

## MOSZE - GKNB_INTM006 - 2020. Autumn

### Team: +++ (PlusPlusPlus)

![Test Workflow](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Test%20Workflow/badge.svg)
![Unit Tests](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Unit%20Tests/badge.svg)
![Documentation](https://github.com/Teaching-projects/SZE-MOSZE-2020-plusplusplus/workflows/Documentation%20workflow/badge.svg)
[![Documentation](https://img.shields.io/badge/Documentation-Here!-blue)](https://teaching-projects.github.io/SZE-MOSZE-2020-plusplusplus/pages.html)

#### Team Members:

- Balogh Máté
- Baranyai Bence
- Karcag Tamás

### Make commands

`Make` is useful to have nice and easy commands to run applications. This is the list of commands we have:

- `make`:

  - `build`: Builds the application (./a.out) (_default target_)
  - `run`: Executes the built binary (You should add the file parameters as `UNIT1` and `UNIT2` named arguments)
  - `test`: Run all tests
  - `unittest`: Run unit tests
  - `documentation`: Generate the documentation
  - `memory_leak_check`: Run memory leak test
  - `static_code_analysis`: Run primary and secondary static code analysis
  - `clean`: Clean built files

### Executing application

Compiled application should be called with 2 parameters, each pointing to a json file with a player defined (name, hp, dmg, attackcooldown).

```json
{
  "name": "Player",
  "hp": 100,
  "dmg": 10,
  "attackcooldown": 12.3
}
```

Example command: `./a.out units/unit1.json units/unit2.json`

3 predefined players for testing can be found in the `units` folder.

### How it works

Using the predefined main function the `Hero` class handles the logic, using the `Json` class for file parsing.

#### Json parser

We use a _bit_ complex regex matcher to find all key/value pairs. It is looping until it finds new pairs and returns error if more data exists beyond that point.

3 types of parameters can be used with the parse:

- filename
- istream
- string (containing json)

### Output test

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

> Url of the Doxygen code documentation: [Go to documentation](https://teaching-projects.github.io/SZE-MOSZE-2020-plusplusplus/pages.html).

#### Manual Generation

- Install doxygen and graphviz pacakages
- Run the next command: `doxygen doxygenconf`
- Use the generated documents from the `/docs`
