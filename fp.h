#include "sprites.h"

typedef struct {
	int position;
	int velocity;
	int score;
} gamestate;

typedef struct {
	char *name;
	int score;
} hsentry;

typedef struct {
	float timestep;
	float timeout;
	int power;
	sprite *sp;
} settings;


/*
 * High score list
 * TODO: save and retrieve from file
 */
hsentry *highscores;

/* 
 * set up and close ncurses
 */
void initcurses();
void closecurses();

/*
 * Run game
 */
void gameloop();

/*
 * Set up the gamestate end settings
 */
void initgs(gamestate *gs, settings *set);

/*
 * Print game state with curses
 */
void printgame(gamestate gs, settings set);

/*
 * Increment game dynamics with one timestep
 */
void physics(gamestate *gs, settings set, int input);

/*
 * Update gamestate
 * 	- update score
 * 	- TODO: check if dead
 */
void updategs(gamestate *gs);

const char *welcome_prompt[] = {"  ______ _                           ____  _         _ ",
																" |  ____| |                         |  _ \\(_)       | |",
															  " | |__  | | __ _ _ __  _ __  _   _  | |_) |_ _ __ __| |",
																" |  __| | |/ _` | '_ \\| '_ \\| | | | |  _ <| | '__/ _` |",
	 													    " | |    | | (_| | |_) | |_) | |_| | | |_) | | | | (_| |",
	 													    " |_|    |_|\\__,_| .__/| .__/ \\__, | |____/|_|_|  \\__,_|",
	 													    "                | |   | |     __/ |                    ",
	 													    "                |_|   |_|    |___/                     \n"};
	
	void printwelcome();
