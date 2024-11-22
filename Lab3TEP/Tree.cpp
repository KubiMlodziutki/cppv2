#include "Tree.h"
#include "Node.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

Tree::Tree() : root(nullptr), selectedLeafIndex(0) {}
Tree::~Tree() {
    delete root;
}

Node* Tree::copyNode(const Node* node) const {
    if (!node) return nullptr;
    Node* newNode = new Node(node->value);
    for (int i = 0; i < node->children.size(); i++) {
        newNode->children.push_back(copyNode(node->children[i]));
    }
    return newNode;
}

int Tree::getChildrenNumber(const string& operation) const {
    if (operation == "+" || operation == "-" || operation == "*" || operation == "/")
        return 2;
    else if (operation == "sin" || operation == "cos")
        return 1;
    else
        return 0;
}

bool Tree::isNumber(const string& value) const {
    if (value.empty()) return false;
    return all_of(value.begin(), value.end(), isdigit);
}

Node* Tree::parseTokens(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) {
        return nullptr;
    }

    string token = tokens[index++];
    Node* node = new Node(token);
    int childNum = getChildrenNumber(token);

    for (int i = 0; i < childNum; i++) {
        if (index >= tokens.size()) {
            cout << WARN_MISSING_OPERATOR_1 << token << WARN_MISSING_OPERATOR_2 << endl;
            node->children.push_back(new Node("1"));
        }
        else {
            node->children.push_back(parseTokens(tokens, index));
        }
    }

    return node;
}

void Tree::collectTokens(Node* node, vector<string>& tokens) const {
    if (!node) return;
    tokens.push_back(node->value);
    for (int i = 0; i < node->children.size(); i++) {
        collectTokens(node->children[i], tokens);
    }
}

bool Tree::enter(const string& formula) {
    if (root) {
        delete root;
        root = nullptr;
    }

    istringstream stream(formula);
    vector<string> tokens;
    string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        cout << ERROR_EMPTY_FORMULA << endl;
        return false;
    }

    int index = 0;
    root = parseTokens(tokens, index);

    if (index < tokens.size()) {
        cout << WARN_TOO_MANY_TOKENS << index + 1 << " onwards." << endl;
    }

    vector<string> correctedTokens;
    collectTokens(root, correctedTokens);

    cout << INFO_PROCESSED_FORMULA;
    for (int i = 0; i < correctedTokens.size(); i++) {
        cout << " " << correctedTokens[i];
    }
    cout << endl;

    return true;
}

void Tree::vars() const {
    if (!root) {
        cout << ERROR_NO_FORMULA << endl;
        return;
    }

    vector<string> vars_list;
    collectVars(root, vars_list);

    cout << INFO_VARIABLES;
    for (int i = 0; i < vars_list.size(); i++) {
        cout << " " << vars_list[i];
    }
    cout << endl;
}

void Tree::collectVars(Node* node, vector<string>& vars) const {
    if (!node) return;

    if (getChildrenNumber(node->value) == 0 && !isNumber(node->value)) {
        if (find(vars.begin(), vars.end(), node->value) == vars.end()) {
            vars.push_back(node->value);
        }
    }

    for (int i = 0; i < node->children.size(); i++) {
        collectVars(node->children[i], vars);
    }
}

void Tree::print() const {
    if (!root) {
        cout << ERROR_NO_FORMULA << endl;
        return;
    }
    printTree(root);
    cout << endl;
}

void Tree::printTree(Node* node) const {
    if (!node) return;

    cout << node->value << " ";
    for (int i = 0; i < node->children.size(); i++) {
        printTree(node->children[i]);
    }
}

double Tree::comp(const vector<double>& values) const {
    if (!root) {
        cout << ERROR_NO_FORMULA << endl;
        return 0;
    }
    vector<string> vars_list;
    collectVars(root, vars_list);
    if (values.size() != vars_list.size()) {
        cout << ERROR_WRONG_VAR_COUNT << endl;
        return 0;
    }
    return evaluate(root, vars_list, values);
}

double Tree::evaluate(Node* node, const vector<string>& vars, const vector<double>& values) const {
    if (!node) return 0;

    if (node->value == "+") {
        return evaluate(node->children[0], vars, values) + evaluate(node->children[1], vars, values);
    }
    else if (node->value == "-") {
        return evaluate(node->children[0], vars, values) - evaluate(node->children[1], vars, values);
    }
    else if (node->value == "*") {
        return evaluate(node->children[0], vars, values) * evaluate(node->children[1], vars, values);
    }
    else if (node->value == "/") {
        return evaluate(node->children[0], vars, values) / evaluate(node->children[1], vars, values);
    }
    else if (node->value == "sin") {
        return sin(evaluate(node->children[0], vars, values));
    }
    else if (node->value == "cos") {
        return cos(evaluate(node->children[0], vars, values));
    }
    else {
        for (int i = 0; i < vars.size(); i++) {
            if (node->value == vars[i]) {
                return values[i];
            }
        }
        return atof(node->value.c_str());
    }
}

void Tree::join(const string& formula) {
    Tree newTree;
    if (!newTree.enter(formula)) {
        cout << ERROR_INFALID_JOIN << endl;
        return;
    }

    vector<pair<Node*, Node*>> leaves;
    findLeavesWithParents(root, nullptr, leaves);

    if (leaves.empty()) {
        cout << ERROR_NO_LEAVES << endl;
        return;
    }

    cout << INFO_AVAILABLE_LEAVES << endl;
    for (int i = 0; i < leaves.size(); i++) {
        cout << i + 1 << ": " << leaves[i].first->value << endl;
    }

    int choice;
    cout << INFO_CHOOSE_LEAF << leaves.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > leaves.size()) {
        cout << ERROR_INV_CHOICE << endl;
        return;
    }

    selectedLeafIndex = choice - 1;

    *this = *this + newTree;
    cout << INFO_SUCC_JOIN << endl;
}

Tree& Tree::operator=(const Tree& other) {
    if (this != &other) {
        delete root;
        root = copyNode(other.root);
    }
    return *this;
}

void Tree::findLeavesWithParents(Node* node, Node* parent, vector<pair<Node*, Node*>>& leaves) const {
    if (!node) return;
    if (node->children.empty()) {
        leaves.push_back(make_pair(node, parent));
    }
    else {
        for (int i = 0; i < node->children.size(); i++) {
            findLeavesWithParents(node->children[i], node, leaves);
        }
    }
}

Tree Tree::operator+(const Tree& other) const {
    Tree result;
    if (!root) {
        result.root = copyNode(other.root);
    }
    else {
        result.root = copyNode(root);
        vector<pair<Node*, Node*>> leaves;
        findLeavesWithParents(result.root, nullptr, leaves);

        if (!leaves.empty()) {
            int index = selectedLeafIndex;
            if (index >= leaves.size()) {
                index = 0;
            }
            Node* leaf = leaves[index].first;
            Node* parent = leaves[index].second;

            if (parent == nullptr) {
                delete leaf;
                result.root = copyNode(other.root);
            }
            else {
                for (int i = 0; i < parent->children.size(); i++) {
                    if (parent->children[i] == leaf) {
                        delete parent->children[i];
                        parent->children[i] = copyNode(other.root);
                        break;
                    }
                }
            }
        }
    }
    return result;
}
