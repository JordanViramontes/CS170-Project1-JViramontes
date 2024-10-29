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
        std::vector<std::vector<int>> goal;
        std::string blankPos = "00";
        bool explored = false;
        double h;
        int depth;
        double f;
        int size; //3x3 => size=9
        int blanknum;
        Board* parent;
        std::vector<Board*> children;

        void fillGoal(std::vector<std::vector<int>> &, int);
        void findPos(const std::vector<std::vector<int>> &, int &, int &, int); //return 2 ints that show location of blank, use as a helped
        bool isMoveValid(int, int, int); //check if move is valid
        double calculateH(const std::vector<std::vector<int>> &, 
                          const std::vector<std::vector<int>> &, int); //calculate h, int = type of calculations
        std::vector<double> sortTotals(double, double, double, double); //specificlaly for finding smallest total, returns the corresponding move
        std::vector<std::vector<int>> move(int); //make a move
        bool checkKnowns(std::vector<Board*> &, std::vector<std::vector<int>> &);
    public:
        Board(); //default constructor
        Board(Board*, const std::vector<std::vector<int>> &v, int);
        ~Board() {
            parent = nullptr;
        }

        std::vector<Board*> ASearch(std::vector<Board*> &, int); //Search algorithm, 2nd argument is which type of A search
        std::vector<Board*> ASearchUniform();
        void const printBoard();
        void const printGoal();
        void addChildren(std::vector<Board*> t) { 
            for (unsigned int i = 0; i < t.size(); i++) { children.push_back(t.at(i)); }
        }
        void addSingleChild(Board* t) { children.push_back(t); }
        const void printChildren() {
            for (unsigned int i = 0; i < children.size(); i++) {
                std::cout << "Child: " << i << "; "
                     << "Depth: " << children.at(i)->getDepth() 
                     << ", H: " << children.at(i)->getH() 
                     << ", F:" << children.at(i)->getF() << std::endl;
                children.at(i)->printBoard();
            }
        }
        void const getConstants(std::vector<std::vector<int>> &g, int &s, int &bN, int &d) {
            g = goal;
            s = size;
            bN = blanknum;
            d = depth+1;
        }
        std::vector<std::vector<int>> const getVector() { return board; }
        std::vector<std::vector<int>> const getGoal() { return goal; }
        std::vector<Board*> const getChildren() { return children; }
        Board* const getParent() { return parent; }
        double const getH() { return h; }
        double const getF() { return f; }
        int const getDepth() { return depth; }
        bool const getExplored() { return explored; }
        void setExplored() { explored = true; }

};

class Graph {
    private:
        std::vector<Board*> allBoards;
        Board* initBoard;
        Board* finalBoard;
        int calc;

        void printRoute(Board*, int);
        void ASearch(Board*, int, int);
        std::vector<Board*> ASearchUniform(Board*);
        bool checkKnowns(const std::vector<Board*> &, Board*);
        void addBoardVec(std::vector<Board*> t) { 
            for (unsigned int i = 0; i < t.size(); i++) { allBoards.push_back(t.at(i)); }
        }
            
    public:
        Graph();
        Graph(std::vector<std::vector<int>>, int);
        Graph(int);
        ~Graph() {
            for (int i = 0; i < allBoards.size(); i++) {
                delete allBoards.at(i);
                allBoards.at(i) = nullptr;
            }
            initBoard = nullptr; delete initBoard;
            finalBoard = nullptr; delete finalBoard;
        }

        void printRoute();
        void printAllBoards();
        int ASearch();
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