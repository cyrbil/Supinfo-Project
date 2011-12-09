#ifndef FREEMEMORY_H_INCLUDED
#define FREEMEMORY_H_INCLUDED

void free_surfaces_Persos_and_reattribute(SDL_Surface *ecran, Informations *infos); //Libere les surfaces attribuees aux personnages et les reatribut en rappelant la fonction sprites_loading.
void free_surfaces_Persos(SDL_Surface *ecran, Informations *infos);//Libere les surfaces attribuees aux personnages.
void free_surfaces_elements(SDL_Surface *ecran, Informations *infos );//Libere les surfaces attribuees aux elements.
void free_surfaces_elements_and_reattribute(SDL_Surface *ecran, Informations *infos );//Libere les surfaces attribuees aux elements et les reatribut.

#endif // FREEMEMORY_H_INCLUDED

/**
 * \fn free_surfaces_Persos_and_reattribute(SDL_Surface *ecran, Informations *infos)
 * \brief Libere les surfaces attribuees aux personnages et les reatribut en rappelant la fonction sprites_loading.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

 /**
 * \fn free_surfaces_Persos(SDL_Surface *ecran, Informations *infos)
 * \brief //Libere les surfaces attribuees aux personnages.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

 /**
 * \fn free_surfaces_elements(SDL_Surface *ecran, Informations *infos)
 * \brief Libere les surfaces attribuees aux elements.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */

 /**
 * \fn free_surfaces_elements_and_reattribute(SDL_Surface *ecran, Informations *infos)
 * \brief //Libere les surfaces attribuees aux elements et les reatribut.
 * \param infos : informations relatives au jeu.
 * \param ecran : Surface principale d'affichage.
 */
