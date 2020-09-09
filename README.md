# RPG Game

## MOSZE - GKNB_INTM006 - 2020. Autumn

### Team: +++ (PlusPlusPlus)

#### Team Members:

- Balogh Máté
- Baranyai Bence
- Karcag Tamás

### How it works

Compiled application should be called with 6 parameters, like: `./a.out Maple 150 10 Sally 45 3`.

In the `Loop` constructor, the players are read from the parameter list. `Play` is the main game handle, which is recursively called until the game ends (a player has 0 HP).

`Player` attacks other `Player` with a reference given to the other class, Attack returns whether the opponent lost or not.
