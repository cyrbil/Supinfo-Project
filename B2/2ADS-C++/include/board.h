#ifndef BOARD_H
#define BOARD_H

class board
{
    private:
        unsigned int** _board;  // numeric game board representation
        unsigned int   _width;  // width of the board
        unsigned int   _height; // height of the board
    public:
        board(unsigned int width = 6, unsigned int height = 5);
        board(const board&);
        virtual ~board();
        board* operator++(int);
        // Getters
        unsigned int Get_width() { return _width; }
        unsigned int Get_height() { return _height; }
        // Methods
        bool is_free(unsigned int, unsigned);
        void display(void);
        int get_square(unsigned int, unsigned int);
        void set_square(unsigned int, unsigned int, unsigned int);
};

#endif // BOARD_H
