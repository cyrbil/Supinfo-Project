#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

void sprites_loading (Informations *infos); //Fonction de chargement des sprites d'affichage des personnages.
void MAJ_Affichage(Informations *infos, SDL_Surface *ecran); //Fonction de mise à jour de l'affichage à l'ecran.
void change_frame_left(Informations *infos, SDL_Surface *ecran); //Fonction animant mario lors de son deplacement a gauche
void change_frame_right(Informations *infos, SDL_Surface *ecran);//Fonction animant mario lors de son deplacement a droite
void Game_Over (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings);//Affichage de l'ecran game over/defaite.
void Next_level (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings);//Affichage de l'ecran de victoire amenant au niveau suivant.
void pause_menu(SDL_Surface *ecran, Menustruct *GestionMenus, Informations *infos, Son *musique);//Affichage du menu pause.
void HowToPlay(SDL_Surface *ecran, Menustruct *GestionMenus);//Affichage du menu d'aide au jeu et scenario.
void Score_Menu(SDL_Surface *ecran, Menustruct *GestionMenus);//Affichage du menu score.
void Menu_Credits(SDL_Surface *ecran, Menustruct *GestionMenus);//Affichage du menu credits.
void Menu_Settings(SDL_Surface *ecran, Menustruct *GestionMenus, Parametres *settings);//Affichage du menu parametres.

#endif // AFFICHAGE_H_INCLUDED

/**
 * \fn sprites_loading (Informations *infos)
 * \brief Fonction de chargement des sprites d'affichage des personnages.
 * \param infos : informations relatives au jeu.
 */

 /**
 * \fn MAJ_Affichage(Informations *infos, SDL_Surface *ecran)
 * \brief Fonction de mise à jour de l'affichage à l'ecran.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

  /**
 * \fn change_frame_right(Informations *infos, SDL_Surface *ecran)
 * \brief Fonction animant mario lors de son deplacement a droite.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

/**
 * \fn change_frame_left(Informations *infos, SDL_Surface *ecran)
 * \brief Fonction animant mario lors de son deplacement a gauche.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

/**
 * \fn Game_Over (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
 * \brief Affichage de l'ecran game over/defaite.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 * \param musique : Structure relative aux sons et musiques du jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

 /**
 * \fn Next_level (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
 * \brief Affichage de l'ecran de victoire amenant au niveau suivant.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 * \param musique : Structure relative aux sons et musiques du jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn pause_menu(SDL_Surface *ecran, Menustruct *GestionMenus, Informations *infos, Son *musique)
 * \brief Affichage du menu pause.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 * \param musique : Structure relative aux sons et musiques du jeu.
 * \param GestionMenus : elements de menu disponibles en jeu.
 */

/**
 * \fn HowToPlay(SDL_Surface *ecran, Menustruct *GestionMenus)
 * \brief Affichage du menu d'aide au jeu et scenario.
 * \param ecran : Surface principale d'affichage.
 * \param GestionMenus : elements de menu disponibles en jeu.
 */

/**
 * \fn Score_Menu(SDL_Surface *ecran, Menustruct *GestionMenus)
 * \brief Affichage du menu score.
 * \param ecran : Surface principale d'affichage.
 * \param GestionMenus : elements de menu disponibles en jeu.

/**
 * \fn Menu_Credits(SDL_Surface *ecran, Menustruct *GestionMenus)
 * \brief Affichage du menu credits.
 * \param ecran : Surface principale d'affichage.
 * \param GestionMenus : elements de menu disponibles en jeu.
 */

 /**
 * \fn Menu_Settings(SDL_Surface *ecran, Menustruct *GestionMenus, Parametres *settings)
 * \brief Affichage du menu parametres.
 * \param ecran : Surface principale d'affichage.
 * \param GestionMenus : elements de menu disponibles en jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

