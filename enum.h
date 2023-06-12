#ifndef __ENUM_H__
#define __ENUM_H__

// define the eight directions
enum class DirectionType {
    NO, SO, WE, EA, NW, NE, SW, SE
};

// define the cell types 
enum class CellType {
    VAMPIRE,
    WEREWOLF,
    TROLL,
    MERCHANT,
    GOBLIN,
    DRAGON,
    PHOENIX,
    PC,
    DOOR,
    PASSWAY,
    STAIRS,
    POTION,
    VALID,
    VWALL,
    HWALL,
    WHITE,
    COMPASS,
    BARRIERSUIT,
    TREASURE,
};

// define the race types of the PC
enum class RaceType {
    HUMAN,
    DWARF,
    ELVES,
    ORC,
    POTION
};

#endif
