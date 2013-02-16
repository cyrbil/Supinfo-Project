/**
 * \file main.c
 * \brief Fichier principal du programme. Contient la boucle principale faisant tourner le programme.
 * \author Steinhausser Maxime, Demingeon Cyril, Fleury Dorian, Burellier Jean
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <string.h>
#include <fmod.h>
#include <curl.h>
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

CURL *curl;

/**
 * \fn main(int argc, char *argv[])
 * \brief Boucle principal du programme : Selection menus et jeu.
 */

int main(int argc, char *argv[])
{
    curl = curl_easy_init();
    if(!curl){
        fprintf(stderr, "Unable to load curl");
        exit(EXIT_FAILURE);
    }
    SDL_Surface *ecran = NULL, *Menu =NULL, *icone = SDL_LoadBMP("images/icone.bmp"); // Le pointeur qui va stocker la surface de l'écran et autres surfaces
    SDL_SetColorKey(icone, SDL_SRCCOLORKEY, SDL_MapRGB(icone->format, 89, 242, 255));

    // Démarrage de la SDL avec audio, vidéo, et timer. Si erreur alors...
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Ecriture de l'erreur
            exit(EXIT_FAILURE); // On quitte le programme
        }
    //Démarrage SDL TTF---------------------------------------
    if(TTF_Init() == -1)
        {
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }
    //Démarrage FMod--------------------------------------------------------
    Son musique;            //Création d'une structure de type Son, de nom "musique"
    ////ini struct/////     //Initialise une structure vide
    musique.system=NULL;
    musique.canal_zero=NULL;
    musique.canal_un=NULL;
    musique.canal_deux=NULL;
    musique.canal_trois=NULL;
    musique.canal_quatre=NULL;
    musique.canal_jump=NULL;
    musique.canal_items=NULL;
    musique.pow=NULL;
    musique.jump=NULL;
	musique.death=NULL;
	musique.gameOver=NULL;
	musique.next_level=NULL;
	musique.menu=NULL;
	musique.jeu=NULL;
	musique.pause=NULL;
	musique.items=NULL;
	musique.power_up=NULL;
	musique.power_down=NULL;
	musique.one_up=NULL;
	musique.vide=NULL;
    musique.isplayingsound=0;
    /////////////////////
    FMOD_System_Create(&musique.system);
	FMOD_System_Init(musique.system, 20, FMOD_INIT_NORMAL, NULL);
	//-----------------------------------------------------------
    SDL_WM_SetIcon(icone, 0);                                                                //Change l'icone de la fenêtre
    ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT );//Chargement de la fenêtre de 1000*700 pixel, 32 bits/pixel, dans la mémoire vidéo, mode double buffering
    if (ecran == NULL)                                                                     // Si l'ouverture a échoué, on écrit l'erreur et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Donkey Kong", NULL);                         //Change le titre de la fenêtre
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); //Définie la couleur de fond de la fenêtre (noir)
    SDL_Flip(ecran); // Mise à jour de l'écran
    //FIN INITIALISATION---------------------------------------
    SDL_EnableKeyRepeat(200, 200);
    SDL_Event event;
    Menustruct GestionMenus;
    ////INITIALISATION STRUCTURE MENU////
    GestionMenus.Selection=1;
    GestionMenus.continuer=1;
    GestionMenus.continuer1=1;
    GestionMenus.continuer2=1;
    ////////////////////////////////////
    /////////////////////MENU PRINCIPAL/////////////////////
    /////////SON MENU INI///////////////////////////////////////
    FMOD_Sound_SetLoopCount(musique.menu, -1);//On active la répétition de la musique menu à l'infini: une fois
    FMOD_System_GetChannel(musique.system, 0, &musique.canal_zero);
    FMOD_System_GetChannel(musique.system, 1, &musique.canal_un);
    FMOD_System_GetChannel(musique.system, 2, &musique.canal_deux);
    FMOD_System_GetChannel(musique.system, 3, &musique.canal_trois);
    FMOD_System_GetChannel(musique.system, 4, &musique.canal_quatre);
    FMOD_System_GetChannel(musique.system, 5, &musique.canal_jump);
    FMOD_System_GetChannel(musique.system, 6, &musique.canal_items);
    ///////////////INI PARAMETRES/////////////////////////////////
    // Paremetre de base
    Parametres settings;
    settings.Allsongs=NULL;
    get_settings(&settings);//obtiens les paramètres stockés dans un fichier/ou établis celle par défaut
    if (settings.fullscreen==1)//Si le mode plein écran était activé dans les paramètres, on l'active
        {
            ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF| SDL_FULLSCREEN | SDL_ASYNCBLIT );
        }
    ///////////////PARAMETRE LAUNCH///////////////////////////
    FMOD_System_GetMasterChannelGroup(musique.system, &settings.Allsongs);
    //////////////////////////////////////////////////////////

    while (GestionMenus.continuer)
    //Boucle principale N°1 :
    //Couche MENU PROGRAMME.
    //Cette boucle est lancée dès le début du programme.
    //Elle est entierement parcourue tant que le jeu ou un autre menu n'est pas sélectionné.
    //Lorsqu'elle est entierement lue, l'affichage du menu principal du programme en résulte.
    {
        SDL_WaitEvent(&event);

        FMOD_ChannelGroup_SetVolume(settings.Allsongs, settings.GlobalVolume);//règle le volume global
        //////////////////SON//////////////////
        if (FMOD_Channel_IsPlaying (musique.canal_zero, &musique.isplayingsound) !=FMOD_OK)//Si le son n'est pas déjà en train d'être joué (FMOD_OK = son joué), on écrit l'erreur et on arrête.
        {
            musique.resultat = FMOD_System_CreateSound(musique.system,
                                                       "sons/Musique_Menu.mp3",
                                                       FMOD_SOFTWARE |
                                                       FMOD_2D |
                                                       FMOD_CREATESTREAM |
                                                       FMOD_LOOP_NORMAL,
                                                       0,
                                                       &musique.menu);
            if (musique.resultat != FMOD_OK)
            {
                fprintf(stderr, "Impossible de lire le fichier mp3\n");
                exit(EXIT_FAILURE);
            }
            FMOD_System_PlaySound(musique.system, FMOD_CHANNEL_FREE, musique.menu, 0, &musique.canal_zero);
        }
        //////////////////////////////////////////
        switch(event.type)
        {
            case SDL_QUIT:
                GestionMenus.continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        GestionMenus.continuer = 0;
                        break;
                    case SDLK_RETURN:
                        if (GestionMenus.Selection ==1){GestionMenus.continuer1 = 1; GestionMenus.continuer2 = 1; FMOD_Channel_Stop(musique.canal_zero); Main_Engine(ecran, &GestionMenus, &musique, &settings); FMOD_Sound_Release(musique.menu);}
                        if (GestionMenus.Selection ==2){GestionMenus.continuer1 = 1; GestionMenus.continuer2 = 1; HowToPlay(ecran, &GestionMenus);}
                        if (GestionMenus.Selection ==3){GestionMenus.continuer1 = 1; GestionMenus.continuer2 = 1; Score_Menu(ecran, &GestionMenus);}
                        if (GestionMenus.Selection ==4){GestionMenus.continuer1 = 1; GestionMenus.continuer2 = 1; Menu_Settings(ecran, &GestionMenus, &settings);}
                        if (GestionMenus.Selection ==5){GestionMenus.continuer1 = 1; GestionMenus.continuer2 = 1; Menu_Credits(ecran, &GestionMenus);}
                        if (GestionMenus.Selection ==6){GestionMenus.continuer = 0;}
                        break;

                    case SDLK_RIGHT:
                        if (GestionMenus.Selection<=6){GestionMenus.Selection++;}
                        break;

                    case SDLK_LEFT:
                        if (GestionMenus.Selection>=1){GestionMenus.Selection--;}
                        break;

                    case SDLK_UP:
                        GestionMenus.Selection-=3;
                        break;

                    case SDLK_DOWN:
                        GestionMenus.Selection+=3;
                        break;

                    default:
                    void();
                    break;
                }
                break;
        }
        ////(RE)INITIALISATION STRUCTURE MENU////
        GestionMenus.Menu = IMG_Load("images/menu.jpg");
        GestionMenus.positionMenu.x = 0;
        GestionMenus.positionMenu.y = 0;
        GestionMenus.positionPlay.x = 80;
        GestionMenus.positionPlay.y = 140;
        GestionMenus.positionHowToPlay.x = 380;
        GestionMenus.positionHowToPlay.y = 140;
        GestionMenus.positionScoreButton.x = 680;
        GestionMenus.positionScoreButton.y = 140;
        GestionMenus.positionSettings.x = 80;
        GestionMenus.positionSettings.y = 345;
        GestionMenus.positionCredits.x = 380;
        GestionMenus.positionCredits.y = 345;
        GestionMenus.positionQuit.x = 680;
        GestionMenus.positionQuit.y = 345;
        /////////////////////////////////////
        if (GestionMenus.Selection>6){GestionMenus.Selection=1;}
        if (GestionMenus.Selection<1){GestionMenus.Selection=6;}
        //////////////GESTION MENU AFFICHAGE///////////////
        if (GestionMenus.Selection==1){GestionMenus.PlayButton = IMG_Load("images/BoutonPlay.png");}
        else {GestionMenus.PlayButton = IMG_Load("images/BoutonPlay2.png");}
        if (GestionMenus.Selection==2) {GestionMenus.HowToPlay = IMG_Load("images/BoutonHowToPlay.png");}
        else{GestionMenus.HowToPlay = IMG_Load("images/BoutonHowToPlay2.png");}
        if (GestionMenus.Selection==3) {GestionMenus.ScoreButton = IMG_Load("images/BoutonScore.png");}
        else{GestionMenus.ScoreButton = IMG_Load("images/BoutonScore2.png");}
        if (GestionMenus.Selection==4) {GestionMenus.SettingsButton = IMG_Load("images/boutonParametres.png");}
        else{GestionMenus.SettingsButton = IMG_Load("images/boutonParametres2.png");}
        if (GestionMenus.Selection==5) {GestionMenus.CreditsButton = IMG_Load("images/boutonCredits.png");}
        else{GestionMenus.CreditsButton = IMG_Load("images/boutonCredits2.png");}
        if (GestionMenus.Selection==6) {GestionMenus.QuitButton = IMG_Load("images/BoutonQuitter.png");}
        else{GestionMenus.QuitButton = IMG_Load("images/BoutonQuitter2.png");}

        SDL_BlitSurface(GestionMenus.Menu, NULL, ecran, &GestionMenus.positionMenu);// On blitte par-dessus l'écran
        SDL_BlitSurface(GestionMenus.PlayButton, NULL, ecran, &GestionMenus.positionPlay);
        SDL_BlitSurface(GestionMenus.HowToPlay, NULL, ecran, &GestionMenus.positionHowToPlay);
        SDL_BlitSurface(GestionMenus.ScoreButton, NULL, ecran, &GestionMenus.positionScoreButton);
        SDL_BlitSurface(GestionMenus.SettingsButton, NULL, ecran, &GestionMenus.positionSettings);
        SDL_BlitSurface(GestionMenus.CreditsButton, NULL, ecran, &GestionMenus.positionCredits);
        SDL_BlitSurface(GestionMenus.QuitButton, NULL, ecran, &GestionMenus.positionQuit);
        SDL_Flip(ecran); // Mise à jour de l'écran
        //Libèration de la mémoire du menu principal
        SDL_FreeSurface(GestionMenus.Menu);
        SDL_FreeSurface(GestionMenus.PlayButton);
        SDL_FreeSurface(GestionMenus.HowToPlay);
        SDL_FreeSurface(GestionMenus.ScoreButton);
        SDL_FreeSurface(GestionMenus.SettingsButton);
        SDL_FreeSurface(GestionMenus.CreditsButton);
        SDL_FreeSurface(GestionMenus.QuitButton);
    }
    ///////////////////FIN MENU PRINCIPAL///////////////////
    // Arrêt de la SDL (libération de la mémoire).
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(icone);
    SDL_FreeSurface(Menu);
    FMOD_Sound_Release(musique.menu);
    SDL_Quit();
    TTF_Quit();
    //---------------------------------------------------------
    return EXIT_SUCCESS;
}
///////////////////////////FIN MAIN////////////////////////////
