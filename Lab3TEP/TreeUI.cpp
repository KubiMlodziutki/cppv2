#include "TreeUI.h"
#include <iostream>
#include <sstream>

using namespace std;

TreeUI::TreeUI() {}

void TreeUI::run() {
    string input;
    cout << INFO_WELCOME << endl;
    cout << INFO_COMMANDS << endl;
    cout << INFO_ENTER << endl;
    cout << INFO_VARS << endl;
    cout << INFO_PRINT << endl;
    cout << INFO_COMP << endl;
    cout << INFO_JOIN << endl;
    cout << INFO_EXIT << endl;

    while (true) {
        cout << PROMPT;
        getline(cin, input);
        if (input == "exit") {
            cout << INFO_EXITING << endl;
            break;
        }
        processCommand(input);
    }
}

void TreeUI::processCommand(const string& command) {
    istringstream stream(command);
    string cmd;
    stream >> cmd;

    if (cmd == "enter") {
        string formula;
        getline(stream, formula);
        if (formula.empty()) {
            cout << ERROR_NO_FORMULA << endl;
        }
        else {
            tree.enter(formula);
        }
    }
    else if (cmd == "vars") {
        tree.vars();
    }
    else if (cmd == "print") {
        tree.print();
    }
    else if (cmd == "comp") {
        vector<double> values;
        double val;
        while (stream >> val) {
            values.push_back(val);
        }

        if (values.empty()) {
            cout << ERROR_NO_VALUES << endl;
        }
        else {
            double result = tree.comp(values);
            cout << RESULT_PREFIX << result << endl;
        }
    }
    else if (cmd == "join") {
        string formula;
        getline(stream, formula);
        if (formula.empty()) {
            cout << ERROR_NO_FORMULA << endl;
        }
        else {
            tree.join(formula);
        }
    }
    else {
        cout << ERROR_UNKNOWN_CMD << cmd << "'." << endl;
    }
}
