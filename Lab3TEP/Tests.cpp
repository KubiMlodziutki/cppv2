#include "Tests.h"
#include "ResultSaveState.h"
#include "Tree.h"
#include "Error.h"
#include "Result.h"

using namespace std;

Tests::Tests(const string& testTreeFormula, const string& testErrorMessage, const int& intToTest)
    : treeFormula(testTreeFormula), errorMessage(testErrorMessage), testInt(intToTest) {}

void Tests::run() {
    testSaveTree();
    testSaveInt();
    testSaveError();
}

void Tests::testSaveTree() {
    ResultSaveState saver(TEST_SAVE_PATH);
    Result<Tree*, Error> treeResult = Tree::growTree<Tree*, Error>(treeFormula);
    saver.saveToFile(treeResult);
}

void Tests::testSaveInt() {
    ResultSaveState saver(TEST_SAVE_PATH);
    Result<int, Error> intResult = Result<int, Error>::ok(testInt);
    saver.saveToFile(intResult);
}

void Tests::testSaveError() {
    ResultSaveState saver(TEST_SAVE_PATH);

    Error* error = new Error(errorMessage);
    vector<Error*> errors = { error };
    Result<double, Error> errorResult(errors);
    saver.saveToFile(errorResult);

    delete error;
}