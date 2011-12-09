/**
 * \file affichage.c
 * \brief Fichier de gestion de l'affichage, animations et menus.
 * \author Steinhausser Maxime, Demingeon Cyril, Fleury Dorian, Jean Burellier
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
#include "reseau.h"
////////////////////////////////////////////////////////////////////////////


void sprites_loading (Informations *infos)//initialise les tableaux de sprites Mario/Donkey avec chaque image
{
    ////////////////////////MARIO//////////////////////////////////
    if (infos->metal!=1) //Si le pouvoir METAL n'est pas actif :
    {   //Les sprites de Mario sont ceux-ci :
        infos->Mario[STATIC] = IMG_Load("images/mariostatic.png");
        infos->Mario[SAUT_G] = IMG_Load("images/mario_saut_gauche.png");
        infos->Mario[SAUT_D] = IMG_Load("images/mario_saut_droite.png");
        infos->Mario[SAUT_S] = IMG_Load("images/mario_saut.png");
        infos->Mario[G1] = IMG_Load("images/mario_sprint1_gauche.png");
        infos->Mario[G2] = IMG_Load("images/mario_sprint2_gauche.png");
        infos->Mario[G3] = IMG_Load("images/mario_sprint3_gauche.png");
        infos->Mario[G4] = IMG_Load("images/mario_sprint4_gauche.png");
        infos->Mario[G5] = IMG_Load("images/mario_sprint5_gauche.png");
        infos->Mario[G6] = IMG_Load("images/mario_sprint6_gauche.png");
        infos->Mario[G7] = IMG_Load("images/mario_sprint7_gauche.png");
        infos->Mario[G8] = IMG_Load("images/mario_sprint8_gauche.png");
        infos->Mario[G9] = IMG_Load("images/mario_sprint9_gauche.png");
        infos->Mario[G10] = IMG_Load("images/mario_sprint10_gauche.png");
        infos->Mario[G11] = IMG_Load("images/mario_sprint11_gauche.png");
        infos->Mario[G12] = IMG_Load("images/mario_sprint12_gauche.png");
        infos->Mario[D1] = IMG_Load("images/mario_sprint1_droite.png");
        infos->Mario[D2] = IMG_Load("images/mario_sprint2_droite.png");
        infos->Mario[D3] = IMG_Load("images/mario_sprint3_droite.png");
        infos->Mario[D4] = IMG_Load("images/mario_sprint4_droite.png");
        infos->Mario[D5] = IMG_Load("images/mario_sprint5_droite.png");
        infos->Mario[D6] = IMG_Load("images/mario_sprint6_droite.png");
        infos->Mario[D7] = IMG_Load("images/mario_sprint7_droite.png");
        infos->Mario[D8] = IMG_Load("images/mario_sprint8_droite.png");
        infos->Mario[D9] = IMG_Load("images/mario_sprint9_droite.png");
        infos->Mario[D10] = IMG_Load("images/mario_sprint10_droite.png");
        infos->Mario[D11] = IMG_Load("images/mario_sprint11_droite.png");
        infos->Mario[D12] = IMG_Load("images/mario_sprint12_droite.png");
        infos->Mario[CLIMBING] = IMG_Load("images/marioclimb.png");
    }
    if (infos->metal==1) //Si le pouvoir METAL est actif :
    {   //Les sprites de Mario sont ceux-ci :
        infos->Mario[STATIC] = IMG_Load("images/mario_metal/mariostatic.png");
        infos->Mario[SAUT_G] = IMG_Load("images/mario_metal/mario_saut_gauche.png");
        infos->Mario[SAUT_D] = IMG_Load("images/mario_metal/mario_saut_droite.png");
        infos->Mario[SAUT_S] = IMG_Load("images/mario_metal/mario_saut.png");
        infos->Mario[G1] = IMG_Load("images/mario_metal/mario_sprint1_gauche.png");
        infos->Mario[G2] = IMG_Load("images/mario_metal/mario_sprint2_gauche.png");
        infos->Mario[G3] = IMG_Load("images/mario_metal/mario_sprint3_gauche.png");
        infos->Mario[G4] = IMG_Load("images/mario_metal/mario_sprint4_gauche.png");
        infos->Mario[G5] = IMG_Load("images/mario_metal/mario_sprint5_gauche.png");
        infos->Mario[G6] = IMG_Load("images/mario_metal/mario_sprint6_gauche.png");
        infos->Mario[G7] = IMG_Load("images/mario_metal/mario_sprint7_gauche.png");
        infos->Mario[G8] = IMG_Load("images/mario_metal/mario_sprint8_gauche.png");
        infos->Mario[G9] = IMG_Load("images/mario_metal/mario_sprint9_gauche.png");
        infos->Mario[G10] = IMG_Load("images/mario_metal/mario_sprint10_gauche.png");
        infos->Mario[G11] = IMG_Load("images/mario_metal/mario_sprint11_gauche.png");
        infos->Mario[G12] = IMG_Load("images/mario_metal/mario_sprint12_gauche.png");
        infos->Mario[D1] = IMG_Load("images/mario_metal/mario_sprint1_droite.png");
        infos->Mario[D2] = IMG_Load("images/mario_metal/mario_sprint2_droite.png");
        infos->Mario[D3] = IMG_Load("images/mario_metal/mario_sprint3_droite.png");
        infos->Mario[D4] = IMG_Load("images/mario_metal/mario_sprint4_droite.png");
        infos->Mario[D5] = IMG_Load("images/mario_metal/mario_sprint5_droite.png");
        infos->Mario[D6] = IMG_Load("images/mario_metal/mario_sprint6_droite.png");
        infos->Mario[D7] = IMG_Load("images/mario_metal/mario_sprint7_droite.png");
        infos->Mario[D8] = IMG_Load("images/mario_metal/mario_sprint8_droite.png");
        infos->Mario[D9] = IMG_Load("images/mario_metal/mario_sprint9_droite.png");
        infos->Mario[D10] = IMG_Load("images/mario_metal/mario_sprint10_droite.png");
        infos->Mario[D11] = IMG_Load("images/mario_metal/mario_sprint11_droite.png");
        infos->Mario[D12] = IMG_Load("images/mario_metal/mario_sprint12_droite.png");
        infos->Mario[CLIMBING] = IMG_Load("images/mario_metal/marioclimb.png");
    }
    ////////////////////////DONKEY/////////////////////////////////
    infos->Donkey[DK_NORMAL] = IMG_Load("images/Donkey.png");
    infos->Donkey[DK_CARAPACE] = IMG_Load("images/DK_carapace.png");
    infos->Donkey[DK_TONNEAU] = IMG_Load("images/DK_tonneau.png");
    infos->Donkey[DK_POW] = IMG_Load("images/Donkey_pow.png");
    ////////////////////////PEACH/////////////////////////////////
    infos->Peach[PEACH1] = IMG_Load("images/Peach.png");
    infos->Peach[PEACH_HELP] = IMG_Load("images/PeachHelp.png");
    ////////////////////////NOMBRE VIES/////////////////////////////////
    infos->Vies[ZERO_VIE] = IMG_Load("images/champi0.png");
    infos->Vies[UNE_VIE] = IMG_Load("images/champi1.png");
    infos->Vies[DEUX_VIES] = IMG_Load("images/champi2.png");
    infos->Vies[TROIS_VIES] = IMG_Load("images/champi3.png");
}

void MAJ_Affichage(Informations *infos, SDL_Surface *ecran)//Met à jour l'affichage de la totalité des éléments du jeu : à rajouter Donkey Kong, Peach, Score, Level, projectiles.
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //On efface l'écran
    SDL_BlitSurface(infos->Stage, NULL, ecran, &infos->positionStage);//Blitte le stage
    infos->score_surf = TTF_RenderText_Blended(infos->police, infos->score_string, infos->couleurNoire);
    SDL_BlitSurface(infos->score_surf, NULL, ecran, &infos->positionScore); //Blit de la surface contenant le score
    infos->level_surf = TTF_RenderText_Blended(infos->police, infos->level_string, infos->couleurNoire);
    SDL_BlitSurface(infos->level_surf, NULL, ecran, &infos->positionLevel); //Blit de la surface contenant le level
    SDL_BlitSurface(infos->NbVies, NULL, ecran, &infos->positionVies);//Blitte le nombre de vie
    if (infos->flags==1){SDL_BlitSurface(infos->Flags, NULL, ecran, &infos->positionFlags);}//Blitte l'objet Flags
    if (infos->flower==1){SDL_BlitSurface(infos->Flower, NULL, ecran, &infos->positionFlower);}//Blitte l'objet Flower
    if (infos->bowser==1){SDL_BlitSurface(infos->Bowser, NULL, ecran, &infos->positionBowser);}//Blitte l'objet Bowser
    if (infos->champi==1){SDL_BlitSurface(infos->Champi, NULL, ecran, &infos->positionChampi);}//Blitte l'objet Champi
    if (infos->pow==1){SDL_BlitSurface(infos->Pow, NULL, ecran, &infos->positionPow);}//Blitte l'objet Pow
    if (infos->blocmetal==1){SDL_BlitSurface(infos->Blocmetal, NULL, ecran, &infos->positionBlocmetal);}//Blitte l'objet Pow
    if (infos->skelerex==1){SDL_BlitSurface(infos->Skelerex, NULL, ecran, &infos->positionSkelerex);}//Blitte l'objet Skelerex
    if (infos->champvolant==1){SDL_BlitSurface(infos->Champvolant, NULL, ecran, &infos->positionChampvolant);}//Blitte l'objet Champvolant
    if (infos->yoshi==1){SDL_BlitSurface(infos->Yoshi, NULL, ecran, &infos->positionYoshi);}//Blitte l'objet Yoshi
    if (infos->pieuvre==1){SDL_BlitSurface(infos->Pieuvre, NULL, ecran, &infos->positionPieuvre);}//Blitte l'objet Pieuvre
    SDL_BlitSurface(infos->posture_Donkey, NULL, ecran, &infos->positionDonkey);//Blitte Donkey
    SDL_BlitSurface(infos->posture_Peach, NULL, ecran, &infos->positionPeach);//Blitte Donkey
    SDL_BlitSurface(infos->Carapace, NULL, ecran, &infos->positionCarapace);//Blitte Carapace
    SDL_BlitSurface(infos->Carapace2, NULL, ecran, &infos->positionCarapace2);//Blitte Carapace2
    SDL_BlitSurface(infos->Carapace3, NULL, ecran, &infos->positionCarapace3);//Blitte Carapace3
    SDL_BlitSurface(infos->Tonneau, NULL, ecran, &infos->positionTonneau);//Blitte Tonneau
    SDL_BlitSurface(infos->Tonneau2, NULL, ecran, &infos->positionTonneau2);//Blitte Tonneau2
    SDL_BlitSurface(infos->Tonneau3, NULL, ecran, &infos->positionTonneau3);//Blitte Tonneau3
    SDL_BlitSurface(infos->posture_Mario, NULL, ecran, &infos->positionMario);// On blitte mario à sa nouvelle position par-dessus l'écran
    SDL_BlitSurface(infos->Toolbar, NULL, ecran, &infos->positionToolbar);//Blitte Toolbar
    SDL_BlitSurface(infos->CurseurVolume, NULL, ecran, &infos->positionCurseurVolume);//Blitte curseur volume
    if (infos->loose==1 && infos->game_over!=1) //En cas de défaite, mais qu'il reste des vies :
        {
        //On affiche l'image de défaite :
        infos->YouLoose = IMG_Load("images/loose.jpg");
        SDL_BlitSurface(infos->YouLoose, NULL, ecran, &infos->positionStage);
        SDL_FreeSurface(infos->YouLoose);
        }
    if (infos->flags==0) //En cas d'obtention du drapeau, et donc de victoire :
        {
        //On affiche l'image de victoire :
        infos->Congratulations = IMG_Load("images/congratulations.jpg");
        SDL_BlitSurface(infos->Congratulations, NULL, ecran, &infos->positionStage);
        SDL_FreeSurface(infos->Congratulations);
        }
    if (infos->game_over==1) //En cas de Game Over :
        {
        infos->positionScore.x=230; //On modifie la position du score
        infos->positionScore.y=405;//...
        //On affiche l'image du Game Over :
        infos->GameOver = IMG_Load("images/Game_over.jpg");
        SDL_BlitSurface(infos->GameOver, NULL, ecran, &infos->positionStage);
        SDL_FreeSurface(infos->GameOver);
        SDL_BlitSurface(infos->score_surf, NULL, ecran, &infos->positionScore); //Blit de la surface contenant le score par dessus tout
        //On gère l'affichage du pseudo tapé par le joueur :
        infos->Pseudo_surf = TTF_RenderText_Blended(infos->police, infos->pseudo, infos->couleurNoire);
        SDL_BlitSurface(infos->Pseudo_surf, NULL, ecran, &infos->pos_pseudo);
        SDL_FreeSurface(infos->Pseudo_surf);
        }
    SDL_Flip(ecran); // On met à jour l'affichage
    SDL_FreeSurface(infos->score_surf); //On libère la surface contenant le score
    SDL_FreeSurface(infos->level_surf); //On libère la surface contenant le level
}

void change_frame_left(Informations *infos, SDL_Surface *ecran)//Gère le passage des sprites de mario en déplacement vers la droite
        {
        //Un compteur est incrémenté à l'infini, modulo 220, les images sont alternées régulierement
        infos->compteur_frame=(infos->compteur_frame+1)%220;
        if ( (infos->compteur_frame>=0)&&(infos->compteur_frame<=10) ){infos->posture_Mario=infos->Mario[G1];}
        if ( (infos->compteur_frame>10)&&(infos->compteur_frame<=20) ){infos->posture_Mario=infos->Mario[G2];}
        if ( (infos->compteur_frame>20)&&(infos->compteur_frame<=30) ){infos->posture_Mario=infos->Mario[G3];}
        if ( (infos->compteur_frame>30)&&(infos->compteur_frame<=40) ){infos->posture_Mario=infos->Mario[G4];}
        if ( (infos->compteur_frame>40)&&(infos->compteur_frame<=50) ){infos->posture_Mario=infos->Mario[G5];}
        if ( (infos->compteur_frame>50)&&(infos->compteur_frame<=60) ){infos->posture_Mario=infos->Mario[G6];}
        if ( (infos->compteur_frame>60)&&(infos->compteur_frame<=70) ){infos->posture_Mario=infos->Mario[G7];}
        if ( (infos->compteur_frame>70)&&(infos->compteur_frame<=80) ){infos->posture_Mario=infos->Mario[G8];}
        if ( (infos->compteur_frame>80)&&(infos->compteur_frame<=90) ){infos->posture_Mario=infos->Mario[G9];}
        if ( (infos->compteur_frame>90)&&(infos->compteur_frame<=100) ){infos->posture_Mario=infos->Mario[G10];}
        if ( (infos->compteur_frame>100)&&(infos->compteur_frame<=110) ){infos->posture_Mario=infos->Mario[G11];}
        if ( (infos->compteur_frame>110)&&(infos->compteur_frame<=120) ){infos->posture_Mario=infos->Mario[G12];}
        if ( (infos->compteur_frame>120)&&(infos->compteur_frame<=130) ){infos->posture_Mario=infos->Mario[G11];}
        if ( (infos->compteur_frame>130)&&(infos->compteur_frame<=140) ){infos->posture_Mario=infos->Mario[G10];}
        if ( (infos->compteur_frame>140)&&(infos->compteur_frame<=150) ){infos->posture_Mario=infos->Mario[G9];}
        if ( (infos->compteur_frame>150)&&(infos->compteur_frame<=160) ){infos->posture_Mario=infos->Mario[G8];}
        if ( (infos->compteur_frame>160)&&(infos->compteur_frame<=170) ){infos->posture_Mario=infos->Mario[G7];}
        if ( (infos->compteur_frame>170)&&(infos->compteur_frame<=180) ){infos->posture_Mario=infos->Mario[G6];}
        if ( (infos->compteur_frame>180)&&(infos->compteur_frame<=190) ){infos->posture_Mario=infos->Mario[G5];}
        if ( (infos->compteur_frame>190)&&(infos->compteur_frame<=200) ){infos->posture_Mario=infos->Mario[G4];}
        if ( (infos->compteur_frame>200)&&(infos->compteur_frame<=210) ){infos->posture_Mario=infos->Mario[G3];}
        if ( (infos->compteur_frame>210)&&(infos->compteur_frame<=220) ){infos->posture_Mario=infos->Mario[G2];}
        MAJ_Affichage(infos, ecran);
        }

void change_frame_right(Informations *infos, SDL_Surface *ecran)//Gère le passage des sprites de mario en déplacement vers la droite
        {
        //Un compteur est incrémenté à l'infini, modulo 220, les images sont alternées régulierement
        infos->compteur_frame=(infos->compteur_frame+1)%220;
        if ( (infos->compteur_frame>=0)&&(infos->compteur_frame<=10) ){infos->posture_Mario=infos->Mario[D1];}
        if ( (infos->compteur_frame>10)&&(infos->compteur_frame<=20) ){infos->posture_Mario=infos->Mario[D2];}
        if ( (infos->compteur_frame>20)&&(infos->compteur_frame<=30) ){infos->posture_Mario=infos->Mario[D3];}
        if ( (infos->compteur_frame>30)&&(infos->compteur_frame<=40) ){infos->posture_Mario=infos->Mario[D4];}
        if ( (infos->compteur_frame>40)&&(infos->compteur_frame<=50) ){infos->posture_Mario=infos->Mario[D5];}
        if ( (infos->compteur_frame>50)&&(infos->compteur_frame<=60) ){infos->posture_Mario=infos->Mario[D6];}
        if ( (infos->compteur_frame>60)&&(infos->compteur_frame<=70) ){infos->posture_Mario=infos->Mario[D7];}
        if ( (infos->compteur_frame>70)&&(infos->compteur_frame<=80) ){infos->posture_Mario=infos->Mario[D8];}
        if ( (infos->compteur_frame>80)&&(infos->compteur_frame<=90) ){infos->posture_Mario=infos->Mario[D9];}
        if ( (infos->compteur_frame>90)&&(infos->compteur_frame<=100) ){infos->posture_Mario=infos->Mario[D10];}
        if ( (infos->compteur_frame>100)&&(infos->compteur_frame<=110) ){infos->posture_Mario=infos->Mario[D11];}
        if ( (infos->compteur_frame>110)&&(infos->compteur_frame<=120) ){infos->posture_Mario=infos->Mario[D12];}
        if ( (infos->compteur_frame>120)&&(infos->compteur_frame<=130) ){infos->posture_Mario=infos->Mario[D11];}
        if ( (infos->compteur_frame>130)&&(infos->compteur_frame<=140) ){infos->posture_Mario=infos->Mario[D10];}
        if ( (infos->compteur_frame>140)&&(infos->compteur_frame<=150) ){infos->posture_Mario=infos->Mario[D9];}
        if ( (infos->compteur_frame>150)&&(infos->compteur_frame<=160) ){infos->posture_Mario=infos->Mario[D8];}
        if ( (infos->compteur_frame>160)&&(infos->compteur_frame<=170) ){infos->posture_Mario=infos->Mario[D7];}
        if ( (infos->compteur_frame>170)&&(infos->compteur_frame<=180) ){infos->posture_Mario=infos->Mario[D6];}
        if ( (infos->compteur_frame>180)&&(infos->compteur_frame<=190) ){infos->posture_Mario=infos->Mario[D5];}
        if ( (infos->compteur_frame>190)&&(infos->compteur_frame<=200) ){infos->posture_Mario=infos->Mario[D4];}
        if ( (infos->compteur_frame>200)&&(infos->compteur_frame<=210) ){infos->posture_Mario=infos->Mario[D3];}
        if ( (infos->compteur_frame>210)&&(infos->compteur_frame<=220) ){infos->posture_Mario=infos->Mario[D2];}
        MAJ_Affichage(infos, ecran);
        }


void Game_Over(SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
{
Uint8 *keystate = SDL_GetKeyState(NULL);//Contiendra l'état d'une touche (enfoncée ou non)
if (infos->loose==1) //Si le héros viens de mourrir
    {
        FMOD_Channel_SetPaused(musique->canal_trois, 1);//pause son pow
        ////////////////////SON DEATH////////////////////////////
        if ((FMOD_Channel_IsPlaying (musique->canal_deux, &musique->isplayingsound) !=FMOD_OK)&& infos->game_over!=1) //Si ce n'est pas un game over
        {
            musique->resultat = FMOD_System_CreateSound(musique->system, "sons/death.mp3", FMOD_CREATESAMPLE, 0, &musique->death);
            if (musique->resultat != FMOD_OK)
            {
                fprintf(stderr, "Impossible de lire le fichier mp3\n");
                exit(EXIT_FAILURE);
            }
            FMOD_Channel_SetPaused(musique->canal_un, 1);
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->death, 0, &musique->canal_deux); //On joue le son de mort
        }
        ///////////////////////////////////////////////////////////

        if (infos->game_over==1) //Si c'est un game over
            {
                //////////////////////////////SON GAME OVER////////////////
                if (FMOD_Channel_IsPlaying (musique->canal_deux, &musique->isplayingsound) !=FMOD_OK)
                {
                    musique->resultat = FMOD_System_CreateSound(musique->system, "sons/game_over.mp3", FMOD_CREATESAMPLE, 0, &musique->gameOver);
                    if (musique->resultat != FMOD_OK)
                    {
                        fprintf(stderr, "Impossible de lire le fichier mp3\n");
                        exit(EXIT_FAILURE);
                    }
                    FMOD_Channel_SetPaused(musique->canal_un, 1);
                    FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->gameOver, 0, &musique->canal_deux);
                }
                ////////////////////////SIASIE PSEUDO//////////////////////////////
                SDL_Event event;
                SDL_EnableUNICODE(1);  //Permet d'activer l'UNICODE pour permettre la saisie et les caractères spéciaux
                    SDL_WaitEvent(&event);
                    if(event.type == SDL_KEYDOWN) //Si une touche est enfoncée
                    {
                        if(event.key.keysym.sym == SDLK_BACKSPACE) // Si il appuis sur la touche retour arriere...
                        {
                            if (infos->positionCurseur>0)//On recule le curseur de 1, sauf si la position est au minimum
                            {
                            infos->positionCurseur--;
                            }
                            infos->pseudo[infos->positionCurseur] = '\0'; //Efface l'ancienne saisie
                            infos->backspace=1;
                            MAJ_Affichage(infos, ecran);
                        }
                        if(((event.key.keysym.unicode & 0xFF00) == 0x0000)
                           && event.key.keysym.sym != SDLK_CAPSLOCK //empeche la detection directe du capslock comme caractère
                           && event.key.keysym.sym != SDLK_RSHIFT //empeche la detection directe du shift comme caractère
                           && event.key.keysym.sym != SDLK_LSHIFT //empeche la detection directe du shift comme caractère
                           && event.key.keysym.sym != SDLK_UP //On continue de lister les exceptions
                           && event.key.keysym.sym != SDLK_DOWN
                           && event.key.keysym.sym != SDLK_RIGHT
                           && event.key.keysym.sym != SDLK_LEFT
                           && event.key.keysym.sym != SDLK_LCTRL
                           && event.key.keysym.sym != SDLK_LALT
                           && event.key.keysym.sym != SDLK_RCTRL
                           && event.key.keysym.sym != SDLK_LCTRL
                           && event.key.keysym.sym != SDLK_RSUPER
                           && event.key.keysym.sym != SDLK_LSUPER
                           && event.key.keysym.sym != SDLK_TAB
                           && event.key.keysym.sym != SDLK_SCROLLOCK
                           && event.key.keysym.sym != SDLK_RMETA
                           && event.key.keysym.sym != SDLK_LMETA
                           && event.key.keysym.sym != SDLK_MODE
                           && event.key.keysym.sym != SDLK_HELP
                           && event.key.keysym.sym != SDLK_PRINT
                           && event.key.keysym.sym != SDLK_END
                           && event.key.keysym.sym != SDLK_PAGEDOWN
                           && event.key.keysym.sym != SDLK_PAGEUP
                           && event.key.keysym.sym != SDLK_PLUS
                           && event.key.keysym.sym != SDLK_MINUS
                           && event.key.keysym.sym != SDLK_SPACE
                           && event.key.keysym.sym != SDLK_F1
                           && event.key.keysym.sym != SDLK_F2
                           && event.key.keysym.sym != SDLK_F3
                           && event.key.keysym.sym != SDLK_F4
                           && event.key.keysym.sym != SDLK_F5
                           && event.key.keysym.sym != SDLK_F6
                           && event.key.keysym.sym != SDLK_F7
                           && event.key.keysym.sym != SDLK_F8
                           && event.key.keysym.sym != SDLK_F9
                           && event.key.keysym.sym != SDLK_F10
                           && event.key.keysym.sym != SDLK_F11
                           && event.key.keysym.sym != SDLK_F12
                           && event.key.keysym.sym != SDLK_F13
                           && event.key.keysym.sym != SDLK_POWER
                           && event.key.keysym.sym != SDLK_EURO
                           && event.key.keysym.sym != SDLK_MENU
                           && event.key.keysym.sym != SDLK_NUMLOCK
                           && event.key.keysym.sym != SDLK_ESCAPE
                           && event.key.keysym.sym != SDLK_RETURN
                           && (infos->positionCurseur + 1 < 20) && infos->continuerSaisie == 1 && infos->backspace==0)
                        {
                            infos->pseudo[infos->positionCurseur] = event.key.keysym.unicode; //On enregistre la touche appuyée dans le tableau à la position du curseur
                            infos->positionCurseur++; //On avance le curseur de 1
                            infos->pseudo[infos->positionCurseur] = '\0'; //On vide cette nouvelle case pour la prochaine entrée.
                            MAJ_Affichage(infos, ecran);
                        }
                    }
                    infos->backspace=0;
            }
            //////////////////////FIN SAISIE PSEUDO//////////////////////////////////////////
    if (keystate[SDLK_RETURN]==1 && infos->positionCurseur!=0) //Si la touche ENTREE est pressée et que le pseudo saisie n'est pas vide
        {
        if (infos->game_over!=1) //Si ce n'est pas un game over
            {
            //Les surfaces sont libèrées puis réatribuées avec leurs valeurs d'origine
            free_surfaces_Persos_and_reattribute(ecran, infos);
            free_surfaces_elements_and_reattribute(ecran, infos);
            }
        /////////mario/////////////
        //Certaines variables concernant Mario sont redéfinies
        infos->positionMario.x = 50; //Position x Initiale Mario
        infos->positionMario.y = 563; //Position y Initiale Mario
        infos->posture_Mario = infos->Mario[STATIC]; //Posture Initiale Mario
        infos->compteur_up_mario=0;
        infos->compteur_frame=0;
        infos->sens=0;
        ///////////////////////////
        //lié au jeu///////////////
        infos->current_floor=ETAGE_UN;
        infos->loose=0; //La variable loose est remise à zero pour relancer le jeu
        infos->vies--; //On perd une vie

        if (infos->game_over!=1){FMOD_Sound_Release(musique->death);} //On désalloue la mémoire octroyée au son lors d'une défaite
        //Les surfaces sont libèrées puis réatribuées avec leurs valeurs d'origine
        free_surfaces_Persos_and_reattribute(ecran, infos);
        free_surfaces_elements_and_reattribute(ecran, infos);
        ///////////////////////////
        SDL_Delay(100);
        if (infos->game_over==1) //Si c'est un game over
            {
            score_send(infos->pseudo,infos->score_string);//Envoi des scores/pseudos en ligne.
            SDL_FreeSurface(infos->Stage); //Libération des surfaces
            FMOD_Sound_Release(musique->gameOver); //On désalloue la mémoire octroyée au son lors d'un game over
            init_donnees(infos, settings); //On réinitialise les données avec les valeurs de base
            }
        }
    }
}

void Next_level (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
{
    if (infos->flags==0) //Si le drapeau est atteint
    {
        Uint8 *keystate = SDL_GetKeyState(NULL);//Contiendra l'état d'une touche (enfoncée ou non)
        FMOD_Channel_SetPaused(musique->canal_trois, 1);//pause son pow
        ////////////////////SON NEXT LEVEL////////////////////////////
        if (FMOD_Channel_IsPlaying (musique->canal_deux, &musique->isplayingsound) !=FMOD_OK)
        {
            musique->resultat = FMOD_System_CreateSound(musique->system, "sons/NextLevel.mp3", FMOD_CREATESAMPLE, 0, &musique->next_level);
            if (musique->resultat != FMOD_OK)
            {
                fprintf(stderr, "Impossible de lire le fichier mp3\n");
                exit(EXIT_FAILURE);
            }
            FMOD_Channel_SetPaused(musique->canal_un, 1);
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->next_level, 0, &musique->canal_deux); //On joue le son de victoire
        }
        ///////////////////////////////////////////////////////////

    if (keystate[SDLK_RETURN]==1) //Si la touche ENTREE est enfoncée
        {
            //On libère les surfaces et les réattributs :
            free_surfaces_Persos_and_reattribute(ecran, infos);
            free_surfaces_elements_and_reattribute(ecran, infos);
            FMOD_Sound_Release(musique->next_level); //On désalloue la mémoire octroyée au son lors d'une victoire
            lvl_up_donnees (infos, settings); //On incrémente la difficulté du jeu
            infos->changesong++; //On incrémente la variable qui détermine si l'on doit relancer le choix d'une musique ou non
            //Et s'il faut relancer le choix, on désalloue la mémoire octroyé au précédent son avant de relancer le choix de la prochaine musique via la fonction choose_song(...)
            if (infos->changesong==settings->changeMusicSet){FMOD_Sound_Release(musique->jeu); choose_song (infos, musique); infos->changesong=0;}
        }
    }
}

void pause_menu(SDL_Surface *ecran, Menustruct *GestionMenus, Informations *infos, Son *musique)
{
    ///////////////////////MENU PAUSE////////////////////////
    SDL_Event event;
    //Les sons sont stoppées :
    FMOD_Channel_SetPaused(musique->canal_un, 1);
    FMOD_Channel_SetPaused(musique->canal_trois, 1);
    infos->pauseMenu=1;

    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            GestionMenus->continuer2 = 0;
            GestionMenus->continuer1 = 0;
            GestionMenus->continuer = 0;
            free_surfaces_Persos(ecran, infos);
            free_surfaces_elements(ecran, infos);
            free_game_songs (musique);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    SDL_Delay(200);
                    GestionMenus->continuer = 1;
                    GestionMenus->continuer1 = 0;
                    GestionMenus->Selection=1;
                    free_surfaces_Persos(ecran, infos);
                    free_surfaces_elements(ecran, infos);
                    free_game_songs (musique);
                    break;
                case SDLK_RETURN: //Si la touche entrée est enfoncée :
                    if (GestionMenus->Selection ==1){SDL_Delay(200);    GestionMenus->continuer2=1;    GestionMenus->continuer1=1;} //Que la selection est la une, on retourne au jeu
                    if (GestionMenus->Selection ==2) //Si la selection est la 2
                        {
                        //On libère la mémoire
                        free_surfaces_Persos(ecran, infos);
                        SDL_Delay(100);
                        free_surfaces_elements(ecran, infos);
                        SDL_Delay(100);
                        //Et on retourne au menu principal du programme
                        GestionMenus->continuer = 1;
                        GestionMenus->continuer1 = 0;
                        GestionMenus->Selection = 1;
                        free_game_songs (musique);
                        }
                    //Si la selection est la 3, on quitte le programme
                    if (GestionMenus->Selection ==3){SDL_Delay(200);    GestionMenus->continuer = 0;   GestionMenus->continuer1 = 0; GestionMenus->Selection=1;}
                    break;

                case SDLK_RIGHT: //Si la touche RIGHT est enfoncée, on incrémente la selection
                    if (GestionMenus->Selection<=3){GestionMenus->Selection++;}
                    break;

                case SDLK_LEFT: //Si la touche LEFT est enfoncée, on décrémente la selection
                    if (GestionMenus->Selection>=1){GestionMenus->Selection--;}
                    break;

                default:
                void();
                break;
            }
            break;
    }
    if (GestionMenus->Selection>3){GestionMenus->Selection=1;} //Si on dépasse la selection 3 on revient à la 1
    if (GestionMenus->Selection<1){GestionMenus->Selection=3;} //Si on dépasse la selection 1 on revient à la 3
    //////////////GESTION MENU PAUSE AFFICHAGE///////////////

    /////PLAY//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (GestionMenus->Selection==1){GestionMenus->PlayButton = IMG_Load("images/BoutonPlay.png");}
    else {GestionMenus->PlayButton = IMG_Load("images/BoutonPlay2.png");}
    /////RETOUR MENU///////////////////////////////////////////////////////////////////////////////////////////////
    if (GestionMenus->Selection==2){GestionMenus->MenuReturn = IMG_Load("images/BoutonRetourMenu.png");}
    else {GestionMenus->MenuReturn = IMG_Load("images/BoutonRetourMenu2.png");}
    /////QUITTER///////////////////////////////////////////////////////////////////////////////////////////////////
    if (GestionMenus->Selection==3) {GestionMenus->QuitButton = IMG_Load("images/BoutonQuitter.png");}
    else{GestionMenus->QuitButton = IMG_Load("images/BoutonQuitter2.png");}
    /////AFFICHAGE/////////////////////////////////////////////////////////////////////////////////////////////////
    GestionMenus->Menu = IMG_Load("images/menu.jpg");
    SDL_BlitSurface(GestionMenus->Menu, NULL, ecran, &GestionMenus->positionMenu);// On blitte par-dessus l'écran
    SDL_BlitSurface(GestionMenus->PlayButton, NULL, ecran, &GestionMenus->positionPlay);
    SDL_BlitSurface(GestionMenus->QuitButton, NULL, ecran, &GestionMenus->positionQuit);
    SDL_BlitSurface(GestionMenus->MenuReturn, NULL, ecran, &GestionMenus->positionReturn);
    SDL_Flip(ecran); // Mise à jour de l'écran
    SDL_FreeSurface(GestionMenus->Menu);
    SDL_FreeSurface(GestionMenus->PlayButton);
    SDL_FreeSurface(GestionMenus->QuitButton);
    SDL_FreeSurface(GestionMenus->MenuReturn);
}

void HowToPlay(SDL_Surface *ecran, Menustruct *GestionMenus)
{
GestionMenus->Menu = IMG_Load("images/howtoplay.jpg");
SDL_BlitSurface(GestionMenus->Menu, NULL, ecran, &GestionMenus->positionMenu);
SDL_Flip(ecran); // Mise à jour de l'écran
SDL_FreeSurface(GestionMenus->Menu);
while (GestionMenus->continuer1)
    {
        SDL_Event event;
        SDL_PollEvent(&event);//Surveille les évènements sans bloquer l'éxécution du programme
        switch(event.type)
        {
            case SDL_QUIT:
                GestionMenus->continuer1 = 0;
                GestionMenus->continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    case SDLK_RETURN:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    default:
                    break;
                }
            default:
            break;
        }
    }
}


void Score_Menu(SDL_Surface *ecran, Menustruct *GestionMenus)
{
    GestionMenus->Menu = IMG_Load("images/MenuScore.jpg");
    get_and_display_scores(ecran, GestionMenus);
    SDL_Flip(ecran); // Mise à jour de l'écran
    /////LIBERATION DES SURFACES////////
    SDL_FreeSurface(GestionMenus->Menu);

///////ATTENTE D'UN EVENEMENT POUR QUITTER LE MENU SCORE//////
while (GestionMenus->continuer1)
    {
        SDL_Event event;

        SDL_PollEvent(&event);//Surveille les évènements sans bloquer l'éxécution du programme
        switch(event.type)
        {
            case SDL_QUIT:
                GestionMenus->continuer1 = 0;
                GestionMenus->continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    case SDLK_RETURN:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    default:
                    break;
                }
            default:
            break;
        }
    }
}

void Menu_Credits(SDL_Surface *ecran, Menustruct *GestionMenus)
{
GestionMenus->Menu = IMG_Load("images/CreditsMenu.jpg");
SDL_BlitSurface(GestionMenus->Menu, NULL, ecran, &GestionMenus->positionMenu);
SDL_Flip(ecran); // Mise à jour de l'écran
SDL_FreeSurface(GestionMenus->Menu);
while (GestionMenus->continuer1)
    {
        SDL_Event event;
        SDL_PollEvent(&event);//Surveille les évènements sans bloquer l'éxécution du programme
        switch(event.type)
        {
            case SDL_QUIT:
                GestionMenus->continuer1 = 0;
                GestionMenus->continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    case SDLK_RETURN:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        break;
                    default:
                    break;
                }
            default:
            break;
        }
    }
}

void Menu_Settings(SDL_Surface *ecran, Menustruct *GestionMenus, Parametres *settings)
{
    GestionMenus->Menu = IMG_Load("images/ParametresMenu.jpg");
    //////////VOLUME//////////////////////////
    SDL_Surface *VolumeBar=IMG_Load("images/settings/volumebar.jpg");
    SDL_Rect positionVolumeBar;
    positionVolumeBar.x=55;
    positionVolumeBar.y=205;
    SDL_Surface *CurseurVolumeBar=IMG_Load("images/settings/curseur_bar.png");
    SDL_Rect positionCurseurVolumeBar;
    positionCurseurVolumeBar.x=(settings->GlobalVolume/0.004)+140;
    positionCurseurVolumeBar.y=203;
    //////////SET CHANGE MUSIC///////////////////
    SDL_Surface *ChangeMusicSet=NULL;
    ChangeMusicSet=IMG_Load("images/settings/set_change_music1.png");
    SDL_Rect positionChangeMusicSet={0,0,0,0};
    positionChangeMusicSet.x=55;
    positionChangeMusicSet.y=240;
    //////////SET NBVIES INITIALES///////////////////
    SDL_Surface *NombreVies=NULL;
    NombreVies=IMG_Load("images/settings/nb_vies_ini3.png");
    SDL_Rect positionVies={0,0,0,0};
    positionVies.x=55;
    positionVies.y=300;
    //////////SET PROBAS POW///////////////////
    SDL_Surface *ProbasPow=NULL;
    ProbasPow=IMG_Load("images/settings/probas_pow1.png");
    SDL_Rect positionProbasPow={0,0,0,0};
    positionProbasPow.x=55;
    positionProbasPow.y=340;
    //////////SET PROBAS ONE UP///////////////////
    SDL_Surface *ProbasOneUP=NULL;
    ProbasOneUP=IMG_Load("images/settings/probas_oneUP1.png");
    SDL_Rect positionProbasOneUP={0,0,0,0};
    positionProbasOneUP.x=55;
    positionProbasOneUP.y=404;
    //////////SET PROBAS BLOC METAL///////////////////
    SDL_Surface *ProbasBlocMetal=NULL;
    ProbasBlocMetal=IMG_Load("images/settings/probas_bloc1.png");
    SDL_Rect positionProbasBlocMetal={0,0,0,0};
    positionProbasBlocMetal.x=55;
    positionProbasBlocMetal.y=470;
    //////////SET MODE AFFICHAGE//////////////////////////
    SDL_Surface *ModeAffichage=NULL;
    ModeAffichage=IMG_Load("images/settings/mode_affichage2.png");
    SDL_Rect positionModeAffichage;
    positionModeAffichage.x=520;
    positionModeAffichage.y=205;

while (GestionMenus->continuer1)
    {
        FMOD_ChannelGroup_SetVolume(settings->Allsongs, settings->GlobalVolume);//règle le volume global

        SDL_Event event;

        SDL_PollEvent(&event);//Surveille les évènements sans bloquer l'éxécution du programme
        //////AFFICHAGE///////////////////////////////////////////////////////////////////////
        //////////SET MODE AFFICHAGE/////////////////////////
        if (settings->fullscreen==1){SDL_FreeSurface(ModeAffichage);   SDL_Surface *ModeAffichage=IMG_Load("images/settings/mode_affichage.png");}
        if (settings->fullscreen==0){SDL_FreeSurface(ModeAffichage);   SDL_Surface *ModeAffichage=IMG_Load("images/settings/mode_affichage2.png");}
        //////////IF PROBAS BLOC METAL/////////////////////////
        if (settings->probas_bloc_metal==0){SDL_FreeSurface(ProbasBlocMetal);   SDL_Surface *ProbasBlocMetal=IMG_Load("images/settings/probas_bloc1.png");}
        if (settings->probas_bloc_metal==1){SDL_FreeSurface(ProbasBlocMetal);   SDL_Surface *ProbasBlocMetal=IMG_Load("images/settings/probas_bloc2.png");}
        if (settings->probas_bloc_metal==2){SDL_FreeSurface(ProbasBlocMetal);   SDL_Surface *ProbasBlocMetal=IMG_Load("images/settings/probas_bloc3.png");}
        if (settings->probas_bloc_metal==3){SDL_FreeSurface(ProbasBlocMetal);   SDL_Surface *ProbasBlocMetal=IMG_Load("images/settings/probas_bloc4.png");}
        if (settings->probas_bloc_metal==4){SDL_FreeSurface(ProbasBlocMetal);   SDL_Surface *ProbasBlocMetal=IMG_Load("images/settings/probas_bloc5.png");}
        //////////IF PROBAS ONE UP/////////////////////////
        if (settings->probas_oneUP==0){SDL_FreeSurface(ProbasOneUP);   SDL_Surface *ProbasOneUP=IMG_Load("images/settings/probas_oneUP1.png");}
        if (settings->probas_oneUP==1){SDL_FreeSurface(ProbasOneUP);   SDL_Surface *ProbasOneUP=IMG_Load("images/settings/probas_oneUP2.png");}
        if (settings->probas_oneUP==2){SDL_FreeSurface(ProbasOneUP);   SDL_Surface *ProbasOneUP=IMG_Load("images/settings/probas_oneUP3.png");}
        if (settings->probas_oneUP==3){SDL_FreeSurface(ProbasOneUP);   SDL_Surface *ProbasOneUP=IMG_Load("images/settings/probas_oneUP4.png");}
        if (settings->probas_oneUP==4){SDL_FreeSurface(ProbasOneUP);   SDL_Surface *ProbasOneUP=IMG_Load("images/settings/probas_oneUP5.png");}
        //////////IF PROBAS POW/////////////////////////
        if (settings->probas_pow==0){SDL_FreeSurface(ProbasPow);   SDL_Surface *ProbasPow=IMG_Load("images/settings/probas_pow1.png");}
        if (settings->probas_pow==1){SDL_FreeSurface(ProbasPow);   SDL_Surface *ProbasPow=IMG_Load("images/settings/probas_pow2.png");}
        if (settings->probas_pow==2){SDL_FreeSurface(ProbasPow);   SDL_Surface *ProbasPow=IMG_Load("images/settings/probas_pow3.png");}
        if (settings->probas_pow==3){SDL_FreeSurface(ProbasPow);   SDL_Surface *ProbasPow=IMG_Load("images/settings/probas_pow4.png");}
        if (settings->probas_pow==4){SDL_FreeSurface(ProbasPow);   SDL_Surface *ProbasPow=IMG_Load("images/settings/probas_pow5.png");}
        //////////IF NB VIES INI/////////////////////////////
        if (settings->nbVies==0){SDL_FreeSurface(NombreVies);   SDL_Surface *NombreVies=IMG_Load("images/settings/nb_vies_ini0.png");}
        if (settings->nbVies==1){SDL_FreeSurface(NombreVies);   SDL_Surface *NombreVies=IMG_Load("images/settings/nb_vies_ini1.png");}
        if (settings->nbVies==2){SDL_FreeSurface(NombreVies);   SDL_Surface *NombreVies=IMG_Load("images/settings/nb_vies_ini2.png");}
        if (settings->nbVies==3){SDL_FreeSurface(NombreVies);   SDL_Surface *NombreVies=IMG_Load("images/settings/nb_vies_ini3.png");}
        //////////IF CHANGE MUSIC SET/////////////////////////
        if (settings->changeMusicSet==1){SDL_FreeSurface(ChangeMusicSet);   SDL_Surface *ChangeMusicSet=IMG_Load("images/settings/set_change_music1.png");}
        if (settings->changeMusicSet==2){SDL_FreeSurface(ChangeMusicSet);   SDL_Surface *ChangeMusicSet=IMG_Load("images/settings/set_change_music2.png");}
        if (settings->changeMusicSet==3){SDL_FreeSurface(ChangeMusicSet);   SDL_Surface *ChangeMusicSet=IMG_Load("images/settings/set_change_music3.png");}
        if (settings->changeMusicSet==4){SDL_FreeSurface(ChangeMusicSet);   SDL_Surface *ChangeMusicSet=IMG_Load("images/settings/set_change_music4.png");}
        if (settings->changeMusicSet==5){SDL_FreeSurface(ChangeMusicSet);   SDL_Surface *ChangeMusicSet=IMG_Load("images/settings/set_change_music5.png");}
        /////////////////////////////////////////////////////
        SDL_BlitSurface(GestionMenus->Menu, NULL, ecran, &GestionMenus->positionMenu);
        SDL_BlitSurface(VolumeBar, NULL, ecran, &positionVolumeBar);
        SDL_BlitSurface(CurseurVolumeBar, NULL, ecran, &positionCurseurVolumeBar);
        SDL_BlitSurface(ChangeMusicSet, NULL, ecran, &positionChangeMusicSet);
        SDL_BlitSurface(NombreVies, NULL, ecran, &positionVies);
        SDL_BlitSurface(ProbasPow, NULL, ecran, &positionProbasPow);
        SDL_BlitSurface(ProbasOneUP, NULL, ecran, &positionProbasOneUP);
        SDL_BlitSurface(ProbasBlocMetal, NULL, ecran, &positionProbasBlocMetal);
        SDL_BlitSurface(ModeAffichage, NULL, ecran, &positionModeAffichage);
        SDL_Flip(ecran); // Mise à jour de l'écran

        if (event.type==SDL_MOUSEBUTTONUP)//si action d'un des boutons de la souris
        {
            ////////////VOLUME///////////////
            if (event.button.x>=positionVolumeBar.x+90
                && event.button.x<=positionVolumeBar.x+positionVolumeBar.w-65
                && event.button.y>=positionVolumeBar.y
                && event.button.y<=positionVolumeBar.y+positionVolumeBar.h)//on vérifie s'il se situe sur le parametre volume
                {
                    positionCurseurVolumeBar.x=event.button.x-10;
                    settings->GlobalVolume=(positionCurseurVolumeBar.x-140)*0.004;
                }
            ///////////SET MUSIC CHANGE////////////
            if (event.button.x>=225
                && event.button.x<=254
                && event.button.y>=263
                && event.button.y<=positionChangeMusicSet.y+positionChangeMusicSet.h)
                {
                    settings->changeMusicSet=1;
                }
            if (event.button.x>=265
                && event.button.x<=294
                && event.button.y>=263
                && event.button.y<=positionChangeMusicSet.y+positionChangeMusicSet.h)
                {
                    settings->changeMusicSet=2;
                }
            if (event.button.x>=305
                && event.button.x<=334
                && event.button.y>=263
                && event.button.y<=positionChangeMusicSet.y+positionChangeMusicSet.h)
                {
                    settings->changeMusicSet=3;
                }
            if (event.button.x>=345
                && event.button.x<=374
                && event.button.y>=263
                && event.button.y<=positionChangeMusicSet.y+positionChangeMusicSet.h)
                {
                    settings->changeMusicSet=4;
                }
            if (event.button.x>=385
                && event.button.x<=414
                && event.button.y>=263
                && event.button.y<=positionChangeMusicSet.y+positionChangeMusicSet.h)
                {
                    settings->changeMusicSet=5;
                }
            ///////////NOMBRE VIES INITIALES////////////
            if (event.button.x>=265
                && event.button.x<=294
                && event.button.y>=300
                && event.button.y<=positionVies.y+positionVies.h)
                {
                    settings->nbVies=0;
                }
            if (event.button.x>=305
                && event.button.x<=334
                && event.button.y>=300
                && event.button.y<=positionVies.y+positionVies.h)
                {
                    settings->nbVies=1;
                }
            if (event.button.x>=345
                && event.button.x<=374
                && event.button.y>=300
                && event.button.y<=positionVies.y+positionVies.h)
                {
                    settings->nbVies=2;
                }
            if (event.button.x>=385
                && event.button.x<=414
                && event.button.y>=300
                && event.button.y<=positionVies.y+positionVies.h)
                {
                    settings->nbVies=3;
                }
            ///////////PROBAS POW////////////
            if (event.button.x>=225
                && event.button.x<=254
                && event.button.y>=363
                && event.button.y<=positionProbasPow.y+positionProbasPow.h)
                {
                    settings->probas_pow=0;
                }
            if (event.button.x>=265
                && event.button.x<=294
                && event.button.y>=363
                && event.button.y<=positionProbasPow.y+positionProbasPow.h)
                {
                    settings->probas_pow=1;
                }
            if (event.button.x>=305
                && event.button.x<=334
                && event.button.y>=363
                && event.button.y<=positionProbasPow.y+positionProbasPow.h)
                {
                    settings->probas_pow=2;
                }
            if (event.button.x>=345
                && event.button.x<=374
                && event.button.y>=363
                && event.button.y<=positionProbasPow.y+positionProbasPow.h)
                {
                    settings->probas_pow=3;
                }
            if (event.button.x>=385
                && event.button.x<=414
                && event.button.y>=363
                && event.button.y<=positionProbasPow.y+positionProbasPow.h)
                {
                    settings->probas_pow=4;
                }
            ///////////PROBAS ONE UP////////////
            if (event.button.x>=225
                && event.button.x<=254
                && event.button.y>=433
                && event.button.y<=positionProbasOneUP.y+positionProbasOneUP.h)
                {
                    settings->probas_oneUP=0;
                }
            if (event.button.x>=265
                && event.button.x<=294
                && event.button.y>=433
                && event.button.y<=positionProbasOneUP.y+positionProbasOneUP.h)
                {
                    settings->probas_oneUP=1;
                }
            if (event.button.x>=305
                && event.button.x<=334
                && event.button.y>=433
                && event.button.y<=positionProbasOneUP.y+positionProbasOneUP.h)
                {
                    settings->probas_oneUP=2;
                }
            if (event.button.x>=345
                && event.button.x<=374
                && event.button.y>=433
                && event.button.y<=positionProbasOneUP.y+positionProbasOneUP.h)
                {
                    settings->probas_oneUP=3;
                }
            if (event.button.x>=385
                && event.button.x<=414
                && event.button.y>=433
                && event.button.y<=positionProbasOneUP.y+positionProbasOneUP.h)
                {
                    settings->probas_oneUP=4;
                }
            ///////////PROBAS BLOC METAL////////////
            if (event.button.x>=225
                && event.button.x<=254
                && event.button.y>=493
                && event.button.y<=positionProbasBlocMetal.y+positionProbasBlocMetal.h)
                {
                    settings->probas_bloc_metal=0;
                }
            if (event.button.x>=265
                && event.button.x<=294
                && event.button.y>=493
                && event.button.y<=positionProbasBlocMetal.y+positionProbasBlocMetal.h)
                {
                    settings->probas_bloc_metal=1;
                }
            if (event.button.x>=305
                && event.button.x<=334
                && event.button.y>=493
                && event.button.y<=positionProbasBlocMetal.y+positionProbasBlocMetal.h)
                {
                    settings->probas_bloc_metal=2;
                }
            if (event.button.x>=345
                && event.button.x<=374
                && event.button.y>=493
                && event.button.y<=positionProbasBlocMetal.y+positionProbasBlocMetal.h)
                {
                    settings->probas_bloc_metal=3;
                }
            if (event.button.x>=385
                && event.button.x<=414
                && event.button.y>=493
                && event.button.y<=positionProbasBlocMetal.y+positionProbasBlocMetal.h)
                {
                    settings->probas_bloc_metal=4;
                }

            ///////////SET MODE AFFICHAGE////////////
            if (event.button.x>=580
                && event.button.x<=715
                && event.button.y>=205
                && event.button.y<=positionModeAffichage.y+positionModeAffichage.h)
                {
                    settings->fullscreen=1;
                    ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN | SDL_ASYNCBLIT );

                }
            if (event.button.x>=750
                && event.button.x<=885
                && event.button.y>=205
                && event.button.y<=positionModeAffichage.y+positionModeAffichage.h)
                {
                    settings->fullscreen=0;
                    ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT );
                }
        }

        switch(event.type)
        {
            case SDL_QUIT:
                GestionMenus->continuer1 = 0;
                GestionMenus->continuer = 0;
                SDL_FreeSurface(GestionMenus->Menu);
                SDL_FreeSurface(VolumeBar);
                SDL_FreeSurface(ProbasPow);
                SDL_FreeSurface(ProbasOneUP);
                SDL_FreeSurface(ChangeMusicSet);
                SDL_FreeSurface(ProbasBlocMetal);
                SDL_FreeSurface(ModeAffichage);
                write_settings(settings);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        SDL_FreeSurface(GestionMenus->Menu);
                        SDL_FreeSurface(VolumeBar);
                        SDL_FreeSurface(ProbasPow);
                        SDL_FreeSurface(ProbasOneUP);
                        SDL_FreeSurface(ChangeMusicSet);
                        SDL_FreeSurface(ProbasBlocMetal);
                        SDL_FreeSurface(ModeAffichage);
                        write_settings(settings);
                        break;
                    case SDLK_RETURN:
                        SDL_Delay(200);
                        GestionMenus->continuer1 = 0;
                        SDL_FreeSurface(GestionMenus->Menu);
                        SDL_FreeSurface(VolumeBar);
                        SDL_FreeSurface(ProbasPow);
                        SDL_FreeSurface(ProbasOneUP);
                        SDL_FreeSurface(ChangeMusicSet);
                        SDL_FreeSurface(ProbasBlocMetal);
                        SDL_FreeSurface(ModeAffichage);
                        write_settings(settings);
                        break;
                    default:
                    break;
                }
            default:
            break;
        }
    }
}
