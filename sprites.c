#include <ncurses.h>
#include "sprites.h"

s_part birdparts[] = {
	{.dx=0, .dy=0, .c='#'},
	{.dx=-1, .dy=0, .c='#'},
	{.dx=-2, .dy=0, .c='#'},
	{.dx=-2, .dy=0, .c='>'},
	{.dx=1, .dy=0, .c='/'},
	{.dx=0, .dy=-1, .c='('},
	{.dx=1, .dy=-1, .c='@'},
	{.dx=2, .dy=-1, .c=')'},
	{.dx=3, .dy=-1, .c='>'}
};

sprite bird = {
	.name = "bird",
	.length = sizeof(birdparts)/sizeof(s_part),
	.parts = birdparts
};

void printsprite(sprite *sp, int y, int x) {
	int dx;
	int dy;
	char c;
	for (int i=0; i<sp->length; i++) {
		dx = sp->parts[i].dx;
		dy = sp->parts[i].dy;
		c = sp->parts[i].c;
		mvprintw(y+dy, x+dx, "%c", c);
	}
}
