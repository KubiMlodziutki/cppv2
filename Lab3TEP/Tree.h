#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Error.h"
#include "Result.h"
#include <string>
#include <vector>

using namespace std;

class Tree {
public:
    Tree();
    ~Tree();

    Result<void, Error> enter(const string& formula);

    Result<vector<string>, Error> vars() const;

    Result<void, Error> print() const;

    Result<double, Error> comp(const vector<double>& values) const;

    Result<void, Error> join(const string& formula);

    Tree& operator=(const Tree& other);
    Tree operator+(const Tree& other) const;

    template <typename T, typename E>
    static Result<T, E> growTree(const string& formula);

private:
    Node* root;
    int selectedLeafIndex;

    Node* copyNode(const Node* node) const;
    Result<Node*, Error> parseTokens(const vector<string>& tokens, int& index);
    void collectTokens(Node* node, vector<string>& tokens) const;
    Result<void, Error> printTree(Node* node) const;
    void collectVars(Node* node, vector<string>& vars) const;
    void findLeavesWithParents(Node* node, Node* parent, vector<pair<Node*, Node*>>& leaves) const;
    double evaluate(Node* node, const vector<string>& vars, const vector<double>& values) const;
    int getChildrenNumber(const string& token) const;
    bool isNumber(const string& value) const;

    string INFO_CHOOSE_LEAF = "Choose a leaf (1-";
    string INFO_CHOOSE_LEAF_END = "): ";
    string INFO_AVAILABLE_LEAVES = "Available leaves to join:";
    string ERROR_NO_LEAVES = "No leaves available to join.";
    string ERROR_INFALID_JOIN = "Invalid formula for joining.";
    string ERROR_WRONG_VAR_COUNT = "Wrong variable count.";
    string ERROR_NO_FORMULA = "No formula entered.";
    string ERROR_INV_CHOICE = "Invalid choice.";
    string INFO_VARIABLES = "Variables: ";
    string INFO_PROCESSED_FORMULA = "Processed formula:";
    string WARN_TOO_MANY_TOKENS = "Warning: Extra tokens detected. Ignoring tokens from position ";
    string WARN_MISSING_OPERATOR_1 = "Warning: Operator '";
    string WARN_MISSING_OPERATOR_2 = "' missing operand. Adding '1'.";
    string MISSING_OPERATOR_NEW_OPERAND = "1";
    string INFO_SUCC_JOIN = "Successfully joined formula to the tree.";
    string ERROR_EMPTY_FORMULA = "Error: Empty formula.";
    string OPERATION_ADD = "+";
    string OPERATION_SUBSTRACT = "-";
    string OPERATION_MULTIPLICATION = "*";
    string OPERATION_DIVISION = "/";
    string OPERATION_SIN = "sin";
    string OPERATION_COS = "cos";
};

template <typename T, typename E>
Result<T, E> Tree::growTree(const string& formula) {
    if (formula.empty()) {
        return Result<T, E>::fail(new Error("Empty formula provided."));
    }

    Tree* newTree = new Tree();
    Result<void, Error> resultEnter = newTree->enter(formula);
    if (!resultEnter.isSuccess()) {
        delete newTree;
        vector<Error*>& errors = resultEnter.getErrors();
        return Result<T, E>::fail(errors);
    }

    return Result<T, E>::ok(newTree);
}

#endif