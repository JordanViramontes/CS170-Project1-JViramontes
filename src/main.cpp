/*
DEVELOPED BY JORDAN VIRAMONTES

Disclaimer:
ALL code in this project was written by me, although I used sources like geeksforgeeks 
to help understand the algorithm, I refused to look at any of the provided code in 
order to figure it out myself.

---
Sources used for learning and understanding the A* Search Algorithm:
* https://www.geeksforgeeks.org/a-search-algorithm/
* https://www.codecademy.com/resources/docs/ai/search-algorithms/a-star-search

Source for double checking A* Search Algorithm answers:
* https://deniz.co/8-puzzle-solver/
---
*/

#include <iostream>
#include <fstream>

#include "board.cpp"
#include "graph.cpp"

using namespace std;

int main() {
    Graph g(0);
    // g.ASearch(0);
    g.ASearch();
    g.printGraph();
    // g.printGraph();
    // Board b;
    // b.ASearch(0);

    return 0;
}