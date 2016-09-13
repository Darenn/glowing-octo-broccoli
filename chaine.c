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
}

chaine chaine_creer_char(char* c)
{
}

void chaine_detruire(chaine* ch)
{
}

void chaine_afficher(FILE* f, chaine ch)
{
}

unsigned int chaine_extraire_taille(chaine ch)
{
}


bool chaine_est_vide(chaine ch)
{
}

bool chaine_est_egal(chaine ch1, chaine ch2)
{
}

void chaine_concatener(chaine ch1, chaine ch2)
{
}

char chaine_extraire_char_i(chaine ch, const unsigned int i)
{
}

void chaine_modifier_char_i(chaine ch, const unsigned int i, const char c)
{
}

chaine chaine_copier(chaine ch1)
{
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





