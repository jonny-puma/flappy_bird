#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "fp.h"
#include "highscore.h"

// hack to convert macros to strings
#define STR_(X) #X
#define STR(X) STR_(X)


// TODO: put these guys into settings?
int row;
int col;

int main() {
  iniths();
  initcurses();
  printwelcome();

  gamestate gs;
  settings set;
  int choice = 1;
  while (choice) {
    // setup game
    initgame(&gs, &set);

    gameloop(&gs, &set);
    choice = gameover(&gs);
  }

  closecurses();
  return 0;
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

void gameloop(gamestate *gs, settings *set) {
  // start halfdelay mode
  halfdelay(set->timeout);
  int input;
  while (true) {
    printgame(gs, set);
    if (!isalive(gs)) {
      break;
    }
    input = getch();
    physics(gs, set, input);
    updategs(gs);
  }
}

void initgame(gamestate *gs, settings *set) {
  // init gamestate
  gs->bird_y = row/2;
  gs->bird_x = col/4;
  gs->velocity = 0;
  gs->score = 0;

  obstacle *ob = malloc(sizeof(obstacle));
  ob->x = col;
  ob->y = rand() % row;
  ob->speed = 1;
  ob->size = 5;

  gs->ob = ob;

  // init settings
  set->power = 10;
  set->timeout = 1;
  set->timestep = 0.2;
  set->sp = &bird;
}

void physics(gamestate *gs, settings *set, int input) {
  // Lift from flapping
  if (input != ERR) {
    gs->velocity -= set->power;
  }

  // gravity force
  gs->velocity += 10*set->timestep;

  // integrate to bird_y
  gs->bird_y += gs->velocity*set->timestep;

  // stop at floor
  if (gs->bird_y >= row-1) {
    gs->bird_y = row-1;
    if (gs->velocity > 0) {
        gs->velocity = 0;
    }
  }

  // move obstacle
  obstacle *ob = gs->ob;
  ob->x -= ob->speed;
  if (ob->x <= 0) {
    ob->x = col;
    ob->y = rand() % row;
    ob->speed++;
  }
}

void printgame(gamestate *gs, settings *set) {
  erase();
  mvprintw(row-1, 0, "Score: %i", gs->score);
  printsprite(set->sp, gs->bird_y, gs->bird_x);
  printobstacle(*gs->ob);
  refresh();
}

void updategs(gamestate *gs) {
  gs->score++;
}

void printwelcome() {
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

/*
 * TODO: Move printing into separate function.
 */
int gameover(gamestate *gs) {
  char prompt[] = "Game over!";
  int len = sizeof(prompt)/sizeof(char);
  attron(A_BOLD);
  mvprintw(row/2-9, col/2 - len/2, prompt);
  attroff(A_BOLD);

  prinths();

  // check if the score is a high score
  if (gs->score >= highscores[NSCORES-1].score) {
    char name[NAMELEN+1];
    mvprintw(row/2+NSCORES-3, col/2-14, "Enter your name: "); 
    refresh();
    echo();
    curs_set(1);
    getstr(name);
    noecho();
    curs_set(0);
    sanitize(name);
    addhsentry(name, gs->score); 
    prinths();
    refresh();
  }

  char prompt2[] = "Press q to quit or r to play again";
  int len2 = sizeof(prompt2)/sizeof(char);
  mvprintw(row/2+NSCORES-3, col/2 - len2/2, prompt2);

  // parse options
  int ch = 69;
  while (true) {
    ch = getch();
    switch ((char)ch) {
      case 'q':
        return 0;
      case 'r':
        return 1;
    }
  }
}

void prinths() {
  int x = col/2;
  int y = row/2 - 7;
  attron(A_BOLD);
  mvprintw(y++, x-6, "High scores:");
  attroff(A_BOLD);
  mvprintw(y++, x-9, "+----------------+");
  for (int i=0; i<NSCORES; i++) {
    mvprintw(y+i, x-9,
             "|%" STR(-NAMELEN) "s %5i|", highscores[i].name, highscores[i].score);
  }
  mvprintw(y+NSCORES, x-9, "+----------------+");
}

void printobstacle(obstacle ob) {
  int start = ob.y - ob.size;
  int stop = ob.y + ob.size;
  for (int i=0; i<start; i++) {
    mvprintw(i, ob.x, "#");
  }
  for (int i=stop; i<row; i++) {
    mvprintw(i, ob.x, "#");
  }
}

/*
 * TODO: When speed is higher than 1 the obstacle
 *       may jump over the bird. Logic nedds refinement.
 */
bool isalive(gamestate *gs) {
  obstacle *ob = gs->ob;
  if (ob->x == gs->bird_x) {
    int start = ob->y - ob->size;
    int stop = ob->y + ob->size;
    return start < gs->bird_y && gs->bird_y < stop;
  } else {
    return true;
  }
}

/*
 * Remove white space from names
 */
void sanitize(char string[NAMELEN+1]) {
  if (string[0] == '\0') {
    memcpy(string, "Anonymous", NAMELEN);
  }
  for (int i=0; i<NAMELEN; i++) {
    if (string[i] == ' ') {
      string[i] = '_';
    }
  }
}
