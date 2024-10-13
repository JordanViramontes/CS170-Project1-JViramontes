#include <vector>
#include <string>

class Board {
    private:
        std::vector<std::vector<int>> board; //current board
        std::vector<std::vector<int>> goal;
        std::string blankPos = "00";
        int size; //3x3 => size=9
        int searchType; // application of A*
        int blanknum;
        void findPos(const std::vector<std::vector<int>> &, int &, int &, int); //return 2 ints that show location of blank, use as a helped
        bool isMoveValid(int, int, int); //check if move is valid
        double calculateH(const std::vector<std::vector<int>> &, int); //calculate h, int = type of calculations
        int smallestTotal(double, double, double, double); //specificlaly for finding smallest total, returns the corresponding move

    public:
        Board(); //default constructor
        Board(bool, int); //constructor, bool determines wheather board is scrambled or not
        // TODO: add argument for board size

        std::vector<std::vector<int>> move(int); //make a move
        int ASearch(int); //Search algorithm, 2nd argument is which type of A search

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