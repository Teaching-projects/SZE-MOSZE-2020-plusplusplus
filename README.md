# RPG Game

## MOSZE - GKNB_INTM006 - 2020. Autumn

### Team: +++ (PlusPlusPlus)

#### Team Members:

- Balogh Máté
- Baranyai Bence
- Karcag Tamás

### Executing application

Compiled application should be called with 2 parameters, each pointing to a json file with a player defined (name, hp, dmg).

```json
{
  "name": "Player",
  "hp": 100,
  "dmg": 10
}
```

Example command: `./a.out units/unit1.json units/unit2.json`

3 predefined players for testing can be found in the `units` folder.

### How it works

In the `Loop` constructor, the players are read from the parameter list. `Play` is the main game handle, which is recursively called until the game ends (a player has 0 HP).

`Player` attacks other `Player` with a reference given to the other class, Attack returns whether the opponent lost or not.

Only the final state of the game is printed, showing who won.

### Output test

There are predefined players in the `units/` folder and a `expected_results.csv` file. The variations in the `csv` file can be executed automatically using the `./run_all.sh` script. If a test fails (results not equal) the script quits with error code.
