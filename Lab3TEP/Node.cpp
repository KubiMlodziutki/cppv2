#include "Node.h"

using namespace std;

Node::Node(const string& val) : value(val) {}

Node::~Node() {
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
}