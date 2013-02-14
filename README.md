Alchemy
=======

Alchemy is not a real card game but a dynamic card game framework. One of it's goals is to supply a platform for the developer to build their own card game without thinking about non-game-logic development(such as network,mutiple player...)

Currently it is still very small and simple.

## Build
* Build Tool:CMake
* You need install CMake tool to build the Alchemy

```
$ mkdir build

$ cd build

$ cmake ..

$ make
```

## Constructure
Alchemy think that there will be two kinds of developer:
* Game Rule developer
* Card Function developer

At most time, the game rule developer will be same with the card function developer. However,at some time, they will be different. Thinking about write an card game with thousands of cards.
