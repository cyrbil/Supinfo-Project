#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

void Main_Engine(SDL_Surface *ecran, Menustruct *GestionMenus, Son *musique, Parametres *settings); //Moteur principal du jeu
void manage_floor(SDL_Surface *ecran, Informations *infos, Parametres *settings); //Gestion des deplacements horizontaux du personnage selon l'etage
void manage_scale(Informations *infos, SDL_Surface *ecran); //Gestion des deplacements verticaux du personnages; passage d'un etage à un autre via les echelles.
void Collision_Engine (SDL_Surface *ecran, Informations *infos, Son *musique); //Gestion des collisions entre le personnage principal et les elements interactifs ou projectiles.
void found_floor(SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings); //Determine sur quel etage est le personnage principal et influe sur son deplacement.

#endif // MOTEUR_H_INCLUDED

/**
 * \fn Main_Engine(SDL_Surface *ecran, Menustruct *GestionMenus, Son *musique, Parametres *settings)
 * \brief Moteur principal du jeu.
 * \param ecran : Surface principale d'affichage.
 * \param GestionMenus : elements de menu disponibles en jeu.
 * \param musique : Structure relative aux sons et musiques du jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn manage_floor(SDL_Surface *ecran, Informations *infos, Parametres *settings)
 * \brief Gestion des deplacements horizontaux du personnage selon l'étage
 * \param ecran : Surface principale d'affichage.
 * \param infos : informations relatives au jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn manage_scale(Informations *infos, SDL_Surface *ecran)
 * \brief Gestion des deplacements verticaux du personnages; passage d'un etage à un autre via les echelles.
 * \param ecran : Surface principale d'affichage.
 * \param infos : informations relatives au jeu.
 */

 /**
 * \fn Collision_Engine (SDL_Surface *ecran, Informations *infos, Son *musique)
 * \brief Gestion des collisions entre le personnage principal et les elements interactifs ou projectiles.
 * \param ecran : Surface principale d'affichage.
 * \param infos : informations relatives au jeu.
 * \param musique : Structure relative aux sons et musiques du jeu.
 */

  /**
 * \fn found_floor(SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
 * \brief Determine sur quel etage est le personnage principal et influe sur son deplacement.
 * \param ecran : Surface principale d'affichage.
 * \param infos : informations relatives au jeu.
 * \param musique : Structure relative aux sons et musiques du jeu.
 * \param settings : Structure relative aux parametres utilisateurs.
 */
