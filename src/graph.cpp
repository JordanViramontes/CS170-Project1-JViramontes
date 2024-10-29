#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "classes.h"

using namespace std;

Graph::Graph() {
    allBoards.push_back(nullptr);
    initBoard = nullptr;
    finalBoard = nullptr;
    calc = 0;
}

Graph::Graph(vector<vector<int>> v, int c) {
    initBoard = new Board(nullptr, v, c);
    finalBoard = nullptr;
    allBoards.push_back(initBoard);

    calc = c;
}

Graph::Graph(int c) {
    // if calc = 0:uniform, 1:misplaced tile, 2:euclidean
    initBoard = new Board();
    allBoards.push_back(initBoard);
    
    calc = c;
}

void Graph::printRoute(Board *b, int depth) {
    // recursively print route from final board
    if (b == nullptr) return;

    printRoute(b->getParent(), depth-1);

    cout << "Explored: " << b->getExplored()
         << ", Depth: " << b->getDepth() 
         << ", H: " << b->getH() 
         << ", F:" << b->getF() << endl;
    b->printBoard();
}

void Graph::printRoute() {
    printRoute(finalBoard, finalBoard->getDepth());
}

void Graph::printAllBoards() {
    for (int i = 0; i < allBoards.size(); i++) {
        cout << "Explored: " << allBoards.at(i)->getExplored()
             << ", Depth: " << allBoards.at(i)->getDepth() 
             << ", H: " << allBoards.at(i)->getH() 
             << ", F:" << allBoards.at(i)->getF() << endl;
        allBoards.at(i)->printBoard();
    }
}

void Graph::ASearch(Board* b, int calc, int g) {
    // check if we've hit our goal
    if (b->getVector() == b->getGoal()) {
        finalBoard = b;
        return; 
    }

    // get all valid children and add them to graph
    vector<Board*> temp = b->ASearch(allBoards, calc);
    b->addChildren(temp);
    addBoardVec(temp);

    //check all boards for lower f value
    double minf = -1;
    Board* minBoard = nullptr;

    for (unsigned int i = 1; i < allBoards.size(); i++) {
        if (allBoards.at(i)->getExplored()) continue;
        if (minf < 0) {
            minf = allBoards.at(i)->getF();
            minBoard = allBoards.at(i);
        }
        if (allBoards.at(i)->getF() < minf) {
            minf = allBoards.at(i)->getF();
            minBoard = allBoards.at(i);
        }
    }

    ASearch(minBoard, calc, minBoard->getDepth()+1);

    minBoard = nullptr;
    delete minBoard;
}

vector<Board*> Graph::ASearchUniform(Board* b) {
    //essentially BFS
    vector<Board*> q;
    q.push_back(b); //start with init node
    unsigned int i = 0; //keep track of q (for bfs)
    bool flag = true;

    while (flag) {
        vector<Board*> temp = q.at(i)->ASearchUniform();

        
        //gets all possiblechildren
        for (int j = 0; j < temp.size(); j++) {
            // check for dups
            if (!checkKnowns(q, temp.at(j))) { 
                //push board to q
                q.push_back(temp.at(j));
                q.at(i)->addSingleChild(temp.at(j));

                // break loop if we've found it
                if (temp.at(j)->getVector() == temp.at(j)->getGoal()) {
                    flag = false;
                }

                // set nodes as explored
                q.at(i)->setExplored();
            }
        }

        i++;
    }
    return q;
}

int Graph::ASearch() {
    if (calc == 0) {
        allBoards = ASearchUniform(initBoard);
        finalBoard = allBoards.at(allBoards.size()-1);
    }
    else ASearch(initBoard, calc, 1);

    int expanded = 0;
    for (unsigned int i = 0; i < allBoards.size(); i++) {
        if (allBoards.at(i)->getExplored()) expanded++;
    }
    return expanded;
}

bool Graph::checkKnowns(const vector<Board*> &v, Board* b) {
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i)->getVector() == b->getVector()) return true;
    }
    return false;
}
