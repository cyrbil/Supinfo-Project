#ifndef SONS_H_INCLUDED
#define SONS_H_INCLUDED

void choose_song (Informations* infos, Son *musique); //Choisit de manière aléatoire une musique parmi celles programmees.
void load_game_songs (Son *musique); //Charge les effets sonores du jeu et elements interactifs.
void free_game_songs (Son *musique); //Desalloue la memoire octroyee aux effets sonores du jeu et elements interactifs.

#endif // SONS_H_INCLUDED

/**
 * \fn choose_song (Informations* infos, Son *musique)
 * \brief Choisit de manière aléatoire une musique parmi celles programmees.
 * \param infos : informations relatives au jeu.
 * \param musique : Structure relative aux sons et musiques du jeu.
 */

 /**
 * \fn load_game_songs (Son *musique)
 * \brief Charge les effets sonores du jeu et elements interactifs.
 * \param musique : Structure relative aux sons et musiques du jeu.
 */

 /**
 * \fn free_game_songs (Son *musique)
 * \brief Desalloue la memoire octroyee aux effets sonores du jeu et elements interactifs.
 * \param musique : Structure relative aux sons et musiques du jeu.
 */
