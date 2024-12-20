#ifndef RESULTSAVESTATE_H
#define RESULTSAVESTATE_H

#include "Result.h"
#include "Error.h"
#include "Tree.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class ResultSaveState {
public:
    ResultSaveState(const string& fileName);

    template <typename T>
    void saveToFile(Result<T, Error>& result);

private:
    string fileName;
    string ERROR_RESULT = "Error: ";

    ofstream openFileAtEnd();
    void saveErrors(const vector<Error*>& errors);
    void saveTree(const Tree* tree);
};

template <>
void ResultSaveState::saveToFile<Tree*>(Result<Tree*, Error>& result);

#endif
