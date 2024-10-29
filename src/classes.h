#pragma once

#include <vector>
#include <string>

// mini for help when sorting moves (greedy)
// had issue where H = 2 different moves
struct moves {
    public:
        double value;
        int move;

        moves(double v, int m) {
            value = v;
            move = m;
        }
};

struct compare {
    inline bool operator() (const moves& struct1, const moves& struct2)
    {
        return (struct1.value < struct2.value);
    }
};

class Board {
    private:
        std::vector<std::vector<int>> board; //current board
        std::vector<Board*> children;
        Board* parent;
        bool explored = false;
        double h; int g; double f;
        int size = 3; // 3x3 board
        int blanknum; // should be size*size=9 by default
        
        // helpers
        void findPos(const std::vector<std::vector<int>> &, int &, int &, int); //return 2 ints that show location of blank, use as a helped
        std::vector<std::vector<int>> move(int); //make and return a move
        bool isMoveValid(int, int, int); //check if move is valid
        double calculateH(const std::vector<std::vector<int>> &, 
                          const std::vector<std::vector<int>> &, int); //calculate h, int = type of calculations
    public:
        // constructors
        Board(Board*, const std::vector<std::vector<int>> &, const std::vector<std::vector<int>> &, int);
        ~Board();
        void const getConstants(int &s, int &bN, int &d);

        // Algorithm
        std::vector<Board*> ASearch(std::vector<Board*> &, const std::vector<std::vector<int>> &, int); //Search algorithm, 2nd argument is which type of A search
        std::vector<Board*> ASearchUniform(const std::vector<std::vector<int>> &);
        void addChildren(std::vector<Board*> t);

        // Get
        std::vector<std::vector<int>> const getVector() { return board; }
        Board* const getParent() { return parent; }
        double const getF() { return f; }
        int const getDepth() { return g; }
        bool const getExplored() { return explored; }

        // Print
        void const printBoard();
};

class Graph {
    private:
        std::vector<Board*> allBoards; // vector of all created boards in order of creation
        Board* initBoard; // first board
        Board* finalBoard; // final board
        std::vector<std::vector<int>> goal; // goal state
        int calc; // determines the heuristic
        int size = 3;

        void printRoute(Board*);
        void ASearch(Board*, int, int);
        std::vector<Board*> ASearchUniform(Board*);
            
    public:
        // constructors
        Graph(std::vector<std::vector<int>>, int);
        ~Graph();

        // functions
        void printRoute();
        void printAllBoards();
        int ASearch();

        // get
        int getDepth() { return finalBoard->getDepth(); };
};

class UI {
    private:
        Graph* g;
        bool isComplete = false;
        void randomBoard();
        void setBoard(int c);
        int setCalc();
        void quitSequence();

    public:
        UI() { };
        ~UI() { 
            g = nullptr;
            delete g;
        }
        void startingSequence();
        void ASearch();
        void printRoute();
        const bool getIsComplete() { return isComplete; }
};