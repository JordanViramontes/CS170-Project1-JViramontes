#include <vector>

class Board {
    private:
        std::vector<int> board;
        std::vector<int> goal;
        int size = 3; //TODO: WILL CHANGE LATER FOR VARIAbILITY
        int searchType;
    
    public:
        Board(bool, int); //constructor, bool determines wheather board is scrambled or not
        // TODO: add argument for board size

        std::vector<int> Move(int); //after a move, it returns a new board
        void        swap(int &, int &); //help determine which index's in the vector to swap when moving
        int         ASearch(std::vector<int>, int); //Search algorithm, 2nd argument is which type of A search

        const std::vector<int> displayBoard(); //return current board
};

class UI {
    private:
        Board board;
        
    public:
        UI(); // constructor + set up board
        void makeAmove(); //display moves
};