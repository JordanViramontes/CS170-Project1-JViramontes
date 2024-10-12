#include<vector>
#include<fstream>
#include <iostream>
#include <string>
// #include <cmath>

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

// UI

UI::UI() {
    //default size is 3x3
    size = 3;
    board = Board(0, size);
};


// Board

Board::Board() {
    size = 3;
    searchType = 0;
    fillVec(goal, size);
    fillTestVec(board, size); //TODO: CHANGE TO REGULAR
    cout << "TODO: FIX DEFAULT CASE FOR BOARD" << endl;
    printVec(board);
    // printVec(goal);
};

Board::Board(bool scramble, int size) {

};

void Board::findBlank(int &pos1, int &pos2) {
    //find where the blank is at
    int blankNum = board.size() * board.size();
    cout << "blankNum: " << blankNum << endl;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.at(i).size(); j++) {
            if (board.at(i).at(j) == blankNum) {
                pos1 = i;
                pos2 = j;
                return;
            }
        }
    }
    cout << "Could not find blank space. Returning 1,1" << endl; 
    pos1 = 1;   pos2 = 1;
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

void Board::move(int move) {
    // get blank's current position
    int pos1, pos2;
    findBlank(pos1, pos2);
    cout << "pos1: " << pos1 << ", pos2: " << pos2 << endl;

    // Check for valitiy before moving
    if (!isMoveValid(pos1, pos2, move)) {
        cout << "Move is not valid, returning";
        return;
    }

    // position of blank
    int blank = board.at(pos1).at(pos2);

    switch(move) {
        case (0) : { //up
            cout << "UP: " << endl;
            int temp = board.at(pos1-1).at(pos2);
            board.at(pos1-1).at(pos2) = blank;
            board.at(pos1).at(pos2) = temp;
            break;
        }
        case (1) : { //down
            cout << "DOWN: " << endl;
            int temp = board.at(pos1+1).at(pos2);
            board.at(pos1+1).at(pos2) = blank;
            board.at(pos1).at(pos2) = temp;
            break;
        }
        case (2) : { //left
            cout << "LEFT: " << endl;
            int temp = board.at(pos1).at(pos2-1);
            board.at(pos1).at(pos2-1) = blank;
            board.at(pos1).at(pos2) = temp;
            break;
        }
        case (3) : { //right
            cout << "RIGHT: "<< endl;
            int temp = board.at(pos1).at(pos2+1);
            board.at(pos1).at(pos2+1) = blank;
            board.at(pos1).at(pos2) = temp;
            break;
        }
        default: {
            cout << "SWITCH-CASE ERROR WHEN MOVING" << endl;
            break;
        }
    }

    cout << "PRINTING MOVED VEC: " << endl;
    printVec(board);
};  

