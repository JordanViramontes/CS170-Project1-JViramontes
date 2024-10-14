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

void Graph::printNodes(Board* b, int depth) {
    if (b == nullptr) return; //base case
    
    b->printBoard();
    for (int i = 0; i < b->children.size(); i++) {
        cout << "Depth: " << depth << endl;
        printNodes(b->children.at(i), depth+1);
    }
}

void Graph::printGraph() {
    printNodes(initBoard, 0);
}

void Graph::ASearch(Board* b, int calc, int g) {
    if (b->getVector() == b->getGoal()) return; // check if we've hit our goal

    Board* temp = b->ASearch(calc);
    b->children.push_back(temp);

    // cout << "G: " << g << endl;
    // temp->printBoard();

    ASearch(temp, calc, g+1);
}

void Graph::ASearch(int calc) {
    ASearch(initBoard, calc, 1);
}
