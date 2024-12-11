#include "Tree.h"
#include "Node.h"
#include "Error.h"
#include "Result.h"
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
    if (operation == OPERATION_ADD || operation == OPERATION_SUBSTRACT || operation == OPERATION_MULTIPLICATION || operation == OPERATION_DIVISION)
        return 2;
    else if (operation == OPERATION_SIN || operation == OPERATION_COS)
        return 1;
    else
        return 0;
}

bool Tree::isNumber(const string& value) const {
    if (value.empty()) return false;
    return all_of(value.begin(), value.end(), ::isdigit);
}

Result<Node*, Error> Tree::parseTokens(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) {
        return Result<Node*, Error>::ok(nullptr);
    }

    string token = tokens[index++];
    Node* node = new Node(token);
    int childNum = getChildrenNumber(token);

    vector<Error*> errors;

    for (int i = 0; i < childNum; i++) {
        if (index >= tokens.size()) {
            errors.push_back(new Error(WARN_MISSING_OPERATOR_1 + token + WARN_MISSING_OPERATOR_2));
            node->children.push_back(new Node(MISSING_OPERATOR_NEW_OPERAND));
        }
        else {
            Result<Node*, Error> childResult = parseTokens(tokens, index);
            if (!childResult.isSuccess()) {
                vector<Error*>& childErrors = childResult.getErrors();
                errors.insert(errors.end(), childErrors.begin(), childErrors.end());
                node->children.push_back(nullptr);
            }
            else {
                node->children.push_back(childResult.getValue());
            }
        }
    }

    if (!errors.empty()) {
        return Result<Node*, Error>::fail(errors);
    }

    return Result<Node*, Error>::ok(node);
}

void Tree::collectTokens(Node* node, vector<string>& tokens) const {
    if (!node) return;

    tokens.push_back(node->value);
    for (int i = 0; i < node->children.size(); i++) {
        collectTokens(node->children[i], tokens);
    }
}

Result<void, Error> Tree::enter(const string& formula) {
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
        return Result<void, Error>::fail(new Error(ERROR_EMPTY_FORMULA));
    }

    int index = 0;
    Result<Node*, Error> parseResult = parseTokens(tokens, index);

    if (!parseResult.isSuccess()) {
        delete root;
        root = nullptr;
        return Result<void, Error>::fail(parseResult.getErrors());
    }

    root = parseResult.getValue();

    vector<Error*> errors;
    if (index < tokens.size()) {
        errors.push_back(new Error(WARN_TOO_MANY_TOKENS + to_string(index + 1)));
    }

    vector<string> correctedTokens;
    collectTokens(root, correctedTokens);

    if (!errors.empty()) {
        return Result<void, Error>::fail(errors);
    }

    return Result<void, Error>::ok();
}

Result<vector<string>, Error> Tree::vars() const {
    if (!root) {
        return Result<vector<string>, Error>::fail(new Error(ERROR_NO_FORMULA));
    }

    vector<string> vars;
    collectVars(root, vars);

    return Result<vector<string>, Error>::ok(vars);
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

Result<void, Error> Tree::print() const {
    if (!root) {
        return Result<void, Error>::fail(new Error(ERROR_NO_FORMULA));
    }

    printTree(root);
    cout << endl;

    return Result<void, Error>::ok();
}

Result<void, Error> Tree::printTree(Node* node) const {
    if (!node) return Result<void, Error>::ok();

    cout << node->value << " ";
    for (int i = 0; i < node->children.size(); i++) {
        Result<void, Error> resultPrint = printTree(node->children[i]);
        if (!resultPrint.isSuccess()) {
            return resultPrint;
        }
    }

    return Result<void, Error>::ok();
}

Result<double, Error> Tree::comp(const vector<double>& values) const {
    if (!root) {
        return Result<double, Error>::fail(new Error(ERROR_NO_FORMULA));
    }

    vector<string> vars;
    collectVars(root, vars);
    if (values.size() != vars.size()) {
        return Result<double, Error>::fail(new Error(ERROR_WRONG_VAR_COUNT));
    }

    double computed = evaluate(root, vars, values);
    return Result<double, Error>::ok(computed);
}

double Tree::evaluate(Node* node, const vector<string>& vars, const vector<double>& values) const {
    if (!node) return 0;

    if (node->value == OPERATION_ADD) {
        return evaluate(node->children[0], vars, values) + evaluate(node->children[1], vars, values);
    }
    else if (node->value == OPERATION_SUBSTRACT) {
        return evaluate(node->children[0], vars, values) - evaluate(node->children[1], vars, values);
    }
    else if (node->value == OPERATION_MULTIPLICATION) {
        return evaluate(node->children[0], vars, values) * evaluate(node->children[1], vars, values);
    }
    else if (node->value == OPERATION_DIVISION) {
        return evaluate(node->children[0], vars, values) / evaluate(node->children[1], vars, values);
    }
    else if (node->value == OPERATION_SIN) {
        return sin(evaluate(node->children[0], vars, values));
    }
    else if (node->value == OPERATION_COS) {
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

Result<void, Error> Tree::join(const string& formula) {
    Tree newTree;
    Result<void, Error> resultJoin = newTree.enter(formula);

    if (!resultJoin.isSuccess()) {
        vector<Error*>& errors = resultJoin.getErrors();
        errors.push_back(new Error(ERROR_INFALID_JOIN));

        return Result<void, Error>::fail(errors);
    }

    vector<pair<Node*, Node*>> leaves;
    findLeavesWithParents(root, nullptr, leaves);

    if (leaves.empty()) {
        return Result<void, Error>::fail(new Error(ERROR_NO_LEAVES));
    }

    selectedLeafIndex = 0;

    *this = *this + newTree;

    return Result<void, Error>::ok();
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