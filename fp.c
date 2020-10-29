#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "fp.h"


// TODO: put these guys into settings?
int row;
int col;

int main() {
  initcurses();
  printwelcome();
  gameloop();
  closecurses();

  return 1;
}

/*
 * Initialize curses.
 * cbreak: read every character insted of buffering until newline
 * noecho: don't echo character input
 * keypad: read function keys and keypad
 */
void initcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, row, col);
  curs_set(0);
}

void closecurses() {
  endwin();
}

void gameloop() {
  // setup game
  gamestate gs;
  settings set;
  initgs(&gs, &set);

  // start halfdelay mode
  halfdelay(set.timeout);

  int input;
  while (true) {
    printgame(gs, set);
    input = getch();
    physics(&gs, set, input);
    updategs(&gs);
  }
}

void initgs(gamestate *gs, settings *set) {
  // init gamestate
  gs->position = row/2;
  gs->velocity = 0;
  gs->score = 0;

  // init settings
  set->power = 10;
  set->timeout = 1;
  set->timestep = 0.2;
  set->sp = &bird;
}

void physics(gamestate *gs, settings set, int input) {
  // Lift from flapping else gravity
  if (input != ERR) {
    gs->velocity -= set.power;
  }

  gs->velocity += 10*set.timestep;
  

  // apply physics
  gs->position += gs->velocity*set.timestep;

  // stop at floor
  if (gs->position >= row-1) {
    gs->position = row-1;
    if (gs->velocity > 0) {
        gs->velocity = 0;
    }
  }
}

void printgame(gamestate gs, settings set) {
  erase();
  mvprintw(row-1, 0, "Score: %i", gs.score);
  printsprite(set.sp, gs.position, col/2);
  refresh();
}

void updategs(gamestate *gs) {
  gs->score++;
}

void printwelcome() {
  // int p_rows = sizeof(welcome_prompt)/sizeof(*welcome_prompt[0])/sizeof(char);
  // int p_cols = sizeof(*welcome_prompt[0])/sizeof(char);
  int p_rows = 8;
  int p_cols = 55;
  int x = col/2 - p_cols/2;
  int y = row/2 - p_rows/2;
  for (int i=0; i<p_rows; i++) {
    mvprintw(y+i, x, welcome_prompt[i]);
  }
  char prompt[] = "Press any button to start!";
  int p_length = sizeof(prompt)/sizeof(char);
  mvprintw(y+p_rows+1, col/2-p_length/2, prompt);
  refresh();
  getch();
  }
