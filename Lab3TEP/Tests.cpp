#include "Tests.h"
#include "ResultSaveState.h"
#include "Tree.h"
#include "Error.h"
#include "Result.h"
#include "MySmartPointer.h"
#include "TestObject.h"
#include "Counters.h"

using namespace std;

Tests::Tests(const string& testTreeFormula, const string& testErrorMessage, const int& intToTest)
    : treeFormula(testTreeFormula), errorMessage(testErrorMessage), testInt(intToTest) {}

void Tests::run() {
    //testSaveTree();
    //testSaveInt();
    //testSaveError();
    testPointers();
}

void Tests::testPointers() {
    Counters counters;
    cout << TEST1 << endl;
    {
        MySmartPointer<int> ptrInt(new int(SMART_INT));
        cout << VALUE_SMART_INT << *ptrInt << endl;

        MySmartPointer<TestObject> ptrObj(new TestObject(ptrOBJ_INT1));
        cout << VALUE_SMART_OBJ << ptrObj->getValue() << endl;
        ptrObj->setValue(ptrOBJ_INT2);
        cout << VALUE_SMART_OBJ_SET << ptrObj->getValue() << endl;
    }

    cout << TEST2 << endl;
    {
        MySmartPointer<TestObject> ptrA(new TestObject(ptrOBJ_INT3));
        MySmartPointer<TestObject> ptrB(new TestObject(ptrOBJ_INT4));
        cout << VALUE_SMART_OBJ << ptrA->getValue() << endl;
    }

    cout << TEST3 << endl;
    {
        static TestObject staticObj(staticOBJ_INT);
        MySmartPointer<TestObject> ptrStatic(&staticObj, false);
        cout << VALUE_SMART_STATIC_OBJ << ptrStatic->getValue() << endl;
    }

    cout << TEST4 << endl;
    {
        Tree tree1(&counters);
        tree1.enter(TEST_TREE_FORMULA_1);

        Tree tree2(&counters);
        tree2.enter(TEST_TREE_FORMULA_2);

        cout << TEST_TREES << endl;
        tree1.print();
        tree2.print();

        tree1 = move(tree2);

        cout << TREE_AFTER_MOVE << endl;
        tree1.print();

        cout << MOVED_TREE << endl;
        tree2.print();
    }

    cout << TEST5 << endl;
    {
        Tree tree3(&counters);
        tree3.enter(TEST_TREE_FORMULA_3);

        Tree tree4(&counters);
        tree4.enter(TEST_TREE_FORMULA_4);

        cout << TEST_TREES << endl;
        tree3.print();
        tree4.print();

        Tree tree3sum4 = tree3 + tree4;
        cout << SUMMED_TREE << endl;
        tree3sum4.print();

        Tree tree5(&counters);
        tree5.enter(TEST_TREE_FORMULA_5);

        cout << TEST_TREES << endl;
        tree4.print();
        tree5.print();

        tree5 = tree4;
        cout << ASSIGNED_TREE << endl;
        tree5.print();

        Tree tree6(move(tree5));
        cout << TREE_AFTER_MOVE_CONSTRUCTOR << endl;
        tree6.print();

        cout << MOVED_TREE_CONSTRUCTOR << endl;
        tree5.print();

        cout << OVERALL_TEST_COUNTERS << endl;
        counters.copyAlert();
        counters.moveAlert();

        cout << TEST_COUNTERS_LOOP_PROCEDURE << endl;

        counters = Counters();
        {
            Tree loopTree1(&counters);
            loopTree1.enter(TEST_TREE_FORMULA_1);

            Tree loopTree2(&counters);
            loopTree2.enter(TEST_TREE_FORMULA_2);

            for (int i = 0; i < LOOP_TEST; i++) {
                Tree temp = loopTree1 + loopTree2;
                loopTree2 = temp;
            }
        }
        cout << LOOP_TEST_COUNTERS_NO_MS << endl;
        counters.copyAlert();
        counters.moveAlert();

        counters = Counters();
        {
            Tree loopTree1(&counters);
            loopTree1.enter(TEST_TREE_FORMULA_1);

            Tree loopTree2(&counters);
            loopTree2.enter(TEST_TREE_FORMULA_2);

            for (int i = 0; i < LOOP_TEST; i++) {
                Tree temp = loopTree1 + loopTree2;
                loopTree2 = move(temp);
            }
        }
        cout << LOOP_TEST_COUNTERS_MS << endl;
        counters.copyAlert();
        counters.moveAlert();


    }
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