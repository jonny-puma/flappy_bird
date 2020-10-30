#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "highscore.h"

/*
 * TODO: Linked list for high score entry?
 *       Makes insertion easier.
 */

void loadhs() {
  FILE *hsfile = fopen("highscores.txt", "rb");

  // Construct entries if no file found
  if (hsfile == NULL) {
    char *name = malloc((NAMELEN+1)*sizeof(char));
    for (int i=0; i<NAMELEN; i++) {
      name[i] = '~';
    }
    name[NAMELEN] = '\0';
    for (int i=0; i<NSCORES; i++) {
      memcpy(highscores[i].name, name, NAMELEN+1);
      highscores[i].score = 0;
    }
    free(name);
  } else {
    for (int i=0; i<NSCORES; i++) {
      // int buffsize = 128;
      // char buffer[buffsize];
      // fgets(buffer, buffsize, hsfile);
      fscanf(hsfile, "%s %i\n", highscores[i].name, &highscores[i].score);
    }
  }
  fclose(hsfile);
}

void iniths() {
  highscores = malloc(NSCORES*sizeof(hsentry));
  loadhs();
}

void savehs() {
  FILE *hsfile = fopen("highscores.txt", "wb");
  
  for (int i=0; i<NSCORES; i++) {
    fprintf(hsfile, "%s %i\n", highscores[i].name, highscores[i].score);
  }
  fclose(hsfile);
}

void addhsentry(char name[NAMELEN], int score) {
  for (int i=0; i<NSCORES; i++) {
    if (score >= highscores[i].score) {
      int buffsize = (NAMELEN-i-1)*sizeof(hsentry);
      hsentry *buffer = malloc(buffsize);
      memcpy(buffer, &highscores[i], buffsize);
      memcpy(highscores[i].name, name, NAMELEN+1);
      highscores[i].score = score;
      memcpy(&highscores[i+1], buffer, buffsize);
      free(buffer);
      savehs();
      break;
    }
  }
}

