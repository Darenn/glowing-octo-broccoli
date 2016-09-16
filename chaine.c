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
  chaine c = (chaine) malloc(sizeof(struct chaine));
  c->taille = 0;
  c->tab = NULL;
  return c;
}

chaine chaine_creer_char(char* c)
{
  chaine ch = (chaine) malloc(sizeof(struct chaine));
  ch->taille = strlen(c);
  /* Je copie en mémoire la chaine donnée car je ne sais pas quand
  il va la libérer */
  ch->tab = (char*) malloc(sizeof(char) * (ch->taille));
  for (size_t i = 0; i < ch->taille; i++) {
    ch->tab[i] = c[i];
  }
  return ch;
}

void chaine_detruire(chaine* ch)
{
  free((*ch)->tab); // Libére le tableau
  free(*ch); // Libére la struct
  *ch = NULL; // On met le pointeur de l'utilisateur à NULL
}

void chaine_afficher(FILE* f, chaine ch)
{
  for (size_t i = 0; i < ch->taille; i++) {
    fprintf(f, "%c", ch->tab[i]);
  }
  fprintf(f, "\n");
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
  if (ch1->taille != ch2->taille) {
    return false;
  } else {
    for (size_t i = 0; i < ch1->taille; i++) {
      if(ch1->tab[i] != ch2->tab[i]) {
        return false;
      }
    }
  }
  return true;
}

void chaine_concatener(chaine ch1, chaine ch2)
{
  // Si la ch2 est vide on ne concatène pas
  if (chaine_est_vide(ch2)) { return; }
  // J'alloue un nouveauTab avec assez de place pour les deux chaines
  char* nouveauTab = (char*) malloc(sizeof(char) * (ch1->taille + ch2->taille));
  // Si ch1 n'est pas vide, je copie son contenu dans mon nouveauTab
  if (!chaine_est_vide(ch1)) {
    for (size_t i = 0; i < ch1->taille; i++) {
      nouveauTab[i] = ch1->tab[i];
    }
  }
  // Je rajoute les caractères de ch2 au bout de mon nouveaTab
  if (!chaine_est_vide(ch2)) {
    for (size_t i = 0; i < ch2->taille; i++) {
      nouveauTab[ch1->taille + i] = ch2->tab[i];
    }
  }
  // Je libère l'ancien tab de ch1, et je fais pointer tab vers nouveauTab
  free(ch1->tab);
  ch1->taille += ch2->taille;
  ch1->tab = nouveauTab;
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
  chaine c = malloc(sizeof(struct chaine));
  c->taille = ch1->taille;
  c->tab= (char*) malloc(sizeof(char) * ch1->taille);
    for (size_t i = 0; i < ch1->taille; i++) {
      c->tab[i] = ch1->tab[i];
    }
  return c;
}

void chaine_en_minuscules(chaine ch)
{
  for (size_t i = 0; i < ch->taille; i++) {
    ch->tab[i] = tolower(ch->tab[i]);
  }
}

void chaine_en_majuscules(chaine ch)
{
  for (size_t i = 0; i < ch->taille; i++) {
    ch->tab[i] = toupper(ch->tab[i]);
  }
}

bool chaine_appartenir(const char c, chaine ch, int* i)
{
  for (size_t j = 0; j < ch->taille; j++) {
    if (ch->tab[j] == c) {
      if (i != NULL) {
        *i = j;
      }
      return true;
    }
  }
  return false;
}

chaine chaine_lire(FILE* f, unsigned int taille)
{
  chaine ch = (chaine) malloc(sizeof(struct chaine));
  ch->taille = taille;
  ch->tab = (char*) malloc(sizeof(char) * taille);
  fread(ch->tab, sizeof(char), taille, f);
  return ch;
}
