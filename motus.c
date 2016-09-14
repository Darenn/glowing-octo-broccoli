#include <stdlib.h>
#include <ctype.h>


#include "motus.h"
#include "chaine.h"

struct motus_motus {
  unsigned int t_mot; //taille des mots du jeu
  unsigned int nb_essai; // le nombre d'essais autorisés
  // t_mot et nb_essai permettent de définir les conditions du jeu
  chaine mot; // mot à trouver
  chaine propositions; // mots proposés
  chaine resultats; // le code pour l'affichage
};


motus motus_creer(unsigned int _t_mot, unsigned int _nb_essai, char* mot)
{
  motus m = (motus) malloc(sizeof(struct motus_motus)); // Allocation memoire
  // INIT
  m->t_mot = _t_mot;
  m->nb_essai = _nb_essai;
  m->mot = chaine_creer_char(mot);
  m->propositions = chaine_creer_vide();
  m->resultats = chaine_creer_vide();

  return m;
}

void motus_detruire(motus* m)
{
  // Destruction des trois chaîne
  chaine_detruire(&(*m)->mot);
  chaine_detruire(&(*m)->propositions);
  chaine_detruire(&(*m)->resultats);
  // Destruction du jeu
  free(*m);
  m = NULL;
}


void motus_afficher(motus m, unsigned int numero, bool gagne)
{
  clrscr();
  unsigned int taille = chaine_extraire_taille(m->propositions);
  unsigned int nb_resultats = taille / (m->t_mot);
  for (unsigned int i=0; i<nb_resultats; i++) {
    for (unsigned int j=0;  j<m->t_mot; j++) {
      char c1 = chaine_extraire_char_i((m->propositions),i*m->t_mot+j);
      char c2 = chaine_extraire_char_i((m->resultats),i*m->t_mot+j);
      switch(c2) {
        case CHAR_BIEN_PLACE:
        couleur("37");
        fprintf(stdout,"%c",c1);
        couleur("0");
        break;
        case CHAR_MAL_PLACE:
        couleur("34");
        fprintf(stdout,"%c",c1);
        couleur("0");
        break;
        case CHAR_NON_PRESENT:
        couleur("31");
        fprintf(stdout,"%c",c1);
        couleur("0");
      }
    }
    fprintf(stdout,"\n");
  }
  for (unsigned int i=nb_resultats; i<m->nb_essai; i++) {
    for (unsigned int j=0;  j<m->t_mot; j++)
    fprintf(stdout,"%c",CHAR_EN_ATTENTE);
    fprintf(stdout,"\n");
  }
  if ((numero-1 != m->nb_essai) && (!gagne))
  fprintf(stdout,"Proposition numéro %d : ",numero);
}

chaine chaine_code(chaine ch, chaine mot, bool* gagne)
{
  // Unification des characteres
  chaine_en_majuscules(ch);
  chaine_en_majuscules(mot);

  // Variables
  int j;  // Indice du charactere si trouvé
  char c; // Charactere courant
  chaine code = chaine_copier(ch); // Creation de la chaine code

  // On parcourt toute la chaine proposé
  for (unsigned int i = 0; i < chaine_extraire_taille(ch); i++) {
    c = chaine_extraire_char_i(ch, i); // Recuperation du charactere courant

    if (chaine_appartenir(c, mot, &j)) { // Si le charactere appartient au mot
      if ((unsigned)j == i) { // Si il est bien placé
        chaine_modifier_char_i(code, i, CHAR_BIEN_PLACE);
      } else { // Sinon
        chaine_modifier_char_i(code, i, CHAR_MAL_PLACE);
      }
    } else { // Si le charactere n'appartient pas au mot
      chaine_modifier_char_i(code, i, CHAR_NON_PRESENT);
    }
  }

  *gagne = chaine_est_egal(ch, mot); // Test de victoire
  return code; // Retour du code
}

void motus_jeu(motus m)
{
  bool gagne = false;
  int numero = 0;
  chaine pro;

  while (((unsigned)++numero <= m->nb_essai) && !gagne) {
    motus_afficher(m, numero, gagne);
    pro = chaine_lire(stdin, m->t_mot);
    chaine_concatener(m->propositions, pro);
    chaine_concatener(m->resultats, chaine_code(pro, m->mot, &gagne));
  }
  motus_afficher(m, numero, gagne);
}
