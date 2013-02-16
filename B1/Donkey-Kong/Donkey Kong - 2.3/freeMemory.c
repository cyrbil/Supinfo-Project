/**
 * \file freeMemory.c
 * \brief Ce fichier regroupe les fonctions utiles à la libération de la mémoire. Ces fonctions sont appelées afin de libèrer la mémoire occupée inutilement; lorsqu'une surface n'est plus utilisée.
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//les delays sont là par sécurité, vider la mémoire/réatribuer trop rapidement semble susceptible de faire planter le programme.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_surfaces_Persos_and_reattribute(SDL_Surface *ecran, Informations *infos )
{
    infos->NbVies=NULL;
    infos->posture_Mario=NULL;
    infos->posture_Peach=NULL;
    infos->posture_Donkey=NULL;
    SDL_Delay(10);
    SDL_FreeSurface(infos->NbVies);
    SDL_FreeSurface(infos->posture_Mario);
    SDL_FreeSurface(infos->posture_Donkey);
    SDL_FreeSurface(infos->posture_Peach);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[STATIC]);
    SDL_FreeSurface(infos->Mario[SAUT_G]);
    SDL_FreeSurface(infos->Mario[SAUT_D]);
    SDL_FreeSurface(infos->Mario[SAUT_S]);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[G1]);
    SDL_FreeSurface(infos->Mario[G2]);
    SDL_FreeSurface(infos->Mario[G3]);
    SDL_FreeSurface(infos->Mario[G4]);
    SDL_FreeSurface(infos->Mario[G5]);
    SDL_FreeSurface(infos->Mario[G6]);
    SDL_FreeSurface(infos->Mario[G7]);
    SDL_FreeSurface(infos->Mario[G8]);
    SDL_FreeSurface(infos->Mario[G9]);
    SDL_FreeSurface(infos->Mario[G10]);
    SDL_FreeSurface(infos->Mario[G11]);
    SDL_FreeSurface(infos->Mario[G12]);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[D1]);
    SDL_FreeSurface(infos->Mario[D2]);
    SDL_FreeSurface(infos->Mario[D3]);
    SDL_FreeSurface(infos->Mario[D4]);
    SDL_FreeSurface(infos->Mario[D5]);
    SDL_FreeSurface(infos->Mario[D6]);
    SDL_FreeSurface(infos->Mario[D7]);
    SDL_FreeSurface(infos->Mario[D8]);
    SDL_FreeSurface(infos->Mario[D9]);
    SDL_FreeSurface(infos->Mario[D10]);
    SDL_FreeSurface(infos->Mario[D11]);
    SDL_FreeSurface(infos->Mario[D12]);
    SDL_FreeSurface(infos->Mario[CLIMBING]);
    SDL_FreeSurface(infos->Donkey[DK_NORMAL]);
    SDL_FreeSurface(infos->Donkey[DK_CARAPACE]);
    SDL_FreeSurface(infos->Donkey[DK_TONNEAU]);
    SDL_FreeSurface(infos->Donkey[DK_POW]);
    SDL_FreeSurface(infos->Peach[PEACH1]);
    SDL_FreeSurface(infos->Peach[PEACH_HELP]);
    SDL_FreeSurface(infos->Vies[UNE_VIE]);
    SDL_FreeSurface(infos->Vies[DEUX_VIES]);
    SDL_FreeSurface(infos->Vies[TROIS_VIES]);
    SDL_FreeSurface(infos->Vies[ZERO_VIE]);
    SDL_Delay(10);
    sprites_loading (infos);
    SDL_Delay(10);
    infos->posture_Mario=infos->Mario[DK_NORMAL];
    infos->posture_Donkey=infos->Donkey[DK_NORMAL];
    infos->posture_Peach=infos->Peach[PEACH1];

}

void free_surfaces_Persos(SDL_Surface *ecran, Informations *infos )
{

    infos->NbVies=NULL;
    infos->posture_Mario=NULL;
    infos->posture_Peach=NULL;
    infos->posture_Donkey=NULL;
    SDL_Delay(10);
    SDL_FreeSurface(infos->NbVies);
    SDL_FreeSurface(infos->posture_Mario);
    SDL_FreeSurface(infos->posture_Donkey);
    SDL_FreeSurface(infos->posture_Peach);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[STATIC]);
    SDL_FreeSurface(infos->Mario[SAUT_G]);
    SDL_FreeSurface(infos->Mario[SAUT_D]);
    SDL_FreeSurface(infos->Mario[SAUT_S]);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[G1]);
    SDL_FreeSurface(infos->Mario[G2]);
    SDL_FreeSurface(infos->Mario[G3]);
    SDL_FreeSurface(infos->Mario[G4]);
    SDL_FreeSurface(infos->Mario[G5]);
    SDL_FreeSurface(infos->Mario[G6]);
    SDL_FreeSurface(infos->Mario[G7]);
    SDL_FreeSurface(infos->Mario[G8]);
    SDL_FreeSurface(infos->Mario[G9]);
    SDL_FreeSurface(infos->Mario[G10]);
    SDL_FreeSurface(infos->Mario[G11]);
    SDL_FreeSurface(infos->Mario[G12]);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Mario[D1]);
    SDL_FreeSurface(infos->Mario[D2]);
    SDL_FreeSurface(infos->Mario[D3]);
    SDL_FreeSurface(infos->Mario[D4]);
    SDL_FreeSurface(infos->Mario[D5]);
    SDL_FreeSurface(infos->Mario[D6]);
    SDL_FreeSurface(infos->Mario[D7]);
    SDL_FreeSurface(infos->Mario[D8]);
    SDL_FreeSurface(infos->Mario[D9]);
    SDL_FreeSurface(infos->Mario[D10]);
    SDL_FreeSurface(infos->Mario[D11]);
    SDL_FreeSurface(infos->Mario[D12]);
    SDL_FreeSurface(infos->Mario[CLIMBING]);
    SDL_FreeSurface(infos->Donkey[DK_NORMAL]);
    SDL_FreeSurface(infos->Donkey[DK_CARAPACE]);
    SDL_FreeSurface(infos->Donkey[DK_TONNEAU]);
    SDL_FreeSurface(infos->Donkey[DK_POW]);
    SDL_FreeSurface(infos->Peach[PEACH1]);
    SDL_FreeSurface(infos->Peach[PEACH_HELP]);
    SDL_FreeSurface(infos->Vies[UNE_VIE]);
    SDL_FreeSurface(infos->Vies[DEUX_VIES]);
    SDL_FreeSurface(infos->Vies[TROIS_VIES]);
    SDL_FreeSurface(infos->Vies[ZERO_VIE]);
    SDL_Delay(10);
}

void free_surfaces_elements(SDL_Surface *ecran, Informations *infos )
{
    SDL_FreeSurface(infos->Stage);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Flower);
    SDL_FreeSurface(infos->Bowser);
    SDL_FreeSurface(infos->Yoshi);
    SDL_FreeSurface(infos->Pieuvre);
    SDL_FreeSurface(infos->Champi);
    SDL_FreeSurface(infos->Champvolant);
    SDL_FreeSurface(infos->Pow);
    SDL_FreeSurface(infos->Skelerex);
    SDL_FreeSurface(infos->Blocmetal);
    SDL_FreeSurface(infos->Flags);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Carapace);
    SDL_FreeSurface(infos->Carapace2);
    SDL_FreeSurface(infos->Carapace3);
    SDL_FreeSurface(infos->Tonneau);
    SDL_FreeSurface(infos->Tonneau2);
    SDL_FreeSurface(infos->Tonneau3);
    SDL_FreeSurface(infos->Toolbar);
    SDL_FreeSurface(infos->CurseurVolume);
}

void free_surfaces_elements_and_reattribute(SDL_Surface *ecran, Informations *infos )
{

    SDL_FreeSurface(infos->Stage);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Flower);
    SDL_FreeSurface(infos->Bowser);
    SDL_FreeSurface(infos->Yoshi);
    SDL_FreeSurface(infos->Pieuvre);
    SDL_FreeSurface(infos->Champi);
    SDL_FreeSurface(infos->Champvolant);
    SDL_FreeSurface(infos->Pow);
    SDL_FreeSurface(infos->Skelerex);
    SDL_FreeSurface(infos->Blocmetal);
    SDL_FreeSurface(infos->Flags);
    SDL_Delay(10);
    SDL_FreeSurface(infos->Carapace);
    SDL_FreeSurface(infos->Carapace2);
    SDL_FreeSurface(infos->Carapace3);
    SDL_FreeSurface(infos->Tonneau);
    SDL_FreeSurface(infos->Tonneau2);
    SDL_FreeSurface(infos->Tonneau3);
    SDL_FreeSurface(infos->Toolbar);
    SDL_FreeSurface(infos->CurseurVolume);

    infos->Stage = SDL_LoadBMP("images/stage.bmp");

    infos->Flags=IMG_Load("images/Flag.png");
    infos->Flower=IMG_Load("images/flower_trophy.png");
    infos->Bowser=IMG_Load("images/bowser_trophy.png");
    infos->Skelerex=IMG_Load("images/skelerex_trophy.png");
    infos->Champvolant=IMG_Load("images/Champi_trophy.png");
    infos->Yoshi=IMG_Load("images/yoshi_trophy.png");
    infos->Pieuvre=IMG_Load("images/pieuvre_trophy.png");
    infos->Pow=IMG_Load("images/pow.png");
    infos->Champi=IMG_Load("images/Champi_up.png");
    infos->Blocmetal=IMG_Load("images/bloc_metal.png");
    infos->Carapace=IMG_Load("images/carapace.png");
    infos->Carapace2=IMG_Load("images/carapace.png");
    infos->Carapace3=IMG_Load("images/carapace.png");
    infos->Tonneau=IMG_Load("images/tonneau.png");
    infos->Tonneau2=IMG_Load("images/tonneau.png");
    infos->Tonneau3=IMG_Load("images/tonneau.png");
    infos->Toolbar = IMG_Load("images/toolbar_ingame.png");
    infos->CurseurVolume = IMG_Load("images/curseur_volume_toolbar.png");
}

