#ifndef ELEMENTS_H_INCLUDED
#define ELEMENTS_H_INCLUDED

void DonkeyKong_Engine (Informations *infos); //Gere l'affichage et le lancement des attaques de Donkey Kong.
void Projectiles_Engine (Informations *infos); //Gere le comportement des projectiles lances par Donkey Kong.
void Peach_engine (Informations *infos); //Gere l'affichage de le princesse.
void check_if_pow(Informations *infos, Son *musique); //Verifie si le pow est actif ou non et gere l'affichage qui en resulte, ainsi que la duree de ses effets.

void get_settings(Parametres *settings); //Charge les parametres utilisateur enregistres dans un fichier externe.
void write_settings(Parametres *settings);//Enregistre dans un fichier externe les parametres utilisateurs.

#endif // ELEMENTS_H_INCLUDED

/**
 * \fn DonkeyKong_Engine (Informations *infos)
 * \brief Gere l'affichage et le lancement des attaques de Donkey Kong.
 * \param infos : informations relatives au jeu.
 */

/**
 * \fn DonkeyKong_Engine (Informations *infos)
 * \brief Gere le comportement des projectiles lances par Donkey Kong.
 * \param infos : informations relatives au jeu.
 */

/**
 * \fn Peach_engine (Informations *infos)
 * \brief Gere l'affichage de le princesse.
 * \param infos : informations relatives au jeu.
 */

 /**
 * \fn check_if_pow (Informations *infos, Son *musique)
 * \brief Gere l'affichage de le princesse.
 * \param infos : informations relatives au jeu.
 * \param musique : Structure relative aux sons et musiques du jeu.
 */

/**
 * \fn get_settings(Parametres *settings)
 * \brief Charge les parametres utilisateur enregistres dans un fichier externe.
 * \param settings : Structure relative aux parametres utilisateurs.
 */

/**
 * \fn write_settings(Parametres *settings)
 * \brief Enregistre dans un fichier externe les parametres utilisateurs.
 * \param settings : Structure relative aux parametres utilisateurs.
 */
