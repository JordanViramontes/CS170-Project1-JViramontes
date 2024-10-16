#pragma once

#include <vector>
#include <string>

class Board {
    private:
        std::vector<std::vector<int>> board; //current board
        std::vector<std::vector<int>> goal;
        std::string blankPos = "00";
        double h;
        int size; //3x3 => size=9
        int blanknum;
        int depth;

        void findPos(const std::vector<std::vector<int>> &, int &, int &, int); //return 2 ints that show location of blank, use as a helped
        bool isMoveValid(int, int, int); //check if move is valid
        double calculateH(const std::vector<std::vector<int>> &, int); //calculate h, int = type of calculations
        int smallestTotal(double, double, double, double); //specificlaly for finding smallest total, returns the corresponding move
        std::vector<std::vector<int>> move(int); //make a move
        
    public:
        Board(); //default constructor
        Board(Board*, const std::vector<std::vector<int>> &v);
        
        Board* ASearch(int); //Search algorithm, 2nd argument is which type of A search
        std::vector<Board*> ASearchUniform();
        Board* parent;
        std::vector<Board*> children;

        void const printBoard();

        double const getH() {
            return h;
        }

        int const getDepth() {
            return depth;
        }

        void const getConstants(std::vector<std::vector<int>> &g, int &s, int &bN, int &d) {
            g = goal;
            s = size;
            bN = blanknum;
            d = depth+1;
        }

        std::vector<std::vector<int>> const getVector() {
            return board;
        }

        std::vector<std::vector<int>> const getGoal() {
            return goal;
        }
        
        std::vector<Board*> const getChildren() {
            return children;
        }

        Board* const getParent() {
            return parent;
        }
        
};

class Graph {
    private:
        std::vector<Board*> allBoards;
        Board* initBoard;
        int calc;

        void printGraph(Board*, int);
        void printGraphUniform(Board*, int);
        void ASearch(Board*, int, int);
        std::vector<Board*> ASearchUniform(Board*);
        bool checkKnowns(const std::vector<Board*> &, Board*);
            
    public:
        Graph();
        Graph(int);
        void printGraph();
        void ASearch();
};
