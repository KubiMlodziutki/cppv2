#include "Counters.h"
#include <iostream>
using namespace std;

Counters::Counters() : copyCount(0), moveCount(0) {}

void Counters::incrementCopy() {
    copyCount++;
}

void Counters::incrementMove() {
    moveCount++;
}

int Counters::getCopyCount() const {
    return copyCount;
}

int Counters::getMoveCount() const {
    return moveCount;
}

void Counters::copyAlert() {
    cout << COPIES_COUNT << copyCount << endl;
}

void Counters::moveAlert() {
    cout << MOVES_COUNT << moveCount << endl;
}
