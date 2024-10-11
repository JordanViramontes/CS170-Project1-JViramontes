#include<vector>
#include<fstream>
#include <iostream>
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
    fillTestVec(board, size);
    printVec(board);
    printVec(goal);
};

Board::Board(bool scramble, int size) {

};

void Board::move(vector<vector<int>> &v, int move) {

};