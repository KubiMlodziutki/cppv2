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
    string DEFAULT_FORMULA = "* + a b c";
    string DEFAULT_ERROR = "Error happened";

    string TEST1 = "--- Test 1: MySmartPointer as template ---";
    string TEST2 = "--- Test 2: Operator= in MySmartPointer ---";
    string TEST3 = "--- Test 3: MySmartPointer static memory test ---";
    string TEST4 = "--- Test 4: Move operator in Tree ---";
    string TEST5 = "--- Test 5: Operator=, operator+, move operator and constructor in Tree ---";

    string VALUE_SMART_INT = "Value stored in smart int pointer: ";
    string VALUE_SMART_OBJ = "Value stored in smart object pointer: ";
    string VALUE_SMART_STATIC_OBJ = "Value stored in smart static object pointer: ";
    string VALUE_SMART_OBJ_SET = "Value stored in smart object pointer after set: ";
    string TEST_TREES = "Trees used to test:";
    string TREE_AFTER_MOVE = "Tree after move:";
    string MOVED_TREE = "Moved tree after move assignment (expected nothing below):";
    string SUMMED_TREE = "Tree after operator+:";
    string ASSIGNED_TREE = "Tree after operator=:";
    string TREE_AFTER_MOVE_CONSTRUCTOR = "Tree after move constructor from other:";
    string MOVED_TREE_CONSTRUCTOR = "Moved tree after move constructor (expected nothing below):";
    string OVERALL_TEST_COUNTERS = "Overall counters:";
    string LOOP_TEST_COUNTERS_MS = "Counter statistics after using move semantics:";
    string LOOP_TEST_COUNTERS_NO_MS = "Counter statistics without using move semantics:";
    string TEST_COUNTERS_LOOP_PROCEDURE = "Starting experiment with/without using move semantics";

    int DEFAULT_INT = 1;
    int LOOP_TEST = 10;
    int SMART_INT = 15;
    int ptrOBJ_INT1 = 10;
    int ptrOBJ_INT2 = 15;
    int ptrOBJ_INT3 = 30;
    int ptrOBJ_INT4 = 45;
    int staticOBJ_INT = 321;

    string TEST_TREE_FORMULA_1 = "+ a b";
    string TEST_TREE_FORMULA_2 = "* c d";
    string TEST_TREE_FORMULA_3 = "+ e f";
    string TEST_TREE_FORMULA_4 = "* g h";
    string TEST_TREE_FORMULA_5 = "+ i j";

    void testSaveTree();
    void testSaveInt();
    void testSaveError();
    void testPointers();
};

#endif