#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>

#include "classes.h" //includes vector

using namespace std;

// Board (object should never be created without a vector)
Board::Board(shared_ptr<Board> p, const vector<vector<int>> &v, const vector<vector<int>> &goal, int calc) {
    board = v;

    if (p == nullptr) {
        blanknum = size*size;
        g = 0;
    }
    else p->getConstants(size, blanknum, g);

    parent = p;
    h = calculateH(board, goal, calc);
    f = h + g;
}

void const Board::getConstants(int &s, int &bN, int &d) {
    // this will be called by the constructor
    s = size;
    bN = blanknum;
    d = g+1;
}

void Board::findPos(const vector<vector<int>> &v, int &pos1, int &pos2, int num) {
    //Find position of number
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = 0; j < v.at(i).size(); j++) {
            if (v.at(i).at(j) == num) {
                pos1 = i;
                pos2 = j;
                return;
            }
        }
    }
    cout << "Could not find blank space. Returning (0,0)" << endl; 
    pos1 = 0;   pos2 = 0;
}

bool Board::isMoveValid(int pos1, int pos2, int move) {
    switch(move) {
        case (0) : { //up
            // board.at(pos1-1).at(pos2);
            if (pos1-1 < 0) return false;
            else return true;
            break;
        }
        case (1) : { //down
            // board.at(pos1+1).at(pos2);
            if (pos1+1 > (int)board.size()-1) return false;
            else return true;
            break;
        }
        case (2) : { //left
            // board.at(pos1).at(pos2-1);
            if (pos2-1 < 0) return false;
            else return true;
            break;
        }
        case (3) : { //right
            // board.at(pos1).at(pos2+1);
            if (pos2+1 > (int)board.size()-1) return false;
            else return true;
            break;
        }
        default: {
            cout << "SWITCH-CASE ERROR WHEN VALIDATING MOVE" << endl;
            return false;
            break;
        }
    }
}

vector<vector<int>> Board::move(int move) {
    //This will be what we return
    vector<vector<int>> tempBoard = board;

    // get blank's current position
    int pos1, pos2;
    findPos(tempBoard, pos1, pos2, board.size() * tempBoard.size());

    // Check for valitiy before moving
    if (!isMoveValid(pos1, pos2, move)) {
        cout << "Move is not valid, returning";
        return tempBoard;
    }

    // position of blank
    int blank = tempBoard.at(pos1).at(pos2);

    switch(move) {
        case (0) : { //up
            // cout << "UP: " << endl;
            int temp = tempBoard.at(pos1-1).at(pos2);
            tempBoard.at(pos1-1).at(pos2) = blank;
            tempBoard.at(pos1).at(pos2) = temp;
            break;
        }
        case (1) : { //down
            // cout << "DOWN: " << endl;
            int temp = tempBoard.at(pos1+1).at(pos2);
            tempBoard.at(pos1+1).at(pos2) = blank;
            tempBoard.at(pos1).at(pos2) = temp;
            break;
        }
        case (2) : { //left
            // cout << "LEFT: " << endl;
            int temp = tempBoard.at(pos1).at(pos2-1);
            tempBoard.at(pos1).at(pos2-1) = blank;
            tempBoard.at(pos1).at(pos2) = temp;
            break;
        }
        case (3) : { //right
            // cout << "RIGHT: "<< endl;
            int temp = tempBoard.at(pos1).at(pos2+1);
            tempBoard.at(pos1).at(pos2+1) = blank;
            tempBoard.at(pos1).at(pos2) = temp;
            break;
        }
        default: {
            cout << "SWITCH-CASE ERROR WHEN MOVING" << endl;
            break;
        }
    }

    // cout << "PRINTING MOVED VEC: " << endl;
    // printVec(board);
    return tempBoard;
};  

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double Board::calculateH(const vector<vector<int>> &v, 
                         const std::vector<std::vector<int>> &g, int calc) {  
    double total = 0;

    switch(calc) {
        case 0: {
            total = 0;
            break;
        }
        case 1: { //Mismatched Tile
            for (unsigned int i = 0; i < v.size(); i++) {
                for (unsigned int j = 0; j < v.at(i).size(); j++) {
                    if (v.at(i).at(j) != g.at(i).at(j)) total++;
                }
            }

            // cout << "H: " << total << endl;
            // printVec(v);
            break;
        }
        case 2: { //Euclidean
            for (int i = 0; i < blanknum-1; i++) {
                int x1, x2, y1, y2;
                findPos(v, x1, y1, i+1);
                findPos(g, x2, y2, i+1);
                total += distance(x1, y1, x2, y2);
            }
            break;
        }
        default: {
            cout << "ERROR WITH H CALCULATION, INVALID CALC TYPE" << endl;
            break;
        }
    }

    return total;
}

vector<shared_ptr<Board>> Board::ASearch(vector<shared_ptr<Board>> &knowns, const std::vector<std::vector<int>> &goal, int calc) {
    vector<vector<int>> tempVector = board;

    int pos1, pos2;
    findPos(board, pos1, pos2, blanknum);

    double hU = blanknum*blanknum, 
        hD = blanknum*blanknum, 
        hL = blanknum*blanknum, 
        hR = blanknum*blanknum;

    // Check possible 4 next states
    if (isMoveValid(pos1, pos2, 0)) hU = calculateH(move(0), goal, calc); //Up
    if (isMoveValid(pos1, pos2, 1)) hD = calculateH(move(1), goal, calc); //Down
    if (isMoveValid(pos1, pos2, 2)) hL = calculateH(move(2), goal, calc); //Left
    if (isMoveValid(pos1, pos2, 3)) hR = calculateH(move(3), goal, calc); //Right

    // Sort and Find Possible Moves
    vector<double> possibleMoves;
    vector<moves> m;

    // fill moves vector
    if (hU != 81) m.push_back(moves(hU, 0));
    if (hD != 81) m.push_back(moves(hD, 1));
    if (hL != 81) m.push_back(moves(hL, 2));
    if (hR != 81) m.push_back(moves(hR, 3));

    // sort moves vector
    sort(m.begin(), m.end(), compare());

    // fill possibleMoves with moves in correct order
    for (unsigned int i = 0; i < m.size(); i++) {
        possibleMoves.push_back(m.at(i).move);
    }

    vector<shared_ptr<Board>> returnBoards;

    //iterate over all moves and return all new states
    for (unsigned int i = 0; i < possibleMoves.size(); i++) {
        vector<vector<int>> temp = move(possibleMoves.at(i));

        // check knowns
        bool isKnown = false;
        for (unsigned int i = 0; i < knowns.size(); i++) {
            if (temp == knowns.at(i)->getVector()) {
                isKnown = true;
                break;
            }
        }

        // if its unique, push back a new board
        if (!isKnown) returnBoards.push_back(shared_ptr<Board>(new Board(shared_ptr<Board>(this), temp, goal, calc)));
    }
    
    explored = true;
    return returnBoards;
}

vector<shared_ptr<Board>> Board::ASearchUniform(const std::vector<std::vector<int>> &goal) {
    vector<shared_ptr<Board>> temp;

    int pos1, pos2;
    findPos(board, pos1, pos2, blanknum);

    // Check possible 4 next states and push all possible ones
    if (isMoveValid(pos1, pos2, 0)) temp.push_back(shared_ptr<Board>(new Board(shared_ptr<Board>(this), move(0), goal, 0))); //Up
    if (isMoveValid(pos1, pos2, 1)) temp.push_back(shared_ptr<Board>(new Board(shared_ptr<Board>(this), move(1), goal, 0))); //Down
    if (isMoveValid(pos1, pos2, 2)) temp.push_back(shared_ptr<Board>(new Board(shared_ptr<Board>(this), move(2), goal, 0))); //Left
    if (isMoveValid(pos1, pos2, 3)) temp.push_back(shared_ptr<Board>(new Board(shared_ptr<Board>(this), move(3), goal, 0))); //Right
    
    explored = true;

    return temp;
}

void const Board::printBoard() {
    cout << "Explored: " << explored
         << ", G(Depth): " << g
         << ", H: " << h
         << ", F:" << f << endl;
        
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board.at(i).size(); j++) {
            if (board.at(i).at(j) == 9) cout << "0, ";
            else cout << board.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::addChildren(vector<shared_ptr<Board>> t) {
    for (unsigned int i = 0; i < t.size(); i++) { 
        children.push_back(t.at(i)); 
        // t.at(i)->setParent(shared_ptr<Board>(this));
    }
}

void Board::addSingleChild(std::shared_ptr<Board> t) {
    children.push_back(t);
}

void const Board::setParent(shared_ptr<Board> p) {
    parent = p;
}