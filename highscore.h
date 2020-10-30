#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#define NAMELEN 10
#define NSCORES 10

typedef struct {
	char name[NAMELEN+1];
	int score;
} hsentry;

hsentry *highscores;

/*
 * Allocate and load the highscore list from file
 */
void iniths();

/*
 * Add high score entry and save to file
 */
void addhsentry(char *name, int score);
#endif
