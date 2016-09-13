#include "chaine.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define SIZE 15

int main (void ) {

  FILE* f_in = fopen("test_chaines_in.txt","r");
  FILE* f_out = fopen("test_chaines_out.txt","w");
  char a_lire[SIZE];
  fgets(a_lire,SIZE,f_in);
  a_lire[strlen(a_lire)-1]='\0';
  chaine ch1 = chaine_creer_char(a_lire);
  fprintf(f_out,"ch1=");
  chaine_afficher(f_out,ch1);

  chaine ch2 = chaine_creer_char("etidiante");
  fprintf(f_out,"ch2=");
  chaine_afficher(f_out,ch2);

  chaine_modifier_char_i(ch2,2,'u');
  fprintf(f_out,"ch2 corrigé=");
  chaine_afficher(f_out,ch2);

  chaine ch3 = chaine_copier(ch2);
  fprintf(f_out,"ch3=");
  chaine_afficher(f_out,ch3);

  chaine_en_majuscules(ch3);
  fprintf(f_out,"ch3=");
  chaine_afficher(f_out,ch3);

  chaine_concatener(ch3,ch1);
  fprintf(f_out,"ch3 modifié=");
  chaine_afficher(f_out, ch3);

  chaine ch4 = chaine_creer_vide();
  chaine_concatener(ch4,ch2);
  fprintf(f_out,"ch4=");
  chaine_afficher(f_out, ch4);

  chaine_detruire(&ch1);
  chaine_detruire(&ch2);
  chaine_detruire(&ch3);
  chaine_detruire(&ch4);

  fclose(f_in);
  fclose(f_out);

  return 0 ;
}
