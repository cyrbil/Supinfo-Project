/**
 * \file structures.c
 * \brief Apporte les différentes phases de contenu à la structure principale du jeu : infos de type struct Information.
 * \author Steinhausser Maxime
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <string.h>
#include <fmod.h>
////////////////////////////////////////////////////////////////////////////
#include "constantes.h"
#include "structures.h"
#include "affichage.h"
#include "personnage.h"
#include "moteur.h"
#include "elements.h"
#include "freeMemory.h"
#include "sons.h"
////////////////////////////////////////////////////////////////////////////

void clean_donnees (Informations *infos, Parametres *settings)
{
    //initialisation des données structurées
    //paramètres
    infos->vitesse_Mario=0;
    infos->portee_saut=0;
    infos->vitesse_Tonneau=0;
    infos->vitesse_Carapace=0;
    infos->pauseMenu=0;
    infos->changesong=0;
    ////NOMBRE de vie////////
    infos->NbVies = NULL;
    infos->positionVies.x=0;
    infos->positionVies.y=0;
    infos->vies=0;
    //lié au score/level
    infos->score=0;
    infos->level=0;
    infos->score_surf=NULL;
    infos->level_surf=NULL;
    infos->positionScore.x = 0;
    infos->positionScore.y = 0;
    infos->positionLevel.x = 0;
    infos->positionLevel.y =0;
    infos->police= NULL;
    infos->couleurNoire.b = 0;//bleu
    infos->couleurNoire.g = 0;//vert
    infos->couleurNoire.r = 0;//rouge
    //Pseudo
    infos->pseudo={0};
    infos->Pseudo_surf=NULL;
    infos->pos_pseudo.x=0;
    infos->pos_pseudo.y=0;
    infos->positionCurseur=-1;
    infos->continuerSaisie=0;
    infos->backspace=0;
    infos->continuer=0;
    //lié à l'affichage
    infos->Stage = NULL;// Chargement de l'image du stage dans une surface
    infos->positionStage.x = 0;
    infos->positionStage.y = 0;
    /////Toolbar////////
    infos->Toolbar = NULL;
    infos->positionToolbar.x = 0;
    infos->positionToolbar.y = 0;
    infos->CurseurVolume = NULL;
    infos->positionCurseurVolume.x=0;
    infos->positionCurseurVolume.y=0;
    ///////Peach//////////////
    infos->posture_Peach = NULL;
    infos->positionPeach.x=0;
    infos->positionPeach.y=0;
    /////////mario/////////////
    infos->positionMario.x = 0;
    infos->positionMario.y = 0;
    infos->posture_Mario = NULL;
    infos->compteur_up_mario=0;
    infos->compteur_frame=0;
    infos->sens=0;
    ///////Donkey//////////////
    infos->posture_Donkey = NULL;
    infos->positionDonkey.x=170;
    infos->positionDonkey.y=0;
    infos->attaque=0;
    //////carapace//////
    infos->carapace=0;
    infos->Carapace=NULL;
    infos->positionCarapace.x=0;
    infos->positionCarapace.y=0;
    //////carapace2//////
    infos->carapace2=0;
    infos->Carapace2=NULL;
    infos->positionCarapace2.x=0;
    infos->positionCarapace2.y=0;
    //////carapace3//////
    infos->carapace3=0;
    infos->Carapace3=NULL;
    infos->positionCarapace3.x=0;
    infos->positionCarapace3.y=0;
    /////tonneau///////
    infos->tonneau=0;
    infos->Tonneau=NULL;
    infos->positionTonneau.x=0;
    infos->positionTonneau.y=0;
    /////tonneau2///////
    infos->tonneau2=0;
    infos->Tonneau2=NULL;
    infos->positionTonneau2.x=0;
    infos->positionTonneau2.y=0;
    /////tonneau3///////
    infos->tonneau3=0;
    infos->Tonneau3=NULL;
    infos->positionTonneau3.x=0;
    infos->positionTonneau3.y=0;
    //lié au jeu
    infos->current_floor=0;
    infos->loose=0;
    infos->game_over=0;
    ////////Flags///////
    infos->Flags=NULL;
    infos->positionFlags.x=0;
    infos->positionFlags.y=0;
    infos->flags=0;
    ////////Flower///////
    infos->Flower=NULL;
    infos->positionFlower.x=0;
    infos->positionFlower.y=0;
    infos->flower=0;
    ////////Bowser///////
    infos->Bowser=NULL;
    infos->positionBowser.x=0;
    infos->positionBowser.y=0;
    infos->bowser=0;
    ////////Skelerex///////
    infos->Skelerex=NULL;
    infos->positionSkelerex.x=0;
    infos->positionSkelerex.y=0;
    infos->skelerex=0;
    ////////Champvolant///////
    infos->Champvolant=NULL;
    infos->positionChampvolant.x=0;
    infos->positionChampvolant.y=0;
    infos->champvolant=0;
    ////////Yoshi///////
    infos->Yoshi=NULL;
    infos->positionYoshi.x=0;
    infos->positionYoshi.y=0;
    infos->yoshi=1;
    ////////Pieuvre///////
    infos->Pieuvre=NULL;
    infos->positionPieuvre.x=0;
    infos->positionPieuvre.y=0;
    infos->pieuvre=0;
    ////////Pow///////
    infos->Pow=NULL;
    infos->positionPow.x=0;
    infos->positionPow.y=0;
    infos->pow=0;
    ////////Champi///////
    infos->Champi=NULL;
    infos->positionChampi.x=0;
    infos->positionChampi.y=0;
    infos->champi=0;
    ////////BLOC METAL///////
    infos->Blocmetal=NULL;
    infos->positionBlocmetal.x=0;
    infos->positionBlocmetal.y=0;
    infos->blocmetal=0;
    infos->metal=0;
    ///////////////////////Fin structure////////////////////////
}

void init_donnees (Informations *infos, Parametres *settings)
{
    srand((int)time(NULL));
    //initialisation des données structurées
    //paramètres
    infos->vitesse_Mario=VITESSE_MARIO_BASE + 1;
    infos->portee_saut=PORTEE_SAUT;
    infos->vitesse_Tonneau=VITESSE_TONNEAU+1;
    infos->vitesse_Carapace=VITESSE_CARAPACE+1;
    infos->pauseMenu=0;
    infos->changesong=0;
    ////NOMBRE de vie////////
    infos->NbVies = NULL;
    infos->positionVies.x=0;
    infos->positionVies.y=0;
    infos->vies=settings->nbVies;
    //lié au score/level
    infos->score=0;
    infos->level=1;
    infos->score_surf=NULL;
    infos->level_surf=NULL;
    infos->positionScore.x = 920;
    infos->positionScore.y = 45;
    infos->positionLevel.x = 960;
    infos->positionLevel.y = 9;
    infos->police= TTF_OpenFont("arial.ttf", 17);
    infos->couleurNoire.b = 0;//bleu
    infos->couleurNoire.g = 0;//vert
    infos->couleurNoire.r = 0;//rouge
    //Pseudo
    infos->pseudo={0};
    infos->pseudo={'J', 'o', 'u', 'e', 'u', 'r', '1'};
    infos->Pseudo_surf=NULL;
    infos->pos_pseudo.x=135;
    infos->pos_pseudo.y=503;
    infos->positionCurseur=1;
    infos->continuerSaisie=1;
    infos->backspace=0;
    infos->continuer=1;
    //lié à l'affichage
    infos->Stage = SDL_LoadBMP("images/stage.bmp");// Chargement de l'image du stage dans une surface
    infos->positionStage.x = 0;
    infos->positionStage.y = 0;
    /////Toolbar////////
    infos->Toolbar = IMG_Load("images/toolbar_ingame.png");
    infos->positionToolbar.x = 0;
    infos->positionToolbar.y = 670;
    infos->CurseurVolume = IMG_Load("images/curseur_volume_toolbar.png");
    infos->positionCurseurVolume.x=(settings->GlobalVolume/0.0054)+80;;
    infos->positionCurseurVolume.y=682;
    ///////Peach//////////////
    infos->posture_Peach = NULL;
    infos->positionPeach.x=425;
    infos->positionPeach.y=5;
    /////////mario/////////////
    infos->positionMario.x = 50;
    infos->positionMario.y = 563;
    infos->posture_Mario = NULL;
    infos->compteur_up_mario=0;
    infos->compteur_frame=0;
    infos->sens=0;
    ///////Donkey//////////////
    infos->posture_Donkey = NULL;
    infos->positionDonkey.x=170;
    infos->positionDonkey.y=0;
    infos->attaque=0;
    //////carapace//////
    infos->carapace=0;
    infos->Carapace=IMG_Load("images/carapace.png");
    infos->positionCarapace.x=10000;
    infos->positionCarapace.y=10000;
    //////carapace2//////
    infos->carapace2=0;
    infos->Carapace2=IMG_Load("images/carapace.png");
    infos->positionCarapace2.x=9500;
    infos->positionCarapace2.y=9500;
    //////carapace3//////
    infos->carapace3=0;
    infos->Carapace3=IMG_Load("images/carapace.png");
    infos->positionCarapace3.x=9000;
    infos->positionCarapace3.y=9000;
    /////tonneau///////
    infos->tonneau=0;
    infos->Tonneau=IMG_Load("images/tonneau.png");
    infos->positionTonneau.x=8500;
    infos->positionTonneau.y=8500;
    /////tonneau2///////
    infos->tonneau2=0;
    infos->Tonneau2=IMG_Load("images/tonneau.png");
    infos->positionTonneau2.x=8000;
    infos->positionTonneau2.y=8000;
    /////tonneau3///////
    infos->tonneau3=0;
    infos->Tonneau3=IMG_Load("images/tonneau.png");
    infos->positionTonneau3.x=7500;
    infos->positionTonneau3.y=7500;
    //lié au jeu
    infos->current_floor=ETAGE_UN;
    infos->loose=0;
    infos->game_over=0;
    ////////Flags///////
    infos->Flags=IMG_Load("images/Flag.png");
    infos->positionFlags.x=600;
    infos->positionFlags.y=90;
    infos->flags=1;
    ////////Flower///////
    infos->Flower=IMG_Load("images/flower_trophy.png");
    infos->positionFlower.x=280;
    infos->positionFlower.y=455;
    infos->flower=1;
    ////////Bowser///////
    infos->Bowser=IMG_Load("images/bowser_trophy.png");
    infos->positionBowser.x=900;
    infos->positionBowser.y=95;
    infos->bowser=1;
    ////////Skelerex///////
    infos->Skelerex=IMG_Load("images/skelerex_trophy.png");
    infos->positionSkelerex.x=50;
    infos->positionSkelerex.y=345;
    infos->skelerex=1;
    ////////Champvolant///////
    infos->Champvolant=IMG_Load("images/Champi_trophy.png");
    infos->positionChampvolant.x=700;
    infos->positionChampvolant.y=328;
    infos->champvolant=1;
    ////////Yoshi///////
    infos->Yoshi=IMG_Load("images/yoshi_trophy.png");
    infos->positionYoshi.x=50;
    infos->positionYoshi.y=180;
    infos->yoshi=1;
    ////////Pieuvre///////
    infos->Pieuvre=IMG_Load("images/pieuvre_trophy.png");
    infos->positionPieuvre.x=890;
    infos->positionPieuvre.y=457;
    infos->pieuvre=1;
    ////////Pow///////
    infos->Pow=IMG_Load("images/pow.png");
    infos->positionPow.x=482;
    infos->positionPow.y=205;
    infos->pow=(rand() % (settings->probas_pow + 1))+1;
    ////////Champi///////
    infos->Champi=IMG_Load("images/Champi_up.png");
    infos->positionChampi.x=340;
    infos->positionChampi.y=95;
    infos->champi=(rand() % (settings->probas_oneUP+ 1))+1;
    ////////BLOC METAL///////
    infos->Blocmetal=IMG_Load("images/bloc_metal.png");
    infos->positionBlocmetal.x=890;
    infos->positionBlocmetal.y=310;
    infos->blocmetal=(rand() % (settings->probas_bloc_metal+ 1))+1;
    infos->metal=0;
    ///////////////////////Fin structure////////////////////////
}

void lvl_up_donnees (Informations *infos, Parametres *settings)
{
    srand((int)time(NULL));
    //initialisation des données structurées
    //paramètres
    if (infos->vitesse_Mario<3){infos->vitesse_Mario++;}
    if (infos->vitesse_Tonneau<3){infos->vitesse_Tonneau++;}
    if (infos->vitesse_Carapace<5){infos->vitesse_Carapace++;}
    //lié au score/level
    infos->score+=10000;
    infos->level++;
    infos->positionScore.x = 920;
    infos->positionScore.y = 45;
    /////////mario/////////////
    infos->positionMario.x = 50;
    infos->positionMario.y = 563;
    infos->posture_Mario = NULL;
    infos->compteur_up_mario=0;
    infos->compteur_frame=0;
    infos->sens=0;
    ///////Donkey//////////////
    infos->attaque=0;
    //lié au jeu
    infos->current_floor=ETAGE_UN;
    infos->loose=0;
    infos->game_over=0;
    ////////Flags///////
    infos->positionFlags.x=600;
    infos->positionFlags.y=90;
    infos->flags=1;
    ////////Flower///////
    infos->flower=1;
    ////////Bowser///////
    infos->bowser=1;
    ////////Skelerex///////
    infos->skelerex=1;
    ////////Champvolant///////
    infos->champvolant=1;
    ////////Yoshi///////
    infos->yoshi=1;
    ////////Pieuvre///////
    infos->pieuvre=1;
    ////////Pow///////
    infos->pow=(rand() % (settings->probas_pow + 1))+1;
    ////////Champi///////
    infos->champi=(rand() % (settings->probas_oneUP+ 1))+1;
    /////BLOC METAL//////
    infos->blocmetal=(rand() % (settings->probas_bloc_metal+ 1))+1;
    ///////////////////////Fin structure////////////////////////
}
