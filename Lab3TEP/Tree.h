#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>
#include <vector>

using namespace std;

class Tree {
public:
    Tree();
    ~Tree();

    bool enter(const string& formula);
    void vars() const;
    void print() const;
    double comp(const vector<double>& values) const;
    void join(const string& formula);

    Tree& operator=(const Tree& other);
    Tree operator+(const Tree& other) const;

private:
    Node* root;
    int selectedLeafIndex;

    Node* copyNode(const Node* node) const;
    Node* parseTokens(const vector<string>& tokens, int& index);
    void collectTokens(Node* node, vector<string>& tokens) const;
    void printTree(Node* node) const;
    void collectVars(Node* node, vector<string>& vars) const;
    void findLeavesWithParents(Node* node, Node* parent, vector<pair<Node*, Node*>>& leaves) const;
    double evaluate(Node* node, const vector<string>& vars, const vector<double>& values) const;
    int getChildrenNumber(const string& token) const;
    bool isNumber(const string& value) const;

    string INFO_CHOOSE_LEAF = "Choose a leaf (1-";
    string INFO_AVAILABLE_LEAVES = "Available leaves to join:";
    string ERROR_NO_LEAVES = "Error: No leaves available to join.";
    string ERROR_INFALID_JOIN = "Error: Invalid formula for joining.";
    string ERROR_WRONG_VAR_COUNT = "Error: Wrong variable count.";
    string ERROR_NO_FORMULA = "Error: No formula entered.";
    string ERROR_INV_CHOICE = "Error: Invalid choice.";
    string INFO_VARIABLES = "Variables: ";
    string INFO_PROCESSED_FORMULA = "Processed formula:";
    string WARN_TOO_MANY_TOKENS = "Warning: Extra tokens detected. Ignoring tokens from position ";
    string WARN_MISSING_OPERATOR_1 = "Warning: Operator '";
    string WARN_MISSING_OPERATOR_2 = "' missing operand. Adding '1'.";
    string INFO_SUCC_JOIN = "Successfully joined formula to the tree.";
    string ERROR_EMPTY_FORMULA = "Error: Empty formula.";

};

#endif
