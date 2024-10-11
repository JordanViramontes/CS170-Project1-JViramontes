#include <vector>

class Board {
    private:
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> goal;
        int size; //3x3 => size=9
        int searchType; // application of A*
    
    public:
        Board(); //default constructor
        Board(bool, int); //constructor, bool determines wheather board is scrambled or not
        // TODO: add argument for board size

        void move(std::vector<std::vector<int>> &, int); //make a move
        void swap(int &, int &); //help determine which index's in the vector to swap when moving
        int ASearch(std::vector<std::vector<int>>, int); //Search algorithm, 2nd argument is which type of A search

        const std::vector<int> displayBoard(); //return current board
};

class UI {
    private:
        Board board;
        int size;

    public:
        UI(); // constructor + set up board
        UI(int);
        void makeAmove(); //display moves
};