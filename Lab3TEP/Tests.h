#ifndef TESTS_H
#define TESTS_H

#include <string>

using namespace std;

class Tests {
public:
    Tests(const string& testTreeFormula = "", const string& testErrorMessage = "", const int& intToTest = 0);

    void run();

private:
    string treeFormula;
    string errorMessage;
    int testInt;

    string TEST_SAVE_PATH = "D:/syf/output_test.txt";
    
    void testSaveTree();
    void testSaveInt();
    void testSaveError();
};

#endif