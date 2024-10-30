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
                cout << "Invalid input, try again\n" << endl;
                break;
            }
        }
    }

}

void UI::randomBoard() {
    int c = setCalc();

    // check our calc
    if (c < 0) {
        quitSequence();
        return;
    }

    vector<vector<int>> v = {{ 1, 9, 3 }, { 4, 2, 6 }, { 7, 5, 8 }};

    cout << "CHECK: " << endl;
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = 0; j < v.at(i).size(); j++) {
            cout << v.at(i).at(j) << ", ";
        }
        cout << endl;
    }

    g = new Graph(v, c);
}

void UI::setBoard(int c) {
    vector<vector<int>> v;
    vector<string> getInput;
    int size = 3;
    bool flag = true;

    //make sure we're good
    if (c < 0) {
        quitSequence();
        return;
    }

    while(flag) {
        bool isInputFine = true;
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
        
        for (int s = 0; s < size; s++) {
            vector<int> temp;

            //input of nothing
            if (getInput.at(s) == "") {
                isInputFine = false;
            }
            
            for (unsigned int i = 0; i < getInput.at(s).size(); i++) {
                if (getInput.at(s).at(i) != ' ') {
                    // if invalid
                    if (getInput.at(s).at(i) < '0' || 
                        getInput.at(s).at(i) > '8' ||
                        (int)getInput.at(s).size() < size) 
                        {
                            isInputFine = false;
                        }

                    // set input 0 -> 9 internally
                    if (getInput.at(s).at(i) == '0') 
                        temp.push_back(9);
                    
                    // normally push back
                    else temp.push_back( (int)getInput.at(s).at(i) - '0' );
                }

                if (temp.size() >= 3) {
                    v.push_back(temp);
                    break;
                }
            }
        }

        // check duplicate numbers
        for (int k = 1; k < (size*2)+1; k++) {
            bool temp = false;

            for (unsigned int j = 0; j < v.size(); j++) {
                for (unsigned int i = 0; i < v.at(j).size(); i++) {
                    if (v.at(i).at(j) == k) {
                        if (temp) {
                            isInputFine = false;
                        }
                        temp = true;
                    }
                }
            } 
        }

        if (isInputFine) flag = false;
        else {
            cout << "\nInvalid Input, try again\n" << endl;
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
                cout << "Invalid input, try again\n" << endl;
                break;
            }
        }
    }
}

void UI::printRoutesSequence() {
    while(true) {
        cout << "Would you like to print the direct route to the goal, or the full graph?"
            << "\nType:\t\"1\" for the direct route," 
            << "\n\t\"2\" for the full graph,"
            << "\n\t\"3\" for both,"
            << "\nor \"q\" to quit:"
            << "\n\t> ";

        string getInput;
        getline(cin, getInput);
        cout << endl;

        if (getInput.size() == 0) getInput = 'q';

        switch (getInput.at(0)) {
            case ('1'): {
                printRoute();
                return;
                break;
            }
            case ('2'): {
                printAllBoards();
                return;
                break;
            }
            case ('3'): {
                printAllBoards();
                printRoute();
                return;
                break;
            }
            case ('q'): {
                quitSequence();
                return;
                break;
            }
            default: {
                cout << "Invalid input, try again\n" << endl;
                break;
            }
        }
    }
}

void UI::ASearch() {
    //help me gob
    cout << "\nSearching ... \n\n";
    int temp = g->ASearch();
    cout << "GOAL!!" 
         << "\n\nThe total amount of nodes expanded were: " << temp 
         << ".\nThe depth of the goal was: " << g->getDepth() << ".\n\n";
}

void UI::printRoute() {
    cout << "Printing Route to Goal State: \n\n";
    g->printRoute(); 
}

void UI::printAllBoards() {
    cout << "Printing entire Graph: \n\n";
    g->printAllBoards();
}