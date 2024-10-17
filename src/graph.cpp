#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "classes.h"

using namespace std;

Graph::Graph() {
    initBoard = new Board();
    allBoards.push_back(initBoard);
}

Graph::Graph(int c) {
    // if calc = 0:uniform, 1:misplaced tile, 2:euclidean
    initBoard = new Board();
    allBoards.push_back(initBoard);
    
    calc = c;
}

void Graph::printGraph(Board* b, int depth) { //DFS
    if (b == nullptr) return; //base case

    cout << "Depth: " << depth 
         << ", H: " << b->getH() << endl;
    b->printBoard();

    for (int i = 0; i < b->children.size(); i++) { //print children
        printGraph(b->children.at(i), depth+1);
    }
}

void Graph::printGraphUniform(Board *b, int depth) {
    if (b == nullptr) return;

    printGraphUniform(b->getParent(), depth-1);

    cout << "Depth: " << depth << endl;
    b->printBoard();
}

void Graph::printGraph() {
    // The "correct" Board is at the end, recursively look at parents
    if (calc == 0) printGraphUniform(allBoards.at(allBoards.size()-1), 
                                     allBoards.at(allBoards.size()-1)->getDepth());
    //euclideon and missing tile
    else printGraph(initBoard, 0);
}

void Graph::printAllBoards() {
    for (int i = 0; i < allBoards.size(); i++) {
        cout << "Depth: " << allBoards.at(i)->getDepth() << endl;
        allBoards.at(i)->printBoard();
    }
}

void Graph::ASearch(Board* b, int calc, int g) {
    if (b->getVector() == b->getGoal()) return; // check if we've hit our goal
    if (b == nullptr) ASearch(b->parent, calc, g-1);
    
    Board* temp = b->ASearch(allBoards, calc);
    allBoards.push_back(temp);
    b->children.push_back(temp);

    ASearch(temp, calc, g+1);
}

vector<Board*> Graph::ASearchUniform(Board* b) {
    //essentially BFS
    vector<Board*> q;
    q.push_back(b); //start with init node
    unsigned int i = 0; //keep track of q (for bfs)
    bool flag = true;

    while (flag) {
        //gets all possiblechildren
        vector<Board*> temp = q.at(i)->ASearchUniform();

        for (int j = 0; j < temp.size(); j++) {
            if (!checkKnowns(q, temp.at(j))) { // check for dups
                //push board to q
                q.push_back(temp.at(j));
                q.at(i)->children.push_back(temp.at(j));

                // break loop if we've found it
                if (temp.at(j)->getVector() == temp.at(j)->getGoal()) {
                    flag = false;
                }
                // cout << "NEW: " << endl;
                // temp.at(j)->printBoard();
            }
            // else cout << "OLD" << endl;
            // temp.at(j)->printBoard();
        }

        i++;
    }
    return q;
}

void Graph::ASearch() {
    printAllBoards();
    if (calc == 0) allBoards = ASearchUniform(initBoard);
    else ASearch(initBoard, calc, 1);
}

bool Graph::checkKnowns(const vector<Board*> &v, Board* b) {
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i)->getVector() == b->getVector()) return true;
    }
    return false;
}


