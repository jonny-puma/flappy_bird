/*
 * Sprites for the game
 * TODO: Animated sprites?
 */
#ifndef SPRITES_H
#define SPRITES_H

typedef struct {
	int dx;
	int dy;
	char c;
} s_part;

typedef struct {
	char name[10];
	int length;
	s_part *parts;
} sprite;

sprite bird;

void printsprite(sprite *sp, int y, int x);

#endif
