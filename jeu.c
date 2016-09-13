#include "chaine.h"
#include "motus.h"

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
int main (int argc, char** argv) {

  assert(argc==4);
  int taille = atoi(argv[1]);
  int nb_essai = atoi(argv[2]);
  char* fich_in = argv[3];

  motus m;
  char ref[taille];
  srand(time(NULL));
  FILE* f_in = fopen(fich_in,"r");
  int ligne = rand()%18;
  printf("ligne=%d\n",ligne);
  fseek(f_in,ligne*7,SEEK_SET);
  fgets(ref,taille+2,f_in);
  ref[strlen(ref)-1]='\0';
  fclose(f_in);

  m = motus_creer(taille,nb_essai,ref);
  motus_jeu(m);

  motus_detruire(m);
  

  return 0 ;
}
