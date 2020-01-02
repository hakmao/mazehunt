#ifndef MAZEHUNT_DEFS_H
#define MAZEHUNT_DEFS_H
#define VERSION "0.0.1"

// grid representation
const int SCREEN_LINES = 24;
const int SCREEN_COLS = 80;

// grid size
const int GRID_COLS = 19;
const int GRID_ROWS = 10;
//
const int CELL_WIDTH = 3;
const int CELL_HEIGHT = 1;
const int WALL_WIDTH = 1;
const int WALL_HEIGHT = 1;

constexpr const int TEXT_COLS = 
    WALL_WIDTH + (GRID_COLS * (CELL_WIDTH + WALL_WIDTH)); // 81
constexpr const int TEXT_LINES = 
    WALL_HEIGHT + (GRID_ROWS * (CELL_HEIGHT + WALL_HEIGHT)); // 21

// directions
// typedef enum { N, W, S, E } Direction;

// point types
// typedef enum { WALL, EMPTY, PLAYER, FOOD, MONSTER } point_type;

// characters
//#define CH_EMPTY ' '
//#define CH_PLAYER '@'
//#define CH_FOOD '*'
//#define CH_ZOMBIE '8'

// colours
#define COL_WALL COLOR_RED
#define COL_EMPTY COLOR_WHITE
#define COL_DEFAULT COLOR_WHITE
#define COL_PLAYER COLOR_BLUE
#define COL_FOOD COLOR_YELLOW
#define COL_ZOMBIE COLOR_MAGENTA
#define COL_STATUS COLOR_GREEN

// alignments
// #define ALIGN_RIGHT 0
// #define ALIGN_LEFT 1

// return codes
//#define R_QUIT 0

#endif
