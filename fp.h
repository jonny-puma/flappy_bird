#include "sprites.h"
#include "highscore.h"

typedef struct {
	float timestep;
	float timeout;
	int power;
	sprite *sp;
} settings;

typedef struct {
  int x;
  int y;
  int size;
  int speed;
} obstacle;

typedef struct {
	int bird_y;
  int bird_x;
	int velocity;
	int score;
  obstacle *ob;
} gamestate;


/* 
 * set up and close ncurses
 */
void initcurses();
void closecurses();

/*
 * Run game
 */
void gameloop(gamestate *gs, settings *set);
bool isalive(gamestate *gs);
int gameover(gamestate *gs);

/*
 * Set up the gamestate end settings
 */
void initgame(gamestate *gs, settings *set);

/*
 * Print game state with curses
 */
void printgame(gamestate *gs, settings *set);
void printobstacle(obstacle ob);
void printwelcome();
void prinths();

/*
 * Replace whitespace with underscore
 */
void sanitize(char string[NAMELEN+1]);

/*
 * Increment game dynamics with one timestep
 */
void physics(gamestate *gs, settings *set, int input);

/*
 * Update gamestate
 * 	- update score
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
	

