/**
 * \file elements.c
 * \brief Regroupe certains éléments interactifs du jeu, ainsi que les fonctions d'écriture de paramètres dans un fichier externe.
 * \author Steinhausser Maxime, Jean Burellier
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

void DonkeyKong_Engine (Informations *infos)
{
    if (infos->pow_activ!=1) //Si le pow n'est pas actif, Donkey kong peut attaquer
    {
    srand((int)time(NULL));
    const int max = FREQUENCE_ATTAQUE, min = 0;
    infos->attaque =(rand() % (max - min + 1)) + min; //Definissions de l'attaque lancée par Donkey de manière aléatoire

        if (infos->attaque==0 || infos->attaque==8) //Si l'attaque est l'attaque 8 ou 0, Donkey Kong ne fais rien et revient à sa posture normale.
        {
            infos->posture_Donkey=infos->Donkey[DK_NORMAL];
        }

        if (infos->attaque==2 && infos->carapace != 1) //Si l'attaque est l'attaque 2 et que la premiere carapace n'est pas déjà lancée :
        {
            // Donkey Kong change de posture et lance la carapace n°1.
            infos->posture_Donkey=infos->Donkey[DK_CARAPACE];
            infos->carapace=1;
            infos->positionCarapace.x=350;
            infos->positionCarapace.y=120;
        }

        if (infos->attaque==3 && infos->tonneau != 1) //Si l'attaque est l'attaque 3 et que le premier tonneau n'est pas déjà lancé :
        {
            // Donkey Kong change de posture et lance le tonneau n°1.
            infos->posture_Donkey=infos->Donkey[DK_TONNEAU];
            infos->tonneau=1;
            infos->positionTonneau.x=(rand() % (950 - 150 + 1)) + 150; //définit la position initiale du tonneau de manière aléatoire
            infos->positionTonneau.y=0;
        }

        if (infos->attaque==4 && infos->tonneau2 != 1) //Si l'attaque est l'attaque 4 et que le second tonneau n'est pas déjà lancé :
        {
            // Donkey Kong change de posture et lance le tonneau n°2.
            infos->posture_Donkey=infos->Donkey[DK_TONNEAU];
            infos->tonneau2=1;
            infos->positionTonneau2.x=(rand() % (950 - 150 + 1)) + 150; //définit la position initiale du tonneau de manière aléatoire
            infos->positionTonneau2.y=0;
        }

        if (infos->attaque==5 && infos->tonneau3 != 1)//Si l'attaque est l'attaque 5 et que le troisième tonneau n'est pas déjà lancé :
        {
            // Donkey Kong change de posture et lance le tonneau n°3.
            infos->posture_Donkey=infos->Donkey[DK_TONNEAU];
            infos->tonneau3=1;
            infos->positionTonneau3.x=(rand() % (950 - 150 + 1)) + 150; //définit la position initiale du tonneau de manière aléatoire
            infos->positionTonneau3.y=0;
        }

        if (infos->attaque==6 && infos->carapace2 != 1) //Si l'attaque est l'attaque 6 et que la seconde carapace n'est pas déjà lancée :
        {
            // Donkey Kong change de posture et lance la carapace n°2.
            infos->posture_Donkey=infos->Donkey[DK_CARAPACE];
            infos->carapace2=1;
            infos->positionCarapace2.x=350;
            infos->positionCarapace2.y=120;
        }

        if (infos->attaque==7 && infos->carapace3 != 1) //Si l'attaque est l'attaque 7 et que la seconde carapace n'est pas déjà lancée :
        {
            // Donkey Kong change de posture et lance la carapace n°3
            infos->posture_Donkey=infos->Donkey[DK_CARAPACE];
            infos->carapace3=1;
            infos->positionCarapace3.x=350;
            infos->positionCarapace3.y=120;
        }
    }
}

void Projectiles_Engine (Informations *infos)
{
    ///////////////////TONNEAUX//////////////////
    if (infos->tonneau==1) //si le tonneau 1 est en jeu, le tonneau suit ce mouvement :
    {
        infos->positionTonneau.y+=infos->vitesse_Tonneau; //la position du tonneau est incrémenté verticalement, vers le bas
        if (infos->positionTonneau.y>=700) //une fois le tonneau sorti de l'écran,
        {
            infos->tonneau=0; //le tonneau est détruit
        }
    }

    if (infos->tonneau2==1) //si le tonneau 2 est en jeu, le tonneau suit ce mouvement :
    {
        infos->positionTonneau2.y+=infos->vitesse_Tonneau; //la position du tonneau est incrémenté verticalement, vers le bas
        if (infos->positionTonneau2.y>=700) //une fois le tonneau sorti de l'écran,
        {
            infos->tonneau2=0; //le tonneau est détruit
        }
    }

    if (infos->tonneau3==1) //si le tonneau 3 est en jeu, le tonneau suit ce mouvement :
    {
        infos->positionTonneau3.y+=infos->vitesse_Tonneau; //la position du tonneau est incrémenté verticalement, vers le bas
        if (infos->positionTonneau3.y>=700) //une fois le tonneau sorti de l'écran,
        {
            infos->tonneau3=0; //le tonneau est détruit
        }
    }
    ///////////////////////////////////////////

    //////////////////CARAPACE/////////////////
    if (infos->carapace==1) //si la carapace 1 est en jeu, la carapace suit ce mouvement :
    {
        if (infos->positionCarapace.x<795 && infos->positionCarapace.y<180)    { infos->positionCarapace.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x>=790 && infos->positionCarapace.y<245)   { infos->positionCarapace.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x>300 && infos->positionCarapace.y<250 && infos->positionCarapace.y>235)   { infos->positionCarapace.x-=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x<=305 && infos->positionCarapace.y>230 && infos->positionCarapace.y<365)   { infos->positionCarapace.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x>115 && infos->positionCarapace.y>355 && infos->positionCarapace.y<375)   { infos->positionCarapace.x-=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x<120 && infos->positionCarapace.y>340 && infos->positionCarapace.y<490)   { infos->positionCarapace.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x<1010 && infos->positionCarapace.y>480 && infos->positionCarapace.y<500)   { infos->positionCarapace.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace.x>1000)   { infos->carapace=0; }
    }

    //////////////////CARAPACE2/////////////////
    if (infos->carapace2==1) //si la carapace 2 est en jeu, la carapace suit ce mouvement :
    {
        if (infos->positionCarapace2.x<795 && infos->positionCarapace2.y<180)    { infos->positionCarapace2.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x>=790 && infos->positionCarapace2.y<245)   { infos->positionCarapace2.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x>300 && infos->positionCarapace2.y<250 && infos->positionCarapace2.y>235)   { infos->positionCarapace2.x-=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x<=305 && infos->positionCarapace2.y>230 && infos->positionCarapace2.y<365)   { infos->positionCarapace2.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x<433 && infos->positionCarapace2.y>355 && infos->positionCarapace2.y<375)   { infos->positionCarapace2.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x>428 && infos->positionCarapace2.y>340 && infos->positionCarapace2.y<490)   { infos->positionCarapace2.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x<1010 && infos->positionCarapace2.y>480 && infos->positionCarapace2.y<500)   { infos->positionCarapace2.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace2.x>1000)   { infos->carapace2=0; }
    }

    //////////////////CARAPACE3/////////////////
    if (infos->carapace3==1) //si la carapace 3 est en jeu, la carapace suit ce mouvement :
    {
        if (infos->positionCarapace3.x<795 && infos->positionCarapace3.y<180)    { infos->positionCarapace3.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x>=790 && infos->positionCarapace3.y<245)   { infos->positionCarapace3.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x<860 && infos->positionCarapace3.y<250 && infos->positionCarapace3.y>235)   { infos->positionCarapace3.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x>850 && infos->positionCarapace3.y>230 && infos->positionCarapace3.y<360)   { infos->positionCarapace3.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x>438 && infos->positionCarapace3.y>355 && infos->positionCarapace3.y<370)   { infos->positionCarapace3.x-=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x<445 && infos->positionCarapace3.y>340 && infos->positionCarapace3.y<490)   { infos->positionCarapace3.y+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x<1010 && infos->positionCarapace3.y>480 && infos->positionCarapace3.y<500)   { infos->positionCarapace3.x+=infos->vitesse_Carapace; }
        if (infos->positionCarapace3.x>1000)   { infos->carapace3=0; }
    }
}

void Peach_engine (Informations *infos)
{
    srand((int)time(NULL));
    infos->help = (rand() % (FREQUENCE_HELP - 0 + FREQUENCE_HELP)) + 0;

    if (infos->help==1)
    {
        infos->posture_Peach=infos->Peach[PEACH_HELP];
    }

    if (infos->help==2)
    {
        infos->posture_Peach=infos->Peach[PEACH1];
    }
}

void check_if_pow(Informations *infos, Son *musique)
{
    if (infos->pow_activ==1) //Si le pow est actif, on fait trembler l'écran
    {
        if (infos->compteur_pow_activ%1==0)
        {
            infos->positionStage.x=5;
            infos->positionStage.y=5;
            infos->positionDonkey.x=175;
            infos->positionDonkey.y=5;
            infos->positionPeach.x=430;
            infos->positionPeach.y=10;
             ////////Flags///////
            infos->positionFlags.x=605;
            infos->positionFlags.y=95;
            ////////Flower///////
            infos->positionFlower.x=285;
            infos->positionFlower.y=460;
            ////////Bowser///////
            infos->positionBowser.x=905;
            infos->positionBowser.y=100;
            ////////Skelerex///////
            infos->positionSkelerex.x=55;
            infos->positionSkelerex.y=350;
            ////////Champvolant///////
            infos->positionChampvolant.x=705;
            infos->positionChampvolant.y=333;
            ////////Yoshi///////
            infos->positionYoshi.x=55;
            infos->positionYoshi.y=185;
            ////////Pieuvre///////
            infos->positionPieuvre.x=895;
            infos->positionPieuvre.y=462;
            ////////Champi///////
            infos->positionChampi.x=345;
            infos->positionChampi.y=100;
            ////////Pow///////
            infos->positionPow.x=487;
            infos->positionPow.y=210;
            ////Bloc Metal/////
            infos->positionBlocmetal.x=895;
            infos->positionBlocmetal.y=315;
        }
        if (infos->compteur_pow_activ%2==0)
        {
            infos->positionStage.x=-5;
            infos->positionStage.y=-5;
            infos->positionDonkey.x=165;
            infos->positionDonkey.y=-5;
            infos->positionPeach.x=420;
            infos->positionPeach.y=0;
             ////////Flags///////
            infos->positionFlags.x=595;
            infos->positionFlags.y=85;
            ////////Flower///////
            infos->positionFlower.x=275;
            infos->positionFlower.y=450;
            ////////Bowser///////
            infos->positionBowser.x=895;
            infos->positionBowser.y=90;
            ////////Skelerex///////
            infos->positionSkelerex.x=45;
            infos->positionSkelerex.y=340;
            ////////Champvolant///////
            infos->positionChampvolant.x=695;
            infos->positionChampvolant.y=323;
            ////////Yoshi///////
            infos->positionYoshi.x=45;
            infos->positionYoshi.y=175;
            ////////Pieuvre///////
            infos->positionPieuvre.x=885;
            infos->positionPieuvre.y=452;
            ////////Champi///////
            infos->positionChampi.x=335;
            infos->positionChampi.y=90;
            ////////Pow///////
            infos->positionPow.x=477;
            infos->positionPow.y=200;
            ////Bloc Metal/////
            infos->positionBlocmetal.x=885;
            infos->positionBlocmetal.y=305;
        }
        else
        {
            infos->positionStage.x=0;
            infos->positionStage.y=0;
            infos->positionYoshi.x=50;
            infos->positionYoshi.y=180;
            infos->positionDonkey.x=170;
            infos->positionDonkey.y=0;
            infos->positionPeach.x=425;
            infos->positionPeach.y=5;
             ////////Flags///////
            infos->positionFlags.x=600;
            infos->positionFlags.y=90;
            ////////Flower///////
            infos->positionFlower.x=280;
            infos->positionFlower.y=455;
            ////////Bowser///////
            infos->positionBowser.x=900;
            infos->positionBowser.y=95;
            ////////Skelerex///////
            infos->positionSkelerex.x=50;
            infos->positionSkelerex.y=345;
            ////////Champvolant///////
            infos->positionChampvolant.x=700;
            infos->positionChampvolant.y=328;
            ////////Yoshi///////
            infos->positionYoshi.x=50;
            infos->positionYoshi.y=180;
            ////////Pieuvre///////
            infos->positionPieuvre.x=890;
            infos->positionPieuvre.y=457;
            ////////Champi///////
            infos->positionChampi.x=340;
            infos->positionChampi.y=95;
            ////////Pow///////
            infos->positionPow.x=482;
            infos->positionPow.y=205;
            ////Bloc Metal/////
            infos->positionBlocmetal.x=890;
            infos->positionBlocmetal.y=310;
        }
        infos->compteur_pow_activ++; //on incrémente le compteur
        infos->posture_Donkey=infos->Donkey[DK_POW]; //Donkey Kong prend la posture lié au déclenchement du Pow
        //Les projectiles sont détruits
        infos->carapace=0;
        infos->carapace2=0;
        infos->carapace3=0;
        infos->tonneau=0;
        infos->tonneau2=0;
        infos->tonneau3=0;
        infos->positionCarapace.x=1000;
        infos->positionCarapace.y=1000;
        infos->positionCarapace2.x=1000;
        infos->positionCarapace2.y=1000;
        infos->positionCarapace3.x=1000;
        infos->positionCarapace3.y=1000;
        infos->positionTonneau.x=1000;
        infos->positionTonneau.y=1000;
        infos->positionTonneau2.x=1000;
        infos->positionTonneau2.y=1000;
        infos->positionTonneau3.x=1000;
        infos->positionTonneau3.y=1000;
        if (infos->compteur_pow_activ==DUREE_POW) //jusqu'à ce que la durée limite soit atteinte
            {
            //L'affichage revient à la normale
            infos->positionStage.x=0;
            infos->positionStage.y=0;
            infos->pow_activ=0;
            }
    }
}


void get_settings(Parametres *settings)
{
    // lecture fichier parametre
    FILE* fichier = NULL;

    fichier = fopen("parametre.txt", "r");

    if (fichier != NULL)
    {
        fscanf(fichier, "%f %d %d %d %d %d %d", &settings->GlobalVolume, &settings->changeMusicSet, &settings->nbVies, &settings->probas_pow, &settings->probas_oneUP, &settings->probas_bloc_metal, &settings->fullscreen);
        // correspondance valeurs
        settings->probas_pow=(settings->probas_pow)-1;
        settings->probas_oneUP=(settings->probas_oneUP)-1;
        settings->probas_bloc_metal=(settings->probas_bloc_metal)-1;
    }
    else
    {
        // On affiche un message d'erreur dans les logs et attribue les valeurs par défauts
        fprintf(stderr, "Impossible d'ouvrir le fichier parametre.txt");
        settings->GlobalVolume=1.0;
        settings->changeMusicSet=2;
        settings->nbVies =3;
        settings->probas_pow =PROBAS_POW;
        settings->probas_oneUP=PROBAS_CHAMPI_UP;
        settings->probas_bloc_metal=PROBAS_BLOC_METAL;
        settings->fullscreen=0;
    }

    //voir si on lit le fichier ou les parametres de base
    //on vérifie chaque valeur du fichier
    if (settings->GlobalVolume<0.0 || settings->GlobalVolume>1.0) //si son corrompu
    {
        settings->GlobalVolume=1.0;
    }

    if (settings->changeMusicSet !=1
        && settings->changeMusicSet !=2
        && settings->changeMusicSet !=3
        && settings->changeMusicSet !=4
        && settings->changeMusicSet !=5 ) //si musicset corrompu
    {
        settings->changeMusicSet=2;
    }

    if (settings->nbVies !=0
        && settings->nbVies !=1
        && settings->nbVies !=2
        && settings->nbVies !=3)// si nbvie corrompu
    {
        settings->nbVies =3;
    }

    if (settings->probas_pow !=0
        && settings->probas_pow !=1
        && settings->probas_pow !=2
        && settings->probas_pow !=3
        && settings->probas_pow !=4)// si probas_pow corrompu
    {
        settings->probas_pow =PROBAS_POW;
    }

    if (settings->probas_oneUP !=0
        && settings->probas_oneUP !=1
        && settings->probas_oneUP !=2
        && settings->probas_oneUP !=3
        && settings->probas_oneUP !=4) // si probas_oneUP corrompu
    {
        settings->probas_oneUP=PROBAS_CHAMPI_UP;
    }

    if (settings->probas_bloc_metal !=0
        && settings->probas_bloc_metal !=1
        && settings->probas_bloc_metal !=2
        && settings->probas_bloc_metal !=3
        && settings->probas_bloc_metal !=4) // si probas_blocmetal corrompu
    {
        settings->probas_bloc_metal=PROBAS_BLOC_METAL;
    }

    if (settings->fullscreen !=0
        && settings->fullscreen !=1) // si mode d'affichage corrompu
    {
        settings->fullscreen=0;
    }
}

void write_settings(Parametres *settings)
{
//ecriture des données dans le fichier parametre
    FILE* fichier = NULL;
    fichier = fopen("parametre.txt", "w");
    if (fichier != NULL)
    {
        // correspondance valeurs
        settings->probas_pow=(settings->probas_pow)+1;
        settings->probas_oneUP=(settings->probas_oneUP)+1;
        settings->probas_bloc_metal=(settings->probas_bloc_metal)+1;
        // On l'écrit dans le fichier
        fprintf(fichier, "%f %d %d %d %d %d %d", settings->GlobalVolume, settings->changeMusicSet, settings->nbVies, settings->probas_pow, settings->probas_oneUP, settings->probas_bloc_metal, settings->fullscreen );
        fclose(fichier);
    }
}
