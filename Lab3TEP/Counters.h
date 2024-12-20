#ifndef COUNTERS_H
#define COUNTERS_H

#include <iostream>
#include <string>

using namespace std;

class Counters {
public:
    Counters();
    void incrementCopy();
    void incrementMove();

    int getCopyCount() const;
    int getMoveCount() const;

    void copyAlert();
    void moveAlert();

private:
    int copyCount;
    int moveCount;
    
    string COPIES_COUNT = "Copies: ";
    string MOVES_COUNT = "Moves: ";
};

#endif
