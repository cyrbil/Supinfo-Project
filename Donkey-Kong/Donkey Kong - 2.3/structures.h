/**
 * \file structures.h
 * \brief Comprend les déclarations de toutes les types de structures du programme. Ces structures sont là pour faciliter l'accès au maximum de données et simplifier l'envoi d'argument aux fonctions.
 * \author Steinhausser Maxime
 */

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

////////////////////////////////////////STRUCTURES/////////////////////////////////////////////////////

/////////////////SCALES//////////////////////
/**
 * \struct Scale
 * \brief Objet : Echelles.
 *
 * C'est une structure composée de deux paramètres indiquant la taille d'une échelle
 */
typedef struct Scale {//structure contenant les paramètres d'une echelle
        int ymin;
        int ymax;
        };

/////////////////MENUSTRUCT//////////////////////
/**
 * \struct Menustruct
 * \brief Objet Graphique : Composants du menu principal.
 *
 * C'est une structure qui contient les surfaces nécéssaires à l'affichage du menu principal, ainsi que les positions des différents composants.
 */
typedef struct Menustruct {//structure contenant les paramètres des menus

        //SURFACES
        SDL_Surface *Menu;
        SDL_Surface *QuitButton;
        SDL_Surface *PlayButton;
        SDL_Surface *MenuReturn;
        SDL_Surface *HowToPlay;
        SDL_Surface *ScoreButton;
        SDL_Surface *CreditsButton;
        SDL_Surface *SettingsButton;
        //POSITIONS SURFACES
        SDL_Rect positionMenu;
        SDL_Rect positionPlay;
        SDL_Rect positionQuit;
        SDL_Rect positionReturn;
        SDL_Rect positionHowToPlay;
        SDL_Rect positionScoreButton;
        SDL_Rect positionCredits;
        SDL_Rect positionSettings;
        //CHOIX
        int Selection;
        int continuer;
        int continuer1;
        int continuer2;
        };

/////////////////INFORMATIONS//////////////////////
/**
 * \struct Informations
 * \brief Structure globale : Composants essentiels au jeu.
 *
 * C'est une structure qui contient toutes les infos nécéssaires au déroulement du jeu en lui-même, les scores, les éléments interactifs, les personnages...
 * Permet de faciliter le passage de nombreuses informations en tant qu'arguments de fonctions.
 */
typedef struct Informations {//structure contenant de nombreuses informations générales liées au jeu, définie pour faciliter l'import de variables dans les fonctions
        //paramètres
        int vitesse_Mario;
        int portee_saut;
        int typepente;
        Scale scaleHeight;
        int vitesse_Tonneau;
        int vitesse_Carapace;
        int compteur_freesurfaces;
        int pauseMenu;
        int changesong;
        char Maintheme[40];
        //lié au score/level
        int score;
        int level;
        char score_string[8];
        char level_string[2];
        SDL_Surface *score_surf;
        SDL_Surface *level_surf;
        SDL_Rect positionScore;
        SDL_Rect positionLevel;
        TTF_Font *police;
        SDL_Color couleurNoire;
        //Pseudo
        char pseudo[20];
        SDL_Surface *Pseudo_surf;
        SDL_Rect pos_pseudo;
        int positionCurseur,
            continuerSaisie,
            backspace,
            continuer;
        //lié à l'affichage
        SDL_Surface *Stage;
        SDL_Rect positionStage;
        SDL_Surface *GameOver;
        SDL_Surface *Congratulations;
        SDL_Surface *YouLoose;
        /////Toolbar////////
        SDL_Surface *Toolbar;
        SDL_Rect positionToolbar;
        SDL_Surface *CurseurVolume;
        SDL_Rect positionCurseurVolume;
        ////////Peach///////
        SDL_Surface *Peach[3];
        SDL_Rect positionPeach;
        SDL_Surface *posture_Peach;
        int help;
        ////////mario///////
        SDL_Surface *Mario[29];
        SDL_Rect positionMario;
        SDL_Surface *posture_Mario;
        int positionMariotemp_x;
        int compteur_up_mario;
        int compteur_frame;
        int sens;
        ////////donkey///////
        SDL_Surface *Donkey[4];
        SDL_Rect positionDonkey;
        SDL_Surface *posture_Donkey;
        int attaque;
        //////carapace//////
        int carapace;
        SDL_Surface *Carapace;
        SDL_Rect positionCarapace;
        //////carapace2//////
        int carapace2;
        SDL_Surface *Carapace2;
        SDL_Rect positionCarapace2;
        //////carapace3//////
        int carapace3;
        SDL_Surface *Carapace3;
        SDL_Rect positionCarapace3;
        /////tonneau1///////
        int tonneau;
        SDL_Surface *Tonneau;
        SDL_Rect positionTonneau;
        /////tonneau2///////
        int tonneau2;
        SDL_Surface *Tonneau2;
        SDL_Rect positionTonneau2;
        /////tonneau3///////
        int tonneau3;
        SDL_Surface *Tonneau3;
        SDL_Rect positionTonneau3;
        //lié au jeu
        int current_floor;
        int loose;
        int game_over;
        ////////NOMBRE de vie///////
        SDL_Surface *Vies[5];
        SDL_Rect positionVies;
        SDL_Surface *NbVies;
        int vies;
        ////////Flags///////
        SDL_Surface *Flags;
        SDL_Rect positionFlags;
        int flags;
        ////////Flower///////
        SDL_Surface *Flower;
        SDL_Rect positionFlower;
        int flower;
        ////////Bowser///////
        SDL_Surface *Bowser;
        SDL_Rect positionBowser;
        int bowser;
        ////////Skelerex///////
        SDL_Surface *Skelerex;
        SDL_Rect positionSkelerex;
        int skelerex;
        ////////Yoshi///////
        SDL_Surface *Yoshi;
        SDL_Rect positionYoshi;
        int yoshi;
        ////////Yoshi///////
        SDL_Surface *Pieuvre;
        SDL_Rect positionPieuvre;
        int pieuvre;
        ////////Champvolant///////
        SDL_Surface *Champvolant;
        SDL_Rect positionChampvolant;
        int champvolant;
        ////////Pow///////
        SDL_Surface *Pow;
        SDL_Rect positionPow;
        int pow;
        int pow_activ;
        int compteur_pow_activ;
        ////////Champi///////
        SDL_Surface *Champi;
        SDL_Rect positionChampi;
        int champi;
        ////////Bloc MEtal///////
        SDL_Surface *Blocmetal;
        SDL_Rect positionBlocmetal;
        int blocmetal;
        int metal;
        };

/////////////////SON//////////////////////
/**
 * \struct Son
 * \brief Objet : Son.
 *
 * C'est une structure qui contient toutes les infos relatives aux sons du programme et à leur fonctionnement.
 * Les canaux sont les espaces réservés aux son pour être jouées, tandis que les SOUND sont les allocations en mémoire.
 */
typedef struct Son {//structure contenant les paramètres des sons

    FMOD_SYSTEM *system;
    ///////CANAUX////////////
    FMOD_CHANNEL *canal_zero;
    FMOD_CHANNEL *canal_un;
    FMOD_CHANNEL *canal_deux;
    FMOD_CHANNEL *canal_trois;
    FMOD_CHANNEL *canal_quatre;
    FMOD_CHANNEL *canal_jump;
    FMOD_CHANNEL *canal_items;
    /////////////SONS////////////////
    FMOD_SOUND *pow;
    FMOD_SOUND *jump;
	FMOD_SOUND *death;
	FMOD_SOUND *gameOver;
	FMOD_SOUND *next_level;
	FMOD_SOUND *menu;
	FMOD_SOUND *jeu;
	FMOD_SOUND *pause;
	FMOD_SOUND *items;
	FMOD_SOUND *power_up;
	FMOD_SOUND *power_down;
	FMOD_SOUND *one_up;
	FMOD_SOUND *vide;
	///////RESULT OUVERTURE//////////
	FMOD_RESULT resultat;
	///////DETECTEUR isPlaying///////
    FMOD_BOOL isplayingsound;
        };

/////////////////PARAMETRES//////////////////////
/**
 * \struct Parametres
 * \brief Objet : Paramètres.
 *
 * Structure comprenant les paramètres définis par l'utilisateur, ou par défaut.
 */
typedef struct Parametres {//structure contenant les paramètres du jeu

        FMOD_CHANNELGROUP *Allsongs;
        float GlobalVolume;
        int changeMusicSet;
        int nbVies;
        int probas_pow;
        int probas_oneUP;
        int probas_bloc_metal;
        int fullscreen;
        };

/////////////////////////////////PROTOTYPES///////////////////////////////////////////////
void clean_donnees (Informations *infos, Parametres *settings); //Fonction d'initialisation des données structurees vides.
void init_donnees (Informations *infos, Parametres *settings);//Fonction d'initialisation des donnees structurees avec les infos necessaires au jeu au premier niveau.
void lvl_up_donnees (Informations *infos, Parametres *settings);//Fonction de mise a jour des donnees structurees a chaque niveau.
//////////////////////////////////////////////////////////////////////////////////////////

#endif // STRUCTURES_H_INCLUDED

/**
 * \fn clean_donnees (Informations *infos, Parametres *settings);
 * \brief Fonction d'initialisation des données structurees vides.
 * \param infos : informations relatives au jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn init_donnees (Informations *infos, Parametres *settings);
 * \brief Fonction d'initialisation des donnees structurees avec les infos necessaires au jeu au premier niveau.
 * \param infos : informations relatives au jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

 /**
 * \fn lvl_up_donnees (Informations *infos, Parametres *settings);
 * \brief Fonction de mise a jour des donnees structurees a chaque niveau.
 * \param infos : informations relatives au jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */
