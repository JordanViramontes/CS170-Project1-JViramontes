#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <memory>

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

    // initBoard = new Board(nullptr, v, goal, c);
    initBoard = shared_ptr<Board>(new Board(nullptr, v, goal, c));
    finalBoard = nullptr;
    allBoards.push_back(initBoard);
    calc = c;
}

void Graph::printRoute(std::shared_ptr<Board> b) {
    // recursively print route from final board
    if (b == nullptr) return;

    printRoute(b->getParent());

    b->printBoard();
}

void Graph::printRoute() {
    printRoute(finalBoard);
}

void Graph::printAllBoards() {
    for (unsigned int i = 0; i < allBoards.size(); i++) {
        allBoards.at(i)->printBoard();
    }
}

void Graph::ASearch(std::shared_ptr<Board> b, int calc, int g) {
    // check if we've hit our goal
    if (b->getVector() == goal) {
        finalBoard = b;
        return; 
    }

    // get all valid children and add them to graph
    vector<std::shared_ptr<Board>> temp = b->ASearch(allBoards, goal, calc);
    b->addChildren(temp);
    for (unsigned int i = 0; i < temp.size(); i++) { 
        allBoards.push_back(temp.at(i)); 
    }

    //check all boards for lower f value
    double minf = -1;
    std::shared_ptr<Board> minBoard = nullptr;

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
}

void Graph::ASearchUniform(shared_ptr<Board> b) {
    //essentially BFS, allBoards already contains the initBoard b
    unsigned int i = 0; //keep track of q (for bfs)
    bool flag = true;

    // check initboard
    if (b->getVector() == goal) {
        return;
    }

    while (flag) {
        // gets all possiblechildren
        cout << "CURRENT: " << endl;
        allBoards.at(i)->printBoard();
        vector<shared_ptr<Board>> temp = allBoards.at(i)->ASearchUniform(goal);
        
        // iterate over next moves
        for (unsigned int j = 0; j < temp.size(); j++) {
            if (!flag) continue;

            // check for dups
            cout << "TEST KNOWN FROM TEMP:";
                temp.at(j)->printBoard();
            bool knowns = false;
            for (unsigned int k = 0; k < allBoards.size(); k++) {
                
                // if total boards is the same as our current move
                if (allBoards.at(k)->getVector() == temp.at(j)->getVector()) {
                    cout << "known!" << endl;
                    knowns = true;
                    break;
                }
            }
            cout << "b" << endl;

            // go to next loop if dups found
            if (knowns) continue;

            // push board to q
            cout << "TEST: " << endl;
            temp.at(j)->printBoard();

            // add board to allBoards and set children
            allBoards.push_back(temp.at(j));
            // allBoards.at(i)->addSingleChild(temp.at(j));

            // break loop if we've found it
            if (temp.at(j)->getVector() == goal) {
                cout << "FOUND IT" << endl;
                flag = false;          
            }
        }
        
        cout << "flag: " << flag << endl;
        i++;
    }
    cout << "? " << endl;
    return;
}

int Graph::ASearch() {
    if (calc == 0) {
        ASearchUniform(initBoard);
        cout << "check" << endl;
        finalBoard = allBoards.at(allBoards.size()-1);
        cout << "check2" << endl;
    }
    else ASearch(initBoard, calc, 1);

    int expanded = 0;
    for (unsigned int i = 0; i < allBoards.size(); i++) {
        if (allBoards.at(i)->getExplored()) expanded++;
    }
    return expanded;
}
