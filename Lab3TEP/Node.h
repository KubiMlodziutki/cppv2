#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string value;
    vector<Node*> children;

    Node(const string& value);
    ~Node();
};

#endif