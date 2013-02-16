#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "../include/player.h"

class game
{
    public:
        // Constructor
        game(unsigned int w, unsigned int h, std::string player1, std::string player2);
        // Destructor
        virtual ~game();
        // Copy Constructor
        game(const game& other);

        // public attributes (yerk...)
        player players[2];
        board* _board;
        std::string winner;
        bool ended;
};

#endif // GAME_H
