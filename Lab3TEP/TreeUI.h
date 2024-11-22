#ifndef TREEUI_H
#define TREEUI_H

#include "Tree.h"
#include <string>

using namespace std;

class TreeUI {
public:
    TreeUI();
    void run();


private:
    Tree tree;

    void processCommand(const string& command);

    string INFO_WELCOME = "Hello, this is Tree calculation app";
    string INFO_COMMANDS = "Commands:";
    string INFO_ENTER = "  enter <formula> - Create or update a tree using prefixed formula";
    string INFO_VARS = "  vars - List all variables in the current tree";
    string INFO_PRINT = "  print - Print prefixed current tree";
    string INFO_COMP = "  comp <var1>, <var2>, ..., <varN> - Compute the tree defining variables";
    string INFO_JOIN = "  join <formula> - Join a new formula to current tree leaf";
    string INFO_EXIT = "  exit - Exit the app";
    string PROMPT = "> ";
    string INFO_EXITING = "Exiting...";
    string ERROR_UNKNOWN_CMD = "Error: Unknown command '";
    string ERROR_NO_FORMULA = "Error: No formula provided.";
    string ERROR_NO_VALUES = "Error: No values provided.";
    string RESULT_PREFIX = "Result: ";

};
#endif