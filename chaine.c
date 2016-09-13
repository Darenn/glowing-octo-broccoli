#include "chaine.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct chaine {
  unsigned int taille;
  char* tab;
};

chaine chaine_creer_vide()
{
  chaine c = malloc(sizeof(chaine));
  c->taille = 0;
  c->tab = NULL;
  return c;
}

chaine chaine_creer_char(char* c)
{
  chaine ch = malloc(sizeof(chaine));
  ch->taille = strlen(c);
  /* Je copie en mémoire la chaine donnée car je ne sais pas quand
  il va la libérer */
  char* tab = malloc (sizeof(char) * (ch->taille + 1)); // +1 pour le caractère NULL
  strcpy(tab, c); // Copie aussi le caractère NULL
  ch->tab = tab;
  return ch;
}

void chaine_detruire(chaine* ch)
{
  // TODO
  //free(ch->tab); // Libére le tableau ? Je ne comprends pas pourquoi ça ne fonctionne pas
  free(ch); // Libére la struct
}

void chaine_afficher(FILE* f, chaine ch)
{
  char* c = ch->tab;
  while (*c != 0) {
    printf("%c", *c);
    c++;
  }
  printf("\n");
}

unsigned int chaine_extraire_taille(chaine ch)
{
  return ch->taille;
}


bool chaine_est_vide(chaine ch)
{
  return ch->taille == 0 && ch->tab == NULL;
}

bool chaine_est_egal(chaine ch1, chaine ch2)
{
  return (!strcmp(ch1->tab, ch2->tab));
}

void chaine_concatener(chaine ch1, chaine ch2)
{
  strcat(ch1->tab, ch2->tab);
}

char chaine_extraire_char_i(chaine ch, const unsigned int i)
{
  return ch->tab[i];
}

void chaine_modifier_char_i(chaine ch, const unsigned int i, const char c)
{
  ch->tab[i] = c;
}

chaine chaine_copier(chaine ch1)
{
  chaine c = malloc(sizeof(chaine));
  c->taille = ch1->taille;
  char* tab = malloc(sizeof(char) * (c->taille + 1)); // +1 pour le caractère NULL
  strcpy(tab, ch1->tab);
  return c;
}

void chaine_en_minuscules(chaine ch)
{
}

void chaine_en_majuscules(chaine ch)
{
}

bool chaine_appartenir(const char c, chaine ch, int* i)
{
}

chaine chaine_lire(FILE* f, unsigned int taille)
{
}
