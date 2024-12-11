#ifndef TREEUI_H
#define TREEUI_H

#include "Tree.h"
#include <string>

using namespace std;

class ResultSaveState;

class TreeUI {
public:
    TreeUI();
    void run();

private:
    Tree tree;

    void processCommand(const string& command, ResultSaveState& saver);

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
    string ERROR_UNKNOWN_CMD = "Error: Unknown command: ";
    string ERROR_NO_FORMULA = "No formula provided.";
    string ERROR_NO_VALUES = "Error: No values provided.";
    string RESULT_PREFIX = "Result: ";
    string CMD_ENTER = "enter";
    string CMD_VARS = "vars";
    string CMD_PRINT = "print";
    string CMD_COMP = "comp";
    string CMD_JOIN = "join";
    string ERROR_RESULT = "Error: ";
    string INFO_TREE_SUCCESS = "Tree has grown succesfully";
    string INPUT_EXIT = "exit";
    string SUCC_JOIN = "Successfully joined two trees.";
    string AVAILABLE_VARS = "Variables:";

    string SAVE_PATH = "D:/syf/output.txt";
};

#endif