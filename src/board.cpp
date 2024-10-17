#include <iostream>
#include<vector>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>

#include "classes.h" //includes vector

using namespace std;

// additional helper functions
void Board::fillVec(vector<vector<int>> &v, int size) {
    int cnt = 1;

    for (int i = 0; i < size; i++) {
        vector<int> tmp;
        for (int j = 0; j < size; j++) {
            tmp.push_back(cnt);
            cnt++;
        }
        v.push_back(tmp);
    }
}

void fillTestVec(vector<vector<int>> &v, int size) {
    int cnt = 1;
    for (int i = 0; i < size; i++) {
        vector<int> tmp;
        for (int j = 0; j < size; j++) {
            tmp.push_back(cnt);
            cnt++;
        }
        v.push_back(tmp);
    }

    bool a = true;
    if (a) {
        cout << endl << "TODO: CHANGE BOARD FROM PRESET 123-489-765" << endl;

        v.at(0).at(0) = 1;
        v.at(0).at(1) = 2;
        v.at(0).at(2) = 3;

        v.at(1).at(0) = 4;
        v.at(1).at(1) = 8;
        v.at(1).at(2) = 9;

        v.at(2).at(0) = 7;
        v.at(2).at(1) = 6;
        v.at(2).at(2) = 5;
    }
    else {
        cout << endl << "TODO: CHANGE BOARD FROM PRESET 123-456-978" << endl;

        v.at(0).at(0) = 1;
        v.at(0).at(1) = 2;
        v.at(0).at(2) = 3;

        v.at(1).at(0) = 4;
        v.at(1).at(1) = 5;
        v.at(1).at(2) = 6;

        v.at(2).at(0) = 9;
        v.at(2).at(1) = 7;
        v.at(2).at(2) = 8;
    }
}

void printVec(const vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(i).size(); j++) {
            cout << v.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

// Board

Board::Board() {
    size = 3;
    blanknum = 9;
    h = 9.0;
    depth = 0;

    parent = nullptr;
    
    fillVec(goal, size);
    fillTestVec(board, size); //TODO: CHANGE TO REGULAR
    cout << "TODO: FIX DEFAULT CASE FOR BOARD" << endl;

    // printVec(board);
    // printVec(goal);
};

Board::Board(Board *p, const vector<vector<int>> &v, int calc) {
    board = v;
    p->getConstants(goal, size, blanknum, depth);
    parent = p;
    h = calculateH(board, goal, calc);
    // cout << "new H: " << h << endl;
    // printBoard();
}

void Board::findPos(const vector<vector<int>> &v, int &pos1, int &pos2, int num) {
    //Find position of number
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(i).size(); j++) {
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
            if (pos1+1 > board.size()-1) return false;
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
            if (pos2+1 > board.size()-1) return false;
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
    // cout << "pos1: " << pos1 << ", pos2: " << pos2 << endl;

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
            for (int i = 0; i < v.size(); i++) {
                for (int j = 0; j < v.at(i).size(); j++) {
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
                findPos(goal, x2, y2, i+1);
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

vector<double> Board::smallestTotal(double U, double D, double L, double R) {
    vector<double> ret;
    vector<moves> m;

    // fill moves vector
    if (U != 81) m.push_back(moves(U, 0));
    if (D != 81) m.push_back(moves(D, 1));
    if (L != 81) m.push_back(moves(L, 2));
    if (R != 81) m.push_back(moves(R, 3));

    // sort moves vector
    sort(m.begin(), m.end(), compare());

    // fill ret with moves in correct order
    for (int i = 0; i < m.size(); i++) {
        ret.push_back(m.at(i).move);
    }

    return ret;
}

bool Board::checkKnowns(vector<Board*> &knowns, vector<vector<int>> &v) {
    for (int i = 0; i < knowns.size(); i++) {
        if (v == knowns.at(i)->getVector()) return true;
    }
    return false;
}

Board* Board::ASearch(vector<Board*> &knowns, int calc) {
    vector<vector<int>> tempVector = board;

    double hB = calculateH(board, goal, calc);

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

    cout << "totals: " << hU << ", " << hD 
        << ", " << hL << ", " << hR 
        << "\tBoard: " << hB << endl;

    vector<double> possibleMoves = smallestTotal(hU, hD, hL, hR);

    //iterate over all moves and return when we dont have a duplicate
    for (int i = 0; i < possibleMoves.size(); i++) {
        vector<vector<int>> temp = move(possibleMoves.at(i));
        if (!checkKnowns(knowns, temp)) return new Board(this, temp, calc);
        cout << "hehe" << endl;
    }
    
    return nullptr;
}

vector<Board*> Board::ASearchUniform() {
    vector<Board*> temp;

    int pos1, pos2;
    findPos(board, pos1, pos2, blanknum);

    // cout << "INIT: " << endl;
    // printVec(board);

    // Check possible 4 next states and push all possible ones
    if (isMoveValid(pos1, pos2, 0)) temp.push_back(new Board(this, move(0), 0)); //Up
    if (isMoveValid(pos1, pos2, 1)) temp.push_back(new Board(this, move(1), 0)); //Down
    if (isMoveValid(pos1, pos2, 2)) temp.push_back(new Board(this, move(2), 0)); //Left
    if (isMoveValid(pos1, pos2, 3)) temp.push_back(new Board(this, move(3), 0)); //Right
    
    return temp;
}

void const Board::printBoard() {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.at(i).size(); j++) {
            cout << board.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}