#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

void jump (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings);//Gere le saut du personnage principal.
void move_right (Informations *infos);//Gere le mouvement du personnage principal vers la droite.
void move_left (Informations *infos);//Gere le mouvement du personnage principal vers la gauche.

#endif // PERSONNAGE_H_INCLUDED

/**
 * \fn jump (SDL_Surface *ecran, Informations *infos, Son *musique, Parametres *settings)
 * \brief Gere le saut du personnage principal.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 * \param musique : Structure relative aux sons et musiques du jeu. (son du saut de mario)
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn move_right (Informations *infos)
 * \brief Gere le mouvement du personnage principal vers la droite.
 * \param infos : informations relatives au jeu.
 */

/**
 * \fn move_left (Informations *infos)
 * \brief Gere le mouvement du personnage principal vers la gauche.
 * \param infos : informations relatives au jeu.
 */

