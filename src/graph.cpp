#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

#include "classes.h"

using namespace std;

Graph::Graph(vector<vector<int>> v, int c) {
    // set goal
    int cnt = 1;
    for (int i = 0; i < size; i++) {
        vector<int> tmp;
        for (int j = 0; j < size; j++) {
            tmp.push_back(cnt);
            cnt++;
        }
        goal.push_back(tmp);
    }

    initBoard = new Board(nullptr, v, goal, c);
    finalBoard = nullptr;
    allBoards.push_back(initBoard);
    calc = c;
}

Graph::~Graph() {
    initBoard = nullptr; delete initBoard;
    finalBoard = nullptr; delete finalBoard;

    // free allBoards
    for (int i = 0; i < allBoards.size(); i++) {
        allBoards.at(i) = nullptr; delete allBoards.at(i);
    }
}

void Graph::printRoute(Board *b) {
    // recursively print route from final board
    if (b == nullptr) return;

    printRoute(b->getParent());

    b->printBoard();
}

void Graph::printRoute() {
    printRoute(finalBoard);
}

void Graph::printAllBoards() {
    for (int i = 0; i < allBoards.size(); i++) {
        allBoards.at(i)->printBoard();
    }
}

void Graph::ASearch(Board* b, int calc, int g) {
    // check if we've hit our goal
    if (b->getVector() == goal) {
        finalBoard = b;
        return; 
    }

    // get all valid children and add them to graph
    vector<Board*> temp = b->ASearch(allBoards, goal, calc);
    b->addChildren(temp);
    for (unsigned int i = 0; i < temp.size(); i++) { 
        allBoards.push_back(temp.at(i)); 
    }

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
        vector<Board*> temp = q.at(i)->ASearchUniform(goal);

        
        //gets all possiblechildren
        for (int j = 0; j < temp.size(); j++) {
            // check for dups
            bool knowns = false;
            for (unsigned int i = 0; i < q.size(); i++) {
                if (q.at(i)->getVector() == b->getVector()) {
                    knowns = true;
                    break;
                }
            }

            // continue if no dups found
            if (!knowns) { 
                //push board to q
                q.push_back(temp.at(j));

                vector<Board*> tempChildVec = { temp.at(j )};
                q.at(i)->addChildren(tempChildVec);

                // break loop if we've found it
                if (temp.at(j)->getVector() == goal) {
                    flag = false;
                }
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