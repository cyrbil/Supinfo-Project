//============================================================================
// Name        : TP-B2.cpp
// Author      : Cyril DEMINGEON - 125827@supinfo.com
// Version     : 1.4
// Copyright   : This project is under CeCILL_V2 license
//				 http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Description : Exercise during Supinfo scholarity.
//               Console board game with two player.
//============================================================================

#include <iostream>
#include <vector>
#include "include/game.h"

using namespace std;

/* // NORMAL GAME
int main(int argc, char *argv[])
{
    unsigned int w,h;
    // basic prompts for game parameters ...
    string p1,p2;
    cout << "Hello, to start a game please enter board dimensions\n\tWidth: ";
    cin >> w;
    cout << "\tHeight: ";
    cin >> h;
    cout << "\nAlright, now please enter your name and your opponent name\n\tYou: ";
    cin >> p1;
    cout << "\tOpponent: ";
    cin >> p2;

    cout << "Okay, building the game ...\n";
    game g = game(w, h, p1, p2); // new game instance
    cout << "Done !\n";

    do{ // game loop
        // player 1
        g._board->display();
        if(g.players[0].can_move(*g._board)){
            g.players[0].move(*g._board);
            g.players[0].drop_wall(*g._board);
        }else break;
        if(!g.players[0].can_move(*g._board)) { cout << "WTF, you block yourself -_- !" << endl; break;}

        // player 2
        g._board->display();
        if(g.players[1].can_move(*g._board)){
            g.players[1].move(*g._board);
            g.players[1].drop_wall(*g._board);
        }else break;
        if(!g.players[1].can_move(*g._board)) { cout << "WTF, you block yourself -_- !" << endl; break;}
    }while(true); // game end

    g.ended = true; // not very usefull ...

    // display winner
    if(!g.players[0].can_move(*g._board)){
        cout << "Mazeltof \"" << g.players[1].Get_pseudo() << "\" you ROCKS !" << endl;
    }else{
        cout << "Mazeltof \"" << g.players[0].Get_pseudo() << "\" you ROCKS !" << endl;
    }
    return 0;
}
//*/

 // MULTIPLE GAMES
int main(int argc, char *argv[])
{
    int n = 1;            // games counter
    vector<string> recap; // winners list

    while(true){
        unsigned int w,h;
        string p1,p2;

        // basic prompt
        cout << "\nGame " << n << endl;
        cout << "Please enter board dimensions\n\tWidth: ";
        cin >> w;
        cout << "\tHeight: ";
        cin >> h;
        cout << "\nAlright, now please enter your name and your opponent name\n\tYou: ";
        cin >> p1;
        cout << "\tOpponent: ";
        cin >> p2;

        cout << "Okay, building the game ...\n";
        game g = game(w, h, p1, p2);
        cout << "Done !\n";

        do{ // game loop
            // player 1
            g._board->display();
            if(g.players[0].can_move(*g._board)){
                g.players[0].move(*g._board);
                g.players[0].drop_wall(*g._board);
            }else break;
            if(!g.players[0].can_move(*g._board)) { cout << "WTF, you block yourself -_- !" << endl; break;}

            // player 2
            g._board->display();
            if(g.players[1].can_move(*g._board)){
                g.players[1].move(*g._board);
                g.players[1].drop_wall(*g._board);
            }else break;
            if(!g.players[1].can_move(*g._board)) { cout << "WTF, you block yourself -_- !" << endl; break;}
        }while(true); // game end


        g.ended = true;
        // winner display
        if(!g.players[0].can_move(*g._board)){
            cout << "Mazeltof \"" << g.players[1].Get_pseudo() << "\" you ROCKS !" << endl;
            recap.push_back(g.players[1].Get_pseudo()); // add winner name to recap
        }else{
            cout << "Mazeltof \"" << g.players[0].Get_pseudo() << "\" you ROCKS !" << endl;
            recap.push_back(g.players[0].Get_pseudo()); // add winner name to recap
        }

        // new game prompt
        char answer;
        do{
            cout << "Start a new game ? (y/n): ";
            cin >> answer;
        }while(answer!='y'&&answer!='n');
        if(answer=='n')
            break; // loop exit
        n++;
    } // game loop end

    // display recap
    cout << "\nRecap:\n" << endl;
    for(unsigned int i = 0; i < recap.size(); i++){
        cout << "\nGame " << i+1 << ": " << recap[i];
    }

    return 0; // end \o/
}
//*/
