#ifndef MOTUS_H
#define MOTUS_H

#include "chaine.h"

#define CHAR_BIEN_PLACE '='
#define CHAR_MAL_PLACE '!'
#define CHAR_NON_PRESENT '.'
#define CHAR_EN_ATTENTE '*'

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm", param)

typedef struct motus_struct *motus;

// Pour créer le jeu
motus motus_creer(unsigned int _t_mot, unsigned int _nb_essai, char *mot);
// Pour détruire correctement les allocations
void motus_detruire(motus *m);
// fonction déjà écrite pour afficher le jeu
void motus_afficher(motus m, unsigned int numero, bool gagne);
// à écrire : renvoie la chaine correspondant au codage proposé lorsqu'on
// compare une proposition ch avec le mot recherché mot
// cf exemples dans l'énoncé.
chaine chaine_code(chaine ch, chaine mot, bool *gagne);
// Déroulement du jeu
void motus_jeu(motus m);

#endif
