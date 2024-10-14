#pragma once

#include <vector>
#include <string>

class Board {
    private:
        std::vector<std::vector<int>> board; //current board
        std::vector<std::vector<int>> goal;
        std::string blankPos = "00";
        int size; //3x3 => size=9
        int blanknum;

        Board* parent;
        std::vector<Board*> children;

        void findPos(const std::vector<std::vector<int>> &, int &, int &, int); //return 2 ints that show location of blank, use as a helped
        bool isMoveValid(int, int, int); //check if move is valid
        double calculateH(const std::vector<std::vector<int>> &, int); //calculate h, int = type of calculations
        int smallestTotal(double, double, double, double); //specificlaly for finding smallest total, returns the corresponding move
        std::vector<std::vector<int>> move(int); //make a move
        
    public:
        Board(); //default constructor
        Board(Board*, const std::vector<std::vector<int>> &v);
        
        Board* ASearch(int); //Search algorithm, 2nd argument is which type of A search
        void addChild(Board*);

        void const printBoard();

        void const getConstants(std::vector<std::vector<int>> &g, int &s, int &bN) {
            g = goal;
            s = size;
            bN = blanknum;
        }

        std::vector<std::vector<int>> const getVector() {
            return board;
        }

        std::vector<std::vector<int>> const getGoal() {
            return goal;
        }
};

class Graph {
    private:
        std::vector<Board*> allBoards;
        Board* initBoard;

        void printNodes(Board*);
        void ASearch(Board*, int, int);
            
    public:
        Graph();
        void printGraph();
        void ASearch(int);
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
