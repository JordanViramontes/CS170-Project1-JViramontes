#include <iostream>
#include <fstream>

#include "classes.h"

using namespace std;

void UI::quitSequence() {
    cout << "Quitting...\n\n";
    isComplete = true;
}

void UI::startingSequence() {
    while(true) {
        cout << "Welcome to 862284516 8 puzzle solver."
            << "\n Type \"1\" to use a default puzzle, \"2\" to enter your own puzzle, or \"q\" to quit:"
            << "\n\t> ";

        string getInput;
        getline(cin, getInput);
        cout << endl;

        if (getInput.size() == 0) getInput = 'q';

        switch (getInput.at(0)) {
            case ('1'): {
                randomBoard();
                return;
                break;
            }
            case ('2'): {
                setBoard( setCalc() );
                return;
                break;
            }
            case ('q'): {
                quitSequence();
                return;
                break;
            }
            default: {
                cout << "Invalid input, try again" << endl;
                break;
            }
        }
    }

}

void UI::randomBoard() {
    cout << "TODO: RANDOM BOARD" << endl << endl << endl;
}

void UI::setBoard(int c) {
    vector<vector<int>> v;
    vector<string> getInput;
    int cnt = 1;
    int size = 3;

    //make sure we're good
    if (c < 0) {
        quitSequence();
        return;
    }

    cout << "Enter your puzzle with a space between each number, Enter 0 for blank\n";
    cout << "Enter the first row: "
         << "\n\t> ";
    
    string temp;
    getline(cin, temp);
    getInput.push_back(temp);

    cout << "Enter the second row: "
         << "\n\t> ";
    
    getline(cin, temp);
    getInput.push_back(temp);

    cout << "Enter the third row: "
         << "\n\t> ";
    
    getline(cin, temp);
    getInput.push_back(temp);
    
    for (unsigned int s = 0; s < size; s++) {
        vector<int> temp;
        
        for (unsigned int i = 0; i < getInput.at(s).size(); i++) {
            if (getInput.at(s).at(i) != ' ') {
                

                // if invalid
                if (getInput.at(s).at(i) < '0' || 
                    getInput.at(s).at(i) > '8' ||
                    getInput.at(s).size() < size) 
                    {
                        quitSequence();
                        return;
                    }

                // set input 0 -> 9 internally
                if (getInput.at(s).at(i) == '0') 
                    temp.push_back(9);
                
                // normally push back
                else temp.push_back( (int)getInput.at(s).at(i) - '0' );
            }

            if (temp.size() >= 3) {
                cout << endl;
                v.push_back(temp);
                break;
            }
        }
    }
    
    // check duplicate numbers
    for (unsigned int k = 1; k < (size*2)+1; k++) {
        bool temp = false;

        for (unsigned int j = 0; j < v.size(); j++) {
            for (unsigned int i = 0; i < v.at(j).size(); i++) {
                if (v.at(i).at(j) == k) {
                    if (temp) {
                        quitSequence();
                        return;
                    }
                    temp = true;
                }
            }
        } 
    }

    g = new Graph(v, c);
}

int UI::setCalc() {
    while(true) {
        cout << "Enter your choice of algorithm"
            << "\nType:\t\"1\" for Uniform Cost Search," 
            << "\n\t\"2\" for Misplaced Tile heuristic,"
            << "\n\t\"3\" for Euclidean distance heuristic."
            << "or \"q\" to quit:"
            << "\n\t> ";

        string getInput;
        getline(cin, getInput);
        cout << endl;

        if (getInput.size() == 0) getInput = 'q';

        switch (getInput.at(0)) {
            case ('1'): {
                return 0;
                break;
            }
            case ('2'): {
                return 1;
                break;
            }
            case ('3'): {
                return 2;
                break;
            }
            case ('q'): {
                return -1;
                break;
            }
            default: {
                cout << "Invalid input, try again" << endl;
                break;
            }
        }
    }
}

void UI::ASearch() {
    //help me gob
    int temp = g->ASearch();
    cout << "GOAL!!" 
         << "\n\nThe total amount of nodes expanded were: " << temp 
         << ".\nThe depth of the goal was: " << g->getDepth() << ".\n\n";
}

void UI::printRoute() {
    g->printRoute();
}