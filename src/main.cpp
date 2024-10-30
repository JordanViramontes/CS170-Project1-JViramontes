/*
DEVELOPED BY JORDAN VIRAMONTES

Disclaimer:
ALL code in this project was written by me and is all original. I used sources like 
geeksforgeeks to help understand the algorithm, however I refused to look at any of the 
provided code in order to figure it out myself.

---
Sources used for learning and understanding the A* Search Algorithm:
* https://www.geeksforgeeks.org/a-search-algorithm/
* https://www.codecademy.com/resources/docs/ai/search-algorithms/a-star-search

Source for double checking A* Search Algorithm:
* https://deniz.co/8-puzzle-solver/

Source for help with using sort() function with structs
* https://stackoverflow.com/questions/1380463/how-do-i-sort-a-vector-of-custom-objects
---
*/

#include <iostream>
#include <string>
#include <fstream>

// #include "board.cpp"
// #include "graph.cpp"
// #include "ui.cpp"
#include "classes.h"

using namespace std;

int main() {

    while (true) {
        UI ui;

        if (!ui.startingSequence()) break;

        ui.ASearch();

        if (!ui.printRoutesSequence()) break;
    }
    

    return 0;
}