Controls:
(To use controller input the controller needs to be connected before starting the build, important when using the co op mode)
StartScreen:
W  =  go up with the arrow
S = go down with the arrow
enter = enter the game in whichever mode u chose.

Game:
Keyboard:
W A S D = movement
F = throw air pump & to pump
Controller:
D-pad = Movement
A Button = throw air pump & to pump

Level loader
The level loader is a class with its main purpose to create the scene by reading the level from file containing numbers 
and save/read the highscore from a seperate file.
the level file numbers:
from 1 - 5 for single mode ( 0 = empty, 1 = tile, 2 = player, 3 = pooka, 4 = fyger, 5 = rock)
or 1 - 6 for co op mode ( same as single except 3 gets turned into player two and the rest gets incremented by one)
after reading the same function will also create the game objects.

Game state
the game state is as the name implies, checking which state the game is currently in and change to different states 
depending on the player input or the player condition.


Enemy manager
I implemented a singleton enemy manager, the reason i made it singleton is because i need to know how many enemies are left
to change scene.
Since there are two enemies, pooka and fyger, i decided to make a base class called enemy and make them a child of the base class
this way when i make the enemymanager i dont need to handle 2 vectors for each enemy.
