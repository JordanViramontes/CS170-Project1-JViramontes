#include <iostream>
#include<vector>
#include<fstream>
#include <string>
#include <cmath>
#include <algorithm>

#include "classes.h" //includes vector

using namespace std;

// additional helper functions
void fillVec(vector<vector<int>> &v, int size) {
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
    fillVec(v, size);
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

    parent = nullptr;
    
    fillVec(goal, size);
    fillTestVec(board, size); //TODO: CHANGE TO REGULAR
    cout << "TODO: FIX DEFAULT CASE FOR BOARD" << endl;

    // printVec(board);
    // printVec(goal);
};

Board::Board(Board *p, const vector<vector<int>> &v) {
    board = v;
    p->getConstants(goal, size, blanknum);
    parent = parent;
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

double Board::calculateH(const vector<vector<int>> &v, int calc) {  
    double total = 0;
    for (int i = 0; i < blanknum-1; i++) {
        int x1, x2, y1, y2;
        findPos(v, x1, y1, i+1);
        findPos(goal, x2, y2, i+1);
        // cout << "num: " << i+1
        //      << ", board: (" << x1 
        //      << ", " << y1 
        //      << "), goal: (" << x2 
        //      << ", " << y2 << ")\n";
        // cout << "num: " << i+1 << ", \tdistance: " << distance(x1, y1, x2, y2) << endl;
        total += distance(x1, y1, x2, y2);
    }
    // cout << "total: " << total << endl;
    return total;
}

int Board::smallestTotal(double U, double D, double L, double R) {
    double temp = min(min(min(U, D), L), R);
    
    if (temp == U) return 0;
    if (temp == D) return 1;
    if (temp == L) return 2;
    if (temp == R) return 3;
    return 0; //default (should never happen)
}

Board* Board::ASearch(int calc) {
    vector<vector<int>> tempVector = board;

    double hB = calculateH(board, calc);

    int pos1, pos2;
    findPos(board, pos1, pos2, blanknum);

    double hU = blanknum*blanknum, 
        hD = blanknum*blanknum, 
        hL = blanknum*blanknum, 
        hR = blanknum*blanknum;

    // Check possible 4 next states
    if (isMoveValid(pos1, pos2, 0)) hU = calculateH(move(0), calc); //Up
    if (isMoveValid(pos1, pos2, 1)) hD = calculateH(move(1), calc); //Down
    if (isMoveValid(pos1, pos2, 2)) hL = calculateH(move(2), calc); //Left
    if (isMoveValid(pos1, pos2, 3)) hR = calculateH(move(3), calc); //Right

    // cout << "totals: " << hU << ", " << hD 
    //     << ", " << hL << ", " << hR 
    //     << "\tBoard: " << hB << endl;

    tempVector = move(smallestTotal(hU, hD, hL, hR));

    return new Board(this, tempVector);
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