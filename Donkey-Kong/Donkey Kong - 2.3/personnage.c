/**
 * \file personnage.c
 * \brief Fichier de gestion des actions du personnage joueur.
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

void jump (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)//Déplace mario en saut
{
    int i;
//////////////////////////////PENTE TYPE 1////////////////////////////////////
    if (infos->typepente==TYPE_1)
    {
         if (infos->sens==1)
        {
            infos->posture_Mario = infos->Mario[SAUT_D];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            infos->positionMario.y+=((infos->positionMariotemp_x-infos->positionMario.x)/PENTE);
            MAJ_Affichage(infos, ecran);
        }
    if (infos->sens==0)
        {
            infos->posture_Mario = infos->Mario[SAUT_S];
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
        }

    if (infos->sens==-1)
        {
            infos->posture_Mario = infos->Mario[SAUT_G];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if(infos->positionMario.x>=25){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if(infos->positionMario.x>=25){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            infos->positionMario.y+=((infos->positionMariotemp_x-infos->positionMario.x)/PENTE);
            MAJ_Affichage(infos, ecran);
        }

    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 2////////////////////////////////////
    if (infos->typepente==TYPE_2)
    {
         if (infos->sens==1)
        {
            infos->posture_Mario = infos->Mario[SAUT_D];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            infos->positionMario.y-=((infos->positionMariotemp_x-infos->positionMario.x)/PENTE);
            MAJ_Affichage(infos, ecran);
        }
    if (infos->sens==0)
        {
            infos->posture_Mario = infos->Mario[SAUT_S];
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
        }

    if (infos->sens==-1)
        {
            infos->posture_Mario = infos->Mario[SAUT_G];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if(infos->positionMario.x>=25){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=GRAVITE; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if(infos->positionMario.x>=25){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            infos->positionMario.y-=((infos->positionMariotemp_x-infos->positionMario.x)/PENTE);
            MAJ_Affichage(infos, ecran);
        }

    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 3////////////////////////////////////
    if (infos->typepente==TYPE_3)
    {
         if (infos->sens==1)
        {
            infos->posture_Mario = infos->Mario[SAUT_D];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut*2;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if (infos->positionMario.x<=900){infos->positionMario.x+=infos->vitesse_Mario*infos->portee_saut*2;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
        }
    if (infos->sens==0)
        {
            infos->posture_Mario = infos->Mario[SAUT_S];
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
        }

    if (infos->sens==-1)
        {
            infos->posture_Mario = infos->Mario[SAUT_G];
            infos->positionMariotemp_x=infos->positionMario.x;
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y-=2;
                if(infos->positionMario.x>=30){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut*2;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
            for (i=0; i<=35; i++)
            {
                Projectiles_Engine (infos);
                DonkeyKong_Engine(infos);
                Collision_Engine (ecran, infos, musique);
                check_if_pow(infos, musique);
                Game_Over(ecran, infos, musique, settings);
                infos->positionMario.y+=2;
                if(infos->positionMario.x>=30){infos->positionMario.x-=infos->vitesse_Mario*infos->portee_saut*2;}
                MAJ_Affichage(infos, ecran);
                if (infos->flags==0 || infos->loose==1 || infos->game_over==1){break;}
            }
        }

    }
//////////////////////////////////////////////////////////////////////////////
}

void move_right (Informations *infos)//Déplace mario vers la droite
{
//////////////////////////////PENTE TYPE 1////////////////////////////////////
    if (infos->typepente==TYPE_1)
    {
        if (infos->positionMario.x<=900)
        {
            infos->sens=1;
            infos->positionMario.x=(infos->positionMario.x)+(infos->vitesse_Mario);
            infos->compteur_up_mario+=infos->vitesse_Mario;
            if (infos->compteur_up_mario>=PENTE){infos->positionMario.y--;   infos->compteur_up_mario=0;}
        }
    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 2////////////////////////////////////
    if (infos->typepente==TYPE_2)
    {
        if (infos->positionMario.x<=900)
        {
            infos->sens=1;
            infos->positionMario.x=(infos->positionMario.x)+(infos->vitesse_Mario);
            infos->compteur_up_mario+=infos->vitesse_Mario;
            if (infos->compteur_up_mario>=PENTE){infos->positionMario.y++;   infos->compteur_up_mario=0;}
        }
    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 3////////////////////////////////////
    if (infos->typepente==TYPE_3)
    {
        if (infos->positionMario.x>=25)
        {
            infos->sens=1;
            infos->positionMario.x=(infos->positionMario.x)+(infos->vitesse_Mario);
        }
    }
//////////////////////////////////////////////////////////////////////////////
}

void move_left (Informations *infos)//Déplace mario vers la gauche
{
//////////////////////////////PENTE TYPE 1////////////////////////////////////
    if (infos->typepente==TYPE_1)
    {
        if (infos->positionMario.x>=25)
        {
            infos->sens=-1;
            infos->positionMario.x=(infos->positionMario.x)-(infos->vitesse_Mario);
            infos->compteur_up_mario-=infos->vitesse_Mario;
            if (infos->compteur_up_mario<=-PENTE){infos->positionMario.y++;   infos->compteur_up_mario=0;}
        }
    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 2////////////////////////////////////
    if (infos->typepente==TYPE_2)
    {
        if (infos->positionMario.x>=25)
        {
            infos->sens=-1;
            infos->positionMario.x=(infos->positionMario.x)-(infos->vitesse_Mario);
            infos->compteur_up_mario-=infos->vitesse_Mario;
            if (infos->compteur_up_mario<=-PENTE){infos->positionMario.y--;   infos->compteur_up_mario=0;}
        }
    }
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////PENTE TYPE 3////////////////////////////////////
    if (infos->typepente==TYPE_3)
    {
        if (infos->positionMario.x>=25)
        {
            infos->sens=-1;
            infos->positionMario.x=(infos->positionMario.x)-(infos->vitesse_Mario);
        }
    }
//////////////////////////////////////////////////////////////////////////////
}

