#include <stdlib.h>
#include <ctype.h>


#include "motus.h"
#include "chaine.h"

struct motus_struct {
  unsigned int t_mot; //taille des mots du jeu
  unsigned int nb_essai; // le nombre d'essais autorisés
  // t_mot et nb_essai permettent de définir les conditions du jeu
  chaine mot; // mot à trouver
  chaine propositions; // mots proposés
  chaine resultats; // le code pour l'affichage
};


motus motus_creer(unsigned int _t_mot, unsigned int _nb_essai, char* mot)
{
  motus m = (motus) malloc(sizeof(struct motus_struct)); // Allocation mémoire
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
  // Destruction des trois chaines
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
  // Unification des caractères
  chaine_en_majuscules(ch);
  chaine_en_majuscules(mot);

  // Variables
  char c;                          // Caractère courant
  chaine code = chaine_copier(ch); // Creation de la chaine code

  // On parcourt toute la chaine proposé
  for (unsigned int i = 0; i < chaine_extraire_taille(ch); i++) {
    c = chaine_extraire_char_i(ch, i); // Recuperation du caractère courant

    if (chaine_appartenir(c, mot, NULL)) { // Si le caractère appartient au mot
      if (chaine_extraire_char_i(mot, i) == c) { // Si il est bien placé
        chaine_modifier_char_i(code, i, CHAR_BIEN_PLACE);
      } else { // Sinon
        chaine_modifier_char_i(code, i, CHAR_MAL_PLACE);
      }
    } else { // Si le caractère n'appartient pas au mot
      chaine_modifier_char_i(code, i, CHAR_NON_PRESENT);
    }
  }

  *gagne = chaine_est_egal(ch, mot); // Test de victoire
  return code; // Retour du code
}

void motus_jeu(motus m)
{
  // Variables
  bool gagne = false;
  unsigned int numero = 0; // Essai courant
  chaine pro;              // Proposition du joueur
  chaine code;             // Code de test

  while ((++numero <= m->nb_essai) && !gagne) { // Tant qu'il reste des essai et que le joueur n'a pas gagné
    motus_afficher(m, numero, gagne);           // On affiche le jeu

    pro = chaine_lire(stdin, m->t_mot);         // Lecture de la proposition
    while (fgetc(stdin) != '\n');               // Suppression des caractères supplémentaires (ex: '/n')
    code = chaine_code(pro, m->mot, &gagne);    // Création du code
    // Ajout de la proposition et du code
    chaine_concatener(m->propositions, pro);
    chaine_concatener(m->resultats, code);
    // Destruction
    chaine_detruire(&pro);
    chaine_detruire(&code);
  }
  motus_afficher(m, numero, gagne);
}
