# Shmup
Shoot 'em up game written in C++ with SFML library. 
Game text is in **Polish** only.

## Rules
Player has to shoot down hordes of monsters, before they travel to the bottom of the screen, while simultaneously doding dangerous attacks in a bullet-hell style scenario. 
Enemies can be fought with two distinct modes of attacking, a precise gun and a chaotic shotgun, which complement each other and reward good reflexes and smart decision making. 
There is also "reinforcement" mechanic, where player can reload their gun and temporarily enter a parry state, in which each damage taken instead results in healing - 
player has to use it smartly to refill their resources and be wary of its cooldown.
After each wave a reward will spawn, oferring 3 distinct upgrades to choose from for boost in later gameplay.


## Team
- [panierka](https://github.com/panierka) - gameplay design and programming, game logic, graphics rendering, collision handling, game state management, art, project organization, sfx
- [jdylik](https://github.com/jdylik) - leaderboard, settings, music, sfx

## Features
- Fun and challenging gameplay
- Two modes of attacking, 
- 6 waves
- 9 enemies with great variety between them
- Challenging boss with range of attacks
- 8 upgrades
- Score system and leaderboard
- Unique graphics
- Full SFX
- Original music

## Controls
| Keybind | Action |
| :---: | :---: |
| `A` | Move left |
| `D` | Move right |
| `Space` | Dodge & Reload |
| `K` | Basic Attack |
| `L` | Special Attack |
| `Enter` | Choose Upgrade | 
| `Esc` | Pause |

## Requirements

- Project was made using SFML-2.5.1 (x64)
- It uses sfml's graphics, window, audio and system .lib files, so you need to put those in the project space (and their debug counterparts, for Debug builds)
- Put `<your path to sfml>/include` in General > Aditional Include Directiories
- Put `<your path to sfml>/lib` in Linker > General > Aditional Library Directiories

## Attributions
- Used font comes from free font pack - "divide by zero" http://fonts.tom7.com/
- SFX have been taken from https://freesound.org/. They are on Creative Commons 0 licences.
