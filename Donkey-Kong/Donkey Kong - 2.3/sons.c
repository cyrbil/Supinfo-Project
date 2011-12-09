/**
 * \file main.c
 * \brief Regroupe les fonctions liées au son, à leur chargement, et à leur libération.
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

void choose_song (Informations* infos, Son *musique)
{
    srand((int)time(NULL));
    int choice=(rand() % (4+ 1)); //On initialise un nombr aléatoire permettant le choix d'une musique
    //On écrit le chemin des différentes musiques dans des variables :
    char musique1[]="sons/Musique_Jeu.mp3";
    char musique2[]="sons/Musique_Jeu2.mp3";
    char musique3[]="sons/Musique_Jeu3.mp3";
    char musique4[]="sons/Musique_Jeu4.mp3";
    //On indique quel chemin utiliser pour le thème principal du jeu selon le nombre aléatoire généré :
    if (choice==1){strcpy(infos->Maintheme, musique1);}
    if (choice==2){strcpy(infos->Maintheme, musique2);}
    if (choice==3){strcpy(infos->Maintheme, musique3);}
    if (choice==4){strcpy(infos->Maintheme, musique4);}
    if (choice>4){strcpy(infos->Maintheme, musique1);}
    if (choice<1){strcpy(infos->Maintheme, musique2);}
     /////////SON JEU CHARGEMENT///////////////////////////////////////
    FMOD_System_GetChannel(musique->system, 1, &musique->canal_un); //On crée le canal sur lequel sera diffusée la musique
    //Et on charge le son en indiquant le chemin contenu dans infos->Maintheme :
    musique->resultat = FMOD_System_CreateSound(musique->system, infos->Maintheme, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique->jeu);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }
    /* On active la répétition de la musique à l'infini: une fois */
    FMOD_Sound_SetLoopCount(musique->jeu, -1);
    FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->jeu, 0, &musique->canal_un); //Le son est joué sur le canal que l'on a crée
}

void load_game_songs (Son *musique)
{
    //////////////////SON SAUT CHARGEMENT////////////////////////////////
    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/jump.mp3", FMOD_CREATESAMPLE, 0, &musique->jump);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }
    //////////////////////////////////////////////////////////
    //////////////////SON Objets CHARGEMENT////////////////////////////////
    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/coin.mp3", FMOD_CREATESAMPLE, 0, &musique->items);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier coin.mp3\n");
        exit(EXIT_FAILURE);
    }
    //////////////////////////////////////////////////////////
    //////////////////SON One UP CHARGEMENT////////////////////////////////
    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/one_up.mp3", FMOD_CREATESAMPLE, 0, &musique->one_up);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier coin.mp3\n");
        exit(EXIT_FAILURE);
    }
    //////////////////////////////////////////////////////////
    //////////////////SON Power UP CHARGEMENT////////////////////////////////
    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/powerup.mp3", FMOD_CREATESAMPLE, 0, &musique->power_up);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier powerup.mp3\n");
        exit(EXIT_FAILURE);
    }
    //////////////////////////////////////////////////////////
    //////////////////SON Power DOWN CHARGEMENT////////////////////////////////
    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/powerdown.wav", FMOD_CREATESAMPLE, 0, &musique->power_down);
    if (musique->resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier powerdown.wav\n");
        exit(EXIT_FAILURE);
    }
    //////////////////////////////////////////////////////////
    //////////////////////////////SON POW////////////////
    if (FMOD_Channel_IsPlaying (musique->canal_trois, &musique->isplayingsound) !=FMOD_OK)
    {
        musique->resultat = FMOD_System_CreateSound(musique->system, "sons/pow.mp3", FMOD_CREATESAMPLE, 0, &musique->pow);
        if (musique->resultat != FMOD_OK)
        {
            fprintf(stderr, "Impossible de lire le fichier pow.mp3\n");
            exit(EXIT_FAILURE);
        }
    }
    //////////////////////////////////////////////////////////
}

void free_game_songs (Son *musique)
{
    //On désalloue la mémoire octroyée aux sons et leurs variables.
    FMOD_Sound_Release(musique->jeu);
    FMOD_Sound_Release(musique->jump);
    FMOD_Sound_Release(musique->pause);
    FMOD_Sound_Release(musique->items);
    FMOD_Sound_Release(musique->one_up);
    FMOD_Sound_Release(musique->power_up);
    FMOD_Sound_Release(musique->power_down);
    FMOD_Sound_Release(musique->pow);
}
