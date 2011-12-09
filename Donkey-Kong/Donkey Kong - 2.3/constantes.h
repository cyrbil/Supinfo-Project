/**
 * \file constantes.h
 * \brief Définition de constantes et énumérations afin de faciliter la lecture et l'utilisation du code source, ainsi que regrouper certains paramètres clés.
 * \author Steinhausser Maxime, Jean Burellier, Fleury Dorian.
 */

#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/////////////////////////////////PARAMETRES/////////////////////////////////
#define VITESSE_MARIO_BASE 1 //0=>Vitesse Minimum (initialisée à 1 + VITESSE_MARIO_BASE dans le jeu)
#define VITESSE_TONNEAU 0 //initialisé à 1 + VITESSE_TONNEAU dans le jeu
#define VITESSE_CARAPACE 0 //initialisé à 1 + VITESSE_CARAPACE dans le jeu
#define PENTE 40 //Plus la pente est forte, plus la valeur est faible
#define GRAVITE 45 //Définie la hauteur de saut de Mario
#define PORTEE_SAUT 1 //Définie la portée de saut de Mario
#define FREQUENCE_ATTAQUE 8 //Def.la proba qu'un projectile soit lancé par DK (Minimum dépent du nombre de projectiles codés, 6 actuellement, 3 carapaces et 3 tonneaux à la fois)
#define FREQUENCE_HELP 3 //Définie la probabilité que Peach crie Help.
#define PROBAS_CHAMPI_UP 2//Definie la probas qu'un champi UP apparaisse à coté de Donkey Kong lors de la génération du niveau. Plus le nombre est grand, plus faible est la chance. Actuel = 1 chance sur 3.
#define PROBAS_POW 2 //Définie de la même manière que précédement l'apparition du Pow
#define DUREE_POW 600 //Définie la durée de l'effet du Pow (100= environ 1 seconde)
#define PROBAS_BLOC_METAL 2//Définie de la même manière que précédement l'apparition du Bloc Metal
///////////////////////////////FIN PARAMETRES///////////////////////////////

    enum {STATIC, SAUT_G, SAUT_D, SAUT_S, G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, CLIMBING};  //Posture Mario
    enum {ETAGE_UN, ECHELLE_UNE, ETAGE_DEUX, ECHELLE_DEUX, ECHELLE_TROIS, ETAGE_TROIS, ECHELLE_QUATRE, ECHELLE_CINQ, ETAGE_QUATRE, ECHELLE_SIX, ETAGE_CINQ};//Gestion étages et echelles
    enum {DK_NORMAL, DK_CARAPACE, DK_TONNEAU, DK_POW}; //Posture Donkey Kong
    enum {TYPE_1, TYPE_2, TYPE_3}; //Type de pente
    enum {ZERO_VIE, UNE_VIE, DEUX_VIES, TROIS_VIES}; //Nombre de vie à afficher
    enum {PEACH1, PEACH_HELP}; //Posture Peach


////////////////////////////PARAMETRES ECHELLES/////////////////////////////
//La définition de la taille des echelles définie la zone d'interaction du personnage avec celles-ci.
//TAILLE ECHELLE 1
#define Y_MIN_SCALE_ONE 547
#define Y_MAX_SCALE_ONE 440
#define X_MIN_SCALE_ONE 720
#define X_MAX_SCALE_ONE 760
#define X_MARIO_ONE 740
//TAILLE ECHELLE 2
#define Y_MIN_SCALE_TWO 433
#define Y_MAX_SCALE_TWO 313
#define X_MIN_SCALE_TWO 415
#define X_MAX_SCALE_TWO 455//prec+40
#define X_MARIO_TWO 436//prec-20
//TAILLE ECHELLE 3
#define Y_MIN_SCALE_THREE 425
#define Y_MAX_SCALE_THREE 316
#define X_MIN_SCALE_THREE 100
#define X_MAX_SCALE_THREE 140//prec+40
#define X_MARIO_THREE 120//prec-20
//TAILLE ECHELLE 4
#define Y_MIN_SCALE_FOUR 310
#define Y_MAX_SCALE_FOUR 182
#define X_MIN_SCALE_FOUR 275
#define X_MAX_SCALE_FOUR 315//prec+40
#define X_MARIO_FOUR 295//prec-20
//TAILLE ECHELLE 5
#define Y_MIN_SCALE_FIVE 300
#define Y_MAX_SCALE_FIVE 190
#define X_MIN_SCALE_FIVE 840
#define X_MAX_SCALE_FIVE 880//prec+40
#define X_MARIO_FIVE 860//prec-20
//TAILLE ECHELLE 6
#define Y_MIN_SCALE_SIX 190
#define Y_MAX_SCALE_SIX 70
#define X_MIN_SCALE_SIX 770
#define X_MAX_SCALE_SIX 810//prec+40
#define X_MARIO_SIX 800//prec-20
//////////////////////////FIN PARAMETRES ECHELLES///////////////////////////

#endif // CONSTANTES_H_INCLUDED
