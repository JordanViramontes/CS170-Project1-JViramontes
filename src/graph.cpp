#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "classes.h"

using namespace std;

Graph::Graph() {
    Board temp;
    initBoard = new Board();
    allBoards.push_back(initBoard);
}

void Graph::printNodes(Board* b) {
    if (b == nullptr) return; //base case
    
    b->printBoard();
    // for (int i = 0; i < b->children.size(); i++) {
    //     printNodes(b->children.at(i));
    // }
}

void Graph::printGraph() {
    cout << "A" << endl;
    printNodes(initBoard);
}

void Graph::ASearch(Board* b, int calc, int g) {
    if (b->getVector() == b->getGoal()) return; // check if we've hit our goal

    Board* temp = b->ASearch(calc);
    
    cout << "G: " << g << endl;
    temp->printBoard();

    ASearch(temp, calc, g+1);
}

void Graph::ASearch(int calc) {
    ASearch(initBoard, calc, 1);
}
