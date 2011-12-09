/**
 * \file moteur.c
 * \brief Fichier contenant le moteur principal du jeu en lui-même, gestion du stage et collisions.
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

void Main_Engine(SDL_Surface *ecran, Menustruct *GestionMenus, Son *musique, Parametres *settings)//le moteur de jeu principal
{
    ////////////////Structure de données jeu///////////////////
    Informations infos;//définition d'une variable infos de structure Informations
    clean_donnees(&infos, settings); //On néttoie ses données.
    init_donnees(&infos, settings); //On initilase avec les données du jeu.
    //Chargement des sprites
    sprites_loading (&infos); //Les sprites sont chargés
    //Quelques positions de base définies :
    infos.posture_Mario = infos.Mario[STATIC];
    infos.posture_Donkey = infos.Donkey[DK_NORMAL];
    infos.posture_Peach = infos.Peach[PEACH1];
    //----------------------------------------------
    choose_song (&infos, musique); //Le son est choisit
    load_game_songs(musique); //Les bruitages sont chargés
    int first_time=0; //initialise une variable de debug

    while (GestionMenus->continuer1)
    //Boucle principale N°2 :
    //Couche MENU PAUSE.
    //Cette boucle est lancée dès le début du jeu mais n'est entierement lue qu'en cas de pression de la touche ECHAP afin d'atteindre le menu pause.
    {
        //////////////INITIALISATION STRUCTURE MENU PAUSE//////////////
        GestionMenus->positionMenu.x = 0;
        GestionMenus->positionMenu.y = 0;
        GestionMenus->positionPlay.x = 100;
        GestionMenus->positionPlay.y = 250;
        GestionMenus->positionQuit.x = 650;
        GestionMenus->positionQuit.y = 250;
        GestionMenus->positionReturn.x = 375;
        GestionMenus->positionReturn.y = 250;
        /////////////////////////////////////////////////////////
        SDL_Event event;

        while (GestionMenus->continuer2)
        //Boucle principale N°3 :
        //Couche JEU.
        //Cette boucle est lancée dès le début du jeu et est entierement lue qtant qu'il n'y a pas pression de la touche ECHAP, laquelle renvoie au menu pause.
        //C'est la boucle principale du moteur du jeu, là où sont lancées toutes les fonctions qui animent celui-ci.
        {

            ///////////////////TOOLBAR///////////////////////////////////////////////////////////
            ///////////////////////VOLUME////////////////////////////////////////////////////////
            if (event.type==SDL_MOUSEBUTTONUP)//si action d'un des boutons de la souris
            {
                ////////////VOLUME///////////////
                if (event.button.x>=80
                    && event.button.x<=270
                    && event.button.y>=infos.positionToolbar.y+10
                    && event.button.y<=infos.positionToolbar.y+40)//on vérifie s'il se situe sur le parametre volume
                    {
                        infos.positionCurseurVolume.x=event.button.x;
                        settings->GlobalVolume=(infos.positionCurseurVolume.x-80)*0.0054;
                    }
            }

            if (event.type==SDL_MOUSEBUTTONUP)//si action d'un des boutons de la souris
            {
            ////////////FULLSCREEN///////////////
                if (event.button.x>=980
                    && event.button.x<=995
                    && event.button.y>=infos.positionToolbar.y+10
                    && event.button.y<=infos.positionToolbar.y+40)//on vérifie s'il se situe sur le bouton no fullscreen
                    {
                        if (settings->fullscreen==1)
                        {
                            ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT );
                            settings->fullscreen = 0;
                        }
                    }
                if (event.button.x>=860
                    && event.button.x<=875
                    && event.button.y>=infos.positionToolbar.y+10
                    && event.button.y<=infos.positionToolbar.y+40)//on vérifie s'il se situe sur le bouton fullscreen
                    {
                        if (settings->fullscreen==0)
                        {
                            ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF| SDL_FULLSCREEN | SDL_ASYNCBLIT );
                            settings->fullscreen = 1;
                        }
                    }
            }

            FMOD_ChannelGroup_SetVolume(settings->Allsongs, settings->GlobalVolume); //Définie le volume grace à la valeur définie dans la structure paramètres.
            /////////////////////////MUSIQUE/////////////////////////////////////////////////////
            if (FMOD_Channel_IsPlaying (musique->canal_deux, &musique->isplayingsound) !=FMOD_OK)
            {
                FMOD_Channel_SetPaused(musique->canal_un, 0);
                FMOD_Channel_SetPaused(musique->canal_trois, 0);
            }

            if (infos.pauseMenu == 1)
            {
                FMOD_Sound_Release(musique->pause);
                infos.pauseMenu=0;
            }
            //////////////////////////////////////////////////////////////////////////////////////
            SDL_PollEvent(&event);//Surveille les évènements sans bloquer l'éxécution du programme
            //Lancements des fonctions de jeu
            sprintf(infos.score_string, "%d", infos.score); //convertit int score en string
            sprintf(infos.level_string, "%d", infos.level);//convertit int level en string

            if (infos.loose!=1 && infos.game_over!=1 && infos.flags!=0)//empêche le jeu de tourner en cas de mort/victoire
            {
                check_if_pow(&infos, musique); //Verifie si le pow est actif ou non et gere l'affichage qui en resulte, ainsi que la duree de ses effets.
                Peach_engine (&infos);//Fonction permettant l'affichage aléatoire de la bulle HELP de Peach
                DonkeyKong_Engine(&infos);//Fonction générant les attaques aléatoires de Donkey
                Projectiles_Engine (&infos);//Fonction générant le mouvement des projectiles générés par Donkey
                Collision_Engine (ecran, &infos, musique);//Fonction générant les collisions avec les projectiles et differents objets
                if (first_time==0){infos.loose=0; infos.game_over=0;} //debug la mort dès le lancement du jeu alors qu'elle n'a pas lieu d'être
                first_time=1; //Fin debug
                found_floor(ecran, &infos, musique, settings);//Fonction déterminant la conduite à adopter en fonction de l'étage détecté. Appel les fonctions manage_floor et manage_scale
            }
            Next_level (ecran, &infos, musique, settings);//Fonction qui vérifie la réussite du niveau et renvoie au niveau suivant si tel est le cas
            Game_Over(ecran, &infos, musique, settings);//Fonction qui vérifie si une collions à été détectée, et affiche alors l'ecran correspondant.
            //Gestion nombre de vies et de l'affichage :
            if (infos.vies>3){infos.vies=3; infos.NbVies = infos.Vies[TROIS_VIES];}
            if (infos.vies==3){infos.NbVies = infos.Vies[TROIS_VIES];}
            if (infos.vies==2){infos.NbVies = infos.Vies[DEUX_VIES];}
            if (infos.vies==1){infos.NbVies = infos.Vies[UNE_VIE];}
            if (infos.vies==0){infos.NbVies = infos.Vies[ZERO_VIE];}

                /////////////////GESTION TOUCHES POUR ATTEINDRE LE MENU PAUSE////////////////////
                switch(event.type) //On surveille les évenements
                {
                    case SDL_QUIT: //Si la souris a cliquée sur la croix :
                        GestionMenus->continuer2 = 0; //On quite le jeu
                        GestionMenus->continuer1 = 0; //On la boucle de l'écran de pause
                        GestionMenus->continuer = 0; //On quitte la boucle principale (le menu du programme)
                        free_game_songs (musique); //On désalloue la mémoire octroyé aux sons et leurs variables.
                        break;
                    case SDL_KEYDOWN: //Si une touche est enfoncée
                        switch (event.key.keysym.sym) //On surveille de quelle touche il s'agit
                        {
                            case SDLK_ESCAPE: //Si c'est la touche ECHAP :
                                if (infos.loose!=1 && infos.flags!=0)//desactive l'accès au menu pause sur l'ecran de fin niveau/You loose
                                {
                                    ////////////////////SON PAUSE////////////////////////////
                                    FMOD_System_CreateSound(musique->system, "sons/pause.mp3", FMOD_CREATESAMPLE, 0, &musique->pause);
                                    FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->pause, 0, &musique->canal_quatre);
                                    ///////////////////////////////////////////////////////////
                                    SDL_Delay(200);
                                    GestionMenus->continuer2 = 0; //On quitte la boucle de jeu, on passe de la couche 3 à 2.
                                }
                                break;
                            default: //Si c'est une autre touche, il ne se passe rien
                            GestionMenus->continuer2 = 1;
                            break;
                        }
                    default: //Si c'est un autre évenement, rien ne se passe.
                    break;
                }
            ///////////////////FIN GESTION TOUCHES POUR ATTEINDRE LE MENU PAUSE///////////////////
        }
    ///////////////////////MENU PAUSE////////////////////////
    pause_menu(ecran, GestionMenus, &infos, musique); //Appel de la fonction gérant le menu pause
    }
}

void manage_floor(SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);//Contiendra l'état d'une touche (enfoncée ou non)

            if ( keystate[SDLK_RIGHT]&&infos->positionMario.x<=900 && !keystate[SDLK_LEFT]) //SI flèche de droite enfoncée
            {
            move_right (infos); //La fonction de gestion du déplacement du personnage vers la droite est appellée.
            change_frame_right(infos, ecran); //La fonction de gestion de l'animation de déplacement est appellée.
            }

            if ( keystate[SDLK_LEFT]&&infos->positionMario.x>=27 && !keystate[SDLK_RIGHT]) //SI flèche de gauche enfoncée
            {
            move_left (infos);//La fonction de gestion du déplacement du personnage vers la gauche est appellée.
            change_frame_left(infos, ecran);//La fonction de gestion de l'animation de déplacement est appellée.
            }

            if ( keystate[SDLK_SPACE]) //SI espace enfoncée
            {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->jump, 0, &musique->canal_jump); //On joue un son
            jump(ecran, infos, musique, settings); //La fonction de gestion du saut est appelée
            }

            if ( ( !keystate[SDLK_DOWN] //Si aucune touche n'est enfoncée
                  &&!keystate[SDLK_UP] //...
                  &&!keystate[SDLK_RIGHT] //...
                  && !keystate[SDLK_LEFT] //...
                  && !keystate[SDLK_SPACE] //...
                 )
                || infos->positionMario.x<=26 //Et que mario ne fait pas une tentative de suicide sur les bords...
                || infos->positionMario.x>=900) //...
            {
            infos->sens=0; //Le sens de déplacement de mario est remis à 0
            infos->posture_Mario = infos->Mario[STATIC]; //La posture de mario revient à celle de base (face)
            MAJ_Affichage(infos, ecran); //L'écran est mis à jour
            }

            /////DEBUG MULTI TOUCHES//////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if ( ( (keystate[SDLK_UP]
                    || keystate[SDLK_DOWN])
                  && (!keystate[SDLK_RIGHT]
                      && !keystate[SDLK_LEFT]
                      && !keystate[SDLK_SPACE]) )
                  || ( keystate[SDLK_RIGHT]
                      && keystate[SDLK_LEFT] ) )
                    {
                        infos->posture_Mario=infos->Mario[STATIC]; MAJ_Affichage(infos, ecran); //Mario est affiché en position de base (de face)
                    }
            ///////////FIN DEBUG//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ////////////////////////GESTION ECHELLES/////////////////////////////////
            /////////////////////////////ETAGE 1 à 2/////////////////////////////////
            ///////////////////////////////ECHELLE 1/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_ONE && infos->positionMario.x<=X_MAX_SCALE_ONE && infos->current_floor==ETAGE_UN )
            {
            //Si la touche UP est enfoncée alors que Mario est à l'étage UN et près de l'echelle N°1 :
            infos->current_floor=ECHELLE_UNE; //On définit la position de Mario comme étant sur l'echelle N°1
            MAJ_Affichage(infos, ecran); //on met à jour l'écran
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_ONE && infos->positionMario.x<=X_MAX_SCALE_ONE && infos->current_floor==ETAGE_DEUX )
            {
            //Si la touche DOWN est enfoncée alors que Mario est à l'étage DEUX et près de l'echelle N°1 :
            infos->current_floor=ECHELLE_UNE; //On définit la position de Mario comme étant sur l'echelle N°1
            MAJ_Affichage(infos, ecran); //on met à jour l'écran
            }
            //Ainsi de suite pour chaque echelle...
            /////////////////////////////ETAGE 2 à 3/////////////////////////////////
            ///////////////////////////////ECHELLE 2/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_TWO && infos->positionMario.x<=X_MAX_SCALE_TWO && infos->current_floor==ETAGE_DEUX )
            {
            infos->current_floor=ECHELLE_DEUX;
            MAJ_Affichage(infos, ecran);
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_TWO && infos->positionMario.x<=X_MAX_SCALE_TWO && infos->current_floor==ETAGE_TROIS )
            {
            infos->current_floor=ECHELLE_DEUX;
            MAJ_Affichage(infos, ecran);
            }
            ///////////////////////////////ECHELLE 3/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_THREE && infos->positionMario.x<=X_MAX_SCALE_THREE && infos->current_floor==ETAGE_DEUX )
            {
            infos->current_floor=ECHELLE_TROIS;
            MAJ_Affichage(infos, ecran);
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_THREE && infos->positionMario.x<=X_MAX_SCALE_THREE && infos->current_floor==ETAGE_TROIS )
            {
            infos->current_floor=ECHELLE_TROIS;
            MAJ_Affichage(infos, ecran);
            }
            /////////////////////////////ETAGE 3 à 4/////////////////////////////////
            ///////////////////////////////ECHELLE 4/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_FOUR && infos->positionMario.x<=X_MAX_SCALE_FOUR && infos->current_floor==ETAGE_TROIS )
            {
            infos->current_floor=ECHELLE_QUATRE;
            MAJ_Affichage(infos, ecran);
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_FOUR && infos->positionMario.x<=X_MAX_SCALE_FOUR && infos->current_floor==ETAGE_QUATRE )
            {
            infos->current_floor=ECHELLE_QUATRE;
            MAJ_Affichage(infos, ecran);
            }
            ///////////////////////////////ECHELLE 5/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_FIVE && infos->positionMario.x<=X_MAX_SCALE_FIVE && infos->current_floor==ETAGE_TROIS )
            {
            infos->current_floor=ECHELLE_CINQ;
            MAJ_Affichage(infos, ecran);
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_FIVE && infos->positionMario.x<=X_MAX_SCALE_FIVE && infos->current_floor==ETAGE_QUATRE )
            {
            infos->current_floor=ECHELLE_CINQ;
            MAJ_Affichage(infos, ecran);
            }
            /////////////////////////////ETAGE 4 à 5/////////////////////////////////
            ///////////////////////////////ECHELLE 6/////////////////////////////////
            if ( keystate[SDLK_UP] && infos->positionMario.x>=X_MIN_SCALE_SIX && infos->positionMario.x<=X_MAX_SCALE_SIX && infos->current_floor==ETAGE_QUATRE )
            {
            infos->current_floor=ECHELLE_SIX;
            MAJ_Affichage(infos, ecran);
            }

            if ( keystate[SDLK_DOWN] && infos->positionMario.x>=X_MIN_SCALE_SIX && infos->positionMario.x<=X_MAX_SCALE_SIX && infos->current_floor==ETAGE_CINQ )
            {
            infos->current_floor=ECHELLE_SIX;
            MAJ_Affichage(infos, ecran);
            }
            ////////////////////////FIN GESTION ECHELLES//////////////////////////////
}

void manage_scale(Informations *infos, SDL_Surface *ecran, Son *musique)
{
    Uint8 *keystate = SDL_GetKeyState(NULL);//Contiendra l'état d'une touche (enfoncée ou non)
    infos->posture_Mario = infos->Mario[CLIMBING]; //La posture de mario est modifiée pour celle en train de monter une echelle


    //On continue de mettre à jour l'écran même s'il n'y a pas d'action afin de ne pas bloquer le jeu :
    if (!keystate[SDLK_UP] && !keystate[SDLK_DOWN]) { MAJ_Affichage(infos, ecran); }

    if (keystate[SDLK_UP]) //Si la touche UP est enfoncée :
    {
        infos->positionMario.y-= infos->vitesse_Mario; //On incrémente la position verticale de Mario (décrèmenter y fais monter Mario)
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
    }

    if (keystate[SDLK_DOWN])//Si la touche DOWN est enfoncée :
    {
        infos->positionMario.y+= infos->vitesse_Mario; //On décrémente la position verticale de Mario (incrèmenter y fais descendre Mario)
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
    }

    if  (infos->positionMario.y <= infos->scaleHeight.ymax)//Une fois Mario au dessus de l'echelle
    {
        if (infos->current_floor==ECHELLE_UNE) //S'il était sur l'echelle N°1
        {
        infos->current_floor = ETAGE_DEUX; //Il est maintenant sur l'étage N°2
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
        }

        if (infos->current_floor==ECHELLE_DEUX) //S'il était sur l'echelle N°2
        {
        infos->current_floor = ETAGE_TROIS; //Il est maintenant sur l'étage N°3
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
        }
        //...AINSI DE SUITE POUR CHAQUE ECHELLE...
        if (infos->current_floor==ECHELLE_TROIS)
        {
        infos->current_floor = ETAGE_TROIS;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_QUATRE)
        {
        infos->current_floor = ETAGE_QUATRE;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_CINQ)
        {
        infos->current_floor = ETAGE_QUATRE;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_SIX)
        {
        infos->current_floor = ETAGE_CINQ;
        MAJ_Affichage(infos, ecran);
        }
    }

    if  (infos->positionMario.y >= infos->scaleHeight.ymin) //Ou une fois Mario en dessous de l'echelle
    {
        if (infos->current_floor==ECHELLE_UNE) //S'il était sur l'echelle N°1
        {
        infos->current_floor = ETAGE_UN; //Il est maintenant sur l'étage N°1
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
        }

        if (infos->current_floor==ECHELLE_DEUX) //S'il était sur l'echelle N°2
        {
        infos->current_floor = ETAGE_DEUX; //Il est maintenant sur l'étage N°2
        MAJ_Affichage(infos, ecran); //On met à jour l'écran
        }
        //...AINSI DE SUITE POUR CHAQUE ECHELLE...
        if (infos->current_floor==ECHELLE_TROIS)
        {
        infos->current_floor = ETAGE_DEUX;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_TROIS)
        {
        infos->current_floor = ETAGE_QUATRE;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_QUATRE)
        {
        infos->current_floor = ETAGE_TROIS;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_CINQ)
        {
        infos->current_floor = ETAGE_TROIS;
        MAJ_Affichage(infos, ecran);
        }

        if (infos->current_floor==ECHELLE_SIX)
        {
        infos->current_floor = ETAGE_QUATRE;
        MAJ_Affichage(infos, ecran);
        }
    }
}

void Collision_Engine (SDL_Surface *ecran, Informations *infos, Son *musique)
{
    //On définit le cadre correspondant à la zone de collision considèrée comme appartenant au personnage principal :
    int zoneMariox1 = infos->positionMario.x + infos->positionMario.w/10;
    int zoneMariox2 = infos->positionMario.x + infos->positionMario.w*9/10;
    int zoneMarioy1 = infos->positionMario.y;
    int zoneMarioy2 = infos->positionMario.y + infos->positionMario.w;
    ///////////////OBJETS///////////////////////////////////////////////////////////////////
    /////////////Objet Flags//////////////////
    //On détermine le centre de l'objet :
    int CentreFlagsx = infos->positionFlags.w/2 + infos->positionFlags.x;
    int CentreFlagsy = infos->positionFlags.h/2 + infos->positionFlags.y;

    if (  ( zoneMariox1 <= CentreFlagsx ) && ( zoneMariox2 >= CentreFlagsx ) && infos->current_floor==ETAGE_CINQ )
    { //Si les coordonnées du centre de l'objet rentre dans la zone horizontale de collision de Mario, et que Mario est sur l'étage où est l'objet :
        if ( ( zoneMarioy1 <= CentreFlagsy ) && ( zoneMarioy2 >= CentreFlagsy ) ) //On vérifie que l'objet est dans la zone verticale de collision de Mario également
        {
            infos->flags=0; //Alors l'objet est pris
        }
        else{void();} //Sinon Rien
    }
    /////////////Objet Flower//////////////////
    int CentreFlowerx = infos->positionFlower.w/2 + infos->positionFlower.x;
    int CentreFlowery = infos->positionFlower.h/2 + infos->positionFlower.y;

    if (  ( zoneMariox1 <= CentreFlowerx ) && ( zoneMariox2 >= CentreFlowerx ) && infos->current_floor==ETAGE_DEUX  && infos->flower==1 )
    { //Si les coordonnées du centre de l'objet rentre dans la zone horizontale de collision de Mario, et que Mario est sur l'étage où est l'objet :
        if ( ( zoneMarioy1 <= CentreFlowery ) && ( zoneMarioy2 >= CentreFlowery ) ) //On vérifie que l'objet est dans la zone verticale de collision de Mario également
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items); //On joue un son
            infos->flower=0; //On détruit l'objet
            infos->score+=1500; //On up le score
        }
        else{void();}
    }
    //////////////////////////////////////////

    //...AINSI DE SUITE POUR CHAQUE OBJET BONUS...VOIR POUR PROJECTILES PLUS BAS...

    /////////////Objet Champi//////////////////
    int CentreChampix = infos->positionChampi.w/2 + infos->positionChampi.x;
    int CentreChampiy = infos->positionChampi.h/2 + infos->positionChampi.y;

    if (  ( zoneMariox1 <= CentreChampix ) && ( zoneMariox2 >= CentreChampix ) && infos->current_floor==ETAGE_CINQ && infos->champi==1 )
    {
        if ( ( zoneMarioy1 <= CentreChampiy ) && ( zoneMarioy2 >= CentreChampiy ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->one_up, 0, &musique->canal_items);
            infos->champi=0;
            infos->vies++;
            infos->score+=7000;
        }
        else{void();}
    }
    /////////////Objet Pow//////////////////
    int CentrePowx = infos->positionPow.w/2 + infos->positionPow.x;
    int CentrePowy = infos->positionPow.h/2 + infos->positionPow.y;

    if (  ( zoneMariox1 <= CentrePowx ) && ( zoneMariox2 >= CentrePowx ) && infos->current_floor==ETAGE_QUATRE && infos->pow==1 )
    {
        if ( ( zoneMarioy1 <= CentrePowy ) && ( zoneMarioy2 >= CentrePowy ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->pow, 0, &musique->canal_trois);
            free_surfaces_Persos_and_reattribute(ecran, infos);
            infos->pow=0;
            infos->score+=6000;
            infos->pow_activ=1;
            infos->compteur_pow_activ=0;
        }
        else{void();}
    }
    /////////////Objet Bowser//////////////////
    int CentreBowserx = infos->positionBowser.w/2 + infos->positionBowser.x;
    int CentreBowsery = infos->positionBowser.h/2 + infos->positionBowser.y;

    if (  ( zoneMariox1 <= CentreBowserx ) && ( zoneMariox2 >= CentreBowserx ) && infos->current_floor==ETAGE_CINQ  && infos->bowser==1 )
    {
        if ( ( zoneMarioy1 <= CentreBowsery ) && ( zoneMarioy2 >= CentreBowsery ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items);
            infos->bowser=0;
            infos->score+=3000;
        }
        else{void();}
    }
    /////////////Objet Skelerex//////////////////
    int CentreSkelerexx = infos->positionSkelerex.w/2 + infos->positionSkelerex.x;
    int CentreSkelerexy = infos->positionSkelerex.h/2 + infos->positionSkelerex.y;

    if (  ( zoneMariox1 <= CentreSkelerexx ) && ( zoneMariox2 >= CentreSkelerexx ) && infos->current_floor==ETAGE_TROIS  && infos->skelerex==1 )
    {
        if ( ( zoneMarioy1 <= CentreSkelerexy ) && ( zoneMarioy2 >= CentreSkelerexy ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items);
            infos->skelerex=0;
            infos->score+=2500;
        }
        else{void();}
    }
    /////////////Objet Yoshi//////////////////
    int CentreYoshix = infos->positionYoshi.w/2 + infos->positionYoshi.x;
    int CentreYoshiy = infos->positionYoshi.h/2 + infos->positionYoshi.y;

    if (  ( zoneMariox1 <= CentreYoshix ) && ( zoneMariox2 >= CentreYoshix ) && infos->current_floor==ETAGE_QUATRE  && infos->yoshi==1 )
    {
        if ( ( zoneMarioy1 <= CentreYoshiy ) && ( zoneMarioy2 >= CentreYoshiy ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items);
            infos->yoshi=0;
            infos->score+=4500;
        }
        else{void();}
    }
    /////////////Objet Pieuvre//////////////////
    int CentrePieuvrex = infos->positionPieuvre.w/2 + infos->positionPieuvre.x;
    int CentrePieuvrey = infos->positionPieuvre.h/2 + infos->positionPieuvre.y;

    if (  ( zoneMariox1 <= CentrePieuvrex ) && ( zoneMariox2 >= CentrePieuvrex ) && infos->current_floor==ETAGE_DEUX  && infos->pieuvre==1 )
    {
        if ( ( zoneMarioy1 <= CentrePieuvrey ) && ( zoneMarioy2 >= CentrePieuvrey ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items);
            infos->pieuvre=0;
            infos->score+=1000;
        }
        else{void();}
    }
    /////////////Objet Bloc Metal//////////////////
    int CentreBlocmetalx = infos->positionBlocmetal.w/2 + infos->positionBlocmetal.x;
    int CentreBlocmetaly = infos->positionBlocmetal.h/2 + infos->positionBlocmetal.y;

    if (  ( zoneMariox1 <= CentreBlocmetalx ) && ( zoneMariox2 >= CentreBlocmetalx ) && infos->current_floor==ETAGE_TROIS  && infos->blocmetal==1 )
    {
        if ( ( zoneMarioy1 <= CentreBlocmetaly ) && ( zoneMarioy2 >= CentreBlocmetaly ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_up, 0, &musique->canal_items);
            infos->blocmetal=0;
            infos->score+=5000;
            infos->metal=1;
            free_surfaces_Persos_and_reattribute(ecran, infos);
        }
        else{void();}
    }
    /////////////Objet Champvolant//////////////////
    int CentreChampvolantx = infos->positionChampvolant.w/2 + infos->positionChampvolant.x;
    int CentreChampvolanty = infos->positionChampvolant.h/2 + infos->positionChampvolant.y;

    if (  ( zoneMariox1 <= CentreChampvolantx ) && ( zoneMariox2 >= CentreChampvolantx ) && infos->current_floor==ETAGE_TROIS  && infos->champvolant==1 )
    {
        if ( ( zoneMarioy1 <= CentreChampvolanty ) && ( zoneMarioy2 >= CentreChampvolanty ) )
        {
            FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->items, 0, &musique->canal_items);
            infos->champvolant=0;
            infos->score+=2800;
        }
        else{void();}
    }
    //////////FIN OBJETS//////////////////////////////////////////////

    /////////PROJECTILES//////////////////////////////////////////////

    /////////////Tonneau1//////////////////
    //On détermine les coordonnées centrales du projectile :
    int CentreTonneaux = infos->positionTonneau.w/2 + infos->positionTonneau.x;
    int CentreTonneauy = infos->positionTonneau.h/2 + infos->positionTonneau.y;

    if (infos->metal!=1) //Si le pouvoir METAL n'est pas actif
    {
        if (  ( zoneMariox1 <= CentreTonneaux ) && ( zoneMariox2 >= CentreTonneaux ) ) //Si les coordonnées du centre de l'objet rentre dans la zone horizontale de collision de Mario
        {
            if ( ( zoneMarioy1 <= CentreTonneauy ) && ( zoneMarioy2 >= CentreTonneauy ) ) //On vérifie que l'objet est dans la zone verticale de collision de Mario également
            {
                infos->loose=1; //L'écran de défaite sera affiché dès que possible
                if (infos->vies==0){infos->game_over=1;} //S'il ne restais plus de vie au héros, l'écran GAME OVER sera affiché dès que possible
            }
            else{void();}
        }
    }
    if (infos->metal==1) //Si le pouvoir METAL est actif
     {
        if (  ( zoneMariox1 <= CentreTonneaux ) && ( zoneMariox2 >= CentreTonneaux ) )                                        //Si Mario
        {                                                                                                                    //Entre en contact
            if ( ( zoneMarioy1 <= CentreTonneauy ) && ( zoneMarioy2 >= CentreTonneauy ) )                                   //Avec le projectile
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items); //Un son est joué
                infos->metal=0;                                                                                          //le pouvoir est désactivé
                free_surfaces_Persos_and_reattribute(ecran, infos);                                                     //Les surfaces réatribuées
                infos->tonneau=0;                                                                                      //Le projectile détruit
                infos->positionTonneau.x=7500;                                                                        //La position du projectile réinitialisée
                infos->positionTonneau.y=7500;                                                                       //au delà de la surface de jeu

            }
            else{void();}
        }
    }
    ///////////////////////////////////////

    //...AINSI DE SUITE POUR CHAQUE PROJECTILE...

    /////////////Tonneau2//////////////////
    int CentreTonneau2x = infos->positionTonneau2.w/2 + infos->positionTonneau2.x;
    int CentreTonneau2y = infos->positionTonneau2.h/2 + infos->positionTonneau2.y;

    if (infos->metal!=1)
    {
        if (  ( zoneMariox1 <= CentreTonneau2x ) && ( zoneMariox2 >= CentreTonneau2x ) )
        {
            if ( ( zoneMarioy1 <= CentreTonneau2y ) && ( zoneMarioy2 >= CentreTonneau2y ) )
            {
                infos->loose=1;
                if (infos->vies==0){infos->game_over=1;}
            }
            else{void();}
        }
    }
    if (infos->metal==1)
     {
        if (  ( zoneMariox1 <= CentreTonneau2x ) && ( zoneMariox2 >= CentreTonneau2x ) )
        {
            if ( ( zoneMarioy1 <= CentreTonneau2y ) && ( zoneMarioy2 >= CentreTonneau2y ) )
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items);
                infos->metal=0;
                free_surfaces_Persos_and_reattribute(ecran, infos);
                infos->tonneau2=0;
                infos->positionTonneau2.x=8000;
                infos->positionTonneau2.y=8000;

            }
            else{void();}
        }
    }

    /////////////Tonneau3//////////////////
    int CentreTonneau3x = infos->positionTonneau3.w/2 + infos->positionTonneau3.x;
    int CentreTonneau3y = infos->positionTonneau3.h/2 + infos->positionTonneau3.y;

    if (infos->metal!=1)
    {
        if (  ( zoneMariox1 <= CentreTonneau3x ) && ( zoneMariox2 >= CentreTonneau3x ) )
        {
            if ( ( zoneMarioy1 <= CentreTonneau3y ) && ( zoneMarioy2 >= CentreTonneau3y ) )
            {
                infos->loose=1;
                if (infos->vies==0){infos->game_over=1;}
            }
            else{void();}
        }
    }
    if (infos->metal==1)
     {
        if (  ( zoneMariox1 <= CentreTonneau3x ) && ( zoneMariox2 >= CentreTonneau3x ) )
        {
            if ( ( zoneMarioy1 <= CentreTonneau3y ) && ( zoneMarioy2 >= CentreTonneau3y ) )
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items);
                infos->metal=0;
                free_surfaces_Persos_and_reattribute(ecran, infos);
                infos->tonneau3=0;
                infos->positionTonneau3.x=8500;
                infos->positionTonneau3.y=8500;

            }
            else{void();}
        }
    }
    ///////////////////////////////////////
    /////////////Carapace//////////////////
    int CentreCarapacex = infos->positionCarapace.w/2 + infos->positionCarapace.x;
    int CentreCarapacey = infos->positionCarapace.h/2 + infos->positionCarapace.y;

    if (infos->metal!=1)
    {
        if (  ( zoneMariox1 <= CentreCarapacex ) && ( zoneMariox2 >= CentreCarapacex ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapacey ) && ( zoneMarioy2 >= CentreCarapacey ) )
            {
                infos->loose=1;
                if (infos->vies==0){infos->game_over=1;}
            }
            else{void();}
        }
    }
    if (infos->metal==1)
     {
        if (  ( zoneMariox1 <= CentreCarapacex ) && ( zoneMariox2 >= CentreCarapacex ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapacey ) && ( zoneMarioy2 >= CentreCarapacey ) )
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items);
                infos->metal=0;
                free_surfaces_Persos_and_reattribute(ecran, infos);
                infos->carapace=0;
                infos->positionCarapace.x=9000;
                infos->positionCarapace.y=9000;
            }
            else{void();}
        }
     }
    /////////////Carapace2//////////////////
    int CentreCarapace2x = infos->positionCarapace2.w/2 + infos->positionCarapace2.x;
    int CentreCarapace2y = infos->positionCarapace2.h/2 + infos->positionCarapace2.y;

    if (infos->metal!=1)
    {
        if (  ( zoneMariox1 <= CentreCarapace2x ) && ( zoneMariox2 >= CentreCarapace2x ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapace2y ) && ( zoneMarioy2 >= CentreCarapace2y ) )
            {
                infos->loose=1;
                if (infos->vies==0){infos->game_over=1;}
            }
            else{void();}
        }
    }
    if (infos->metal==1)
     {
        if (  ( zoneMariox1 <= CentreCarapace2x ) && ( zoneMariox2 >= CentreCarapace2x ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapace2y ) && ( zoneMarioy2 >= CentreCarapace2y ) )
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items);
                infos->metal=0;
                free_surfaces_Persos_and_reattribute(ecran, infos);
                infos->carapace2=0;
                infos->positionCarapace2.x=9500;
                infos->positionCarapace2.y=9500;
            }
            else{void();}
        }
     }
    /////////////Carapace3//////////////////
    int CentreCarapace3x = infos->positionCarapace3.w/2 + infos->positionCarapace3.x;
    int CentreCarapace3y = infos->positionCarapace3.h/2 + infos->positionCarapace3.y;

    if (infos->metal!=1)
    {
        if (  ( zoneMariox1 <= CentreCarapace3x ) && ( zoneMariox2 >= CentreCarapace3x ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapace3y ) && ( zoneMarioy2 >= CentreCarapace3y ) )
            {
                infos->loose=1;
                if (infos->vies==0){infos->game_over=1;}
            }
            else{void();}
        }
    }
    if (infos->metal==1)
     {
        if (  ( zoneMariox1 <= CentreCarapace3x ) && ( zoneMariox2 >= CentreCarapace3x ) )
        {
            if ( ( zoneMarioy1 <= CentreCarapace3y ) && ( zoneMarioy2 >= CentreCarapace3y ) )
            {
                FMOD_System_PlaySound(musique->system, FMOD_CHANNEL_FREE, musique->power_down, 0, &musique->canal_items);
                infos->metal=0;
                free_surfaces_Persos_and_reattribute(ecran, infos);
                infos->carapace3=0;
                infos->positionCarapace3.x=10000;
                infos->positionCarapace3.y=10000;
            }
            else{void();}
        }
     }
    ///////////////////////////////////////
}

void found_floor(SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
{
    if (infos->current_floor==ETAGE_UN)//Si étage actuel est UN
            {
                infos->typepente=TYPE_1; //Montée
                manage_floor(ecran, infos, musique, settings);//On lance la gestion des déplacement de Mario sur le premier étage du stage

            }

            if (infos->current_floor==ETAGE_DEUX)//Si étage actuel est DEUX
            {
                infos->typepente=TYPE_2; //Descente
                manage_floor(ecran, infos, musique, settings);//On lance la gestion des déplacement de Mario sur le deuxieme étage du stage

            }

            if (infos->current_floor==ETAGE_TROIS)//Si étage actuel est TROIS
            {
                infos->typepente=TYPE_1; //Montée
                manage_floor(ecran, infos, musique, settings);//On lance la gestion des déplacement de Mario sur le troisieme étage du stage

            }

            if (infos->current_floor==ETAGE_QUATRE)//Si étage actuel est QUATRE
            {
                infos->typepente=TYPE_2; //Montée
                manage_floor(ecran, infos, musique, settings);//On lance la gestion des déplacement de Mario sur le quatrieme étage du stage

            }

            if (infos->current_floor==ETAGE_CINQ)//Si étage actuel est CINQ
            {
                infos->typepente=TYPE_3; //Plat
                manage_floor(ecran, infos, musique, settings);//On lance la gestion des déplacement de Mario sur le cinquieme étage du stage

            }

            if (infos->current_floor==ECHELLE_UNE) //Si Mario est sur l'echelle N°1 :
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_ONE;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_ONE;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_ONE + X_MIN_SCALE_ONE)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }

            if (infos->current_floor==ECHELLE_DEUX) //Si Mario est sur l'echelle N°2 :
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_TWO;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_TWO;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_TWO+X_MIN_SCALE_TWO)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }

            if (infos->current_floor==ECHELLE_TROIS) //Si Mario est sur l'echelle N°3 :
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_THREE;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_THREE;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_THREE+X_MIN_SCALE_THREE)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }

            if (infos->current_floor==ECHELLE_QUATRE) //Si Mario est sur l'echelle N°4 :
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_FOUR;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_FOUR;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_FOUR+X_MIN_SCALE_FOUR)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }

            if (infos->current_floor==ECHELLE_CINQ) //Si Mario est sur l'echelle N°5 :
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_FIVE;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_FIVE;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_FIVE+X_MIN_SCALE_FIVE)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }

            if (infos->current_floor==ECHELLE_SIX)
            {
                infos->scaleHeight.ymin=Y_MIN_SCALE_SIX;//positionMario.y à atteindre pour redescendre d'un niveau
                infos->scaleHeight.ymax=Y_MAX_SCALE_SIX;//positionMario.y à atteindre pour remonter d'un niveau
                infos->positionMario.x=(X_MAX_SCALE_SIX+X_MIN_SCALE_SIX)/2; //On centre Mario horizontalement par rapport à l'echelle
                manage_scale(infos, ecran, musique); //On lance la gestion des déplacements de Mario sur l'echelle
            }
}
