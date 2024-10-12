#include <vector>
#include <string>

class Board {
    private:
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> goal;
        std::string blankPos = "00";
        int size; //3x3 => size=9
        int searchType; // application of A*
        void findBlank(int &, int &); //return 2 ints that show location of blank, use as a helped
        bool isMoveValid(int, int, int); //check if move is valid
    
    public:
        Board(); //default constructor
        Board(bool, int); //constructor, bool determines wheather board is scrambled or not
        // TODO: add argument for board size

        void move(int); //make a move
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