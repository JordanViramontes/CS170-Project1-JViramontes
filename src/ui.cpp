#include <iostream>
#include <fstream>

#include "classes.h"

using namespace std;

void UI::quitSequence() {
    cout << "Quitting..." << endl << endl;
    isComplete = true;
}

void UI::startingSequence() {
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
            break;
        }
        case ('2'): {
            setBoard();
            break;
        }
        case ('q'): {
            quitSequence();
            break;
        }
        default: {
            cout << "Invalid input, try again" << endl;
            break;
        }
    }
}

void UI::randomBoard() {
    cout << "TODO: RANDOM BOARD" << endl << endl << endl;
}

void UI::setBoard() {
    vector<vector<int>> v;
    vector<string> getInput;
    int cnt = 1;
    int size = 3;

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
                    getInput.at(s).at(i) > '9' ||
                    getInput.at(s).size() < size) 
                    {
                        quitSequence();
                        return;
                    }

                temp.push_back( (int)getInput.at(s).at(i) - '0' );
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
    

    for (unsigned int j = 0; j < v.size(); j++) {
        for (unsigned int i = 0; i < v.at(j).size(); i++) {
            cout << v.at(j).at(i) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}
