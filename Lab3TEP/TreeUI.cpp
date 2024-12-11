#include "TreeUI.h"
#include "ResultSaveState.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

TreeUI::TreeUI() {}

void TreeUI::run() {
    cout << INFO_WELCOME << endl;
    cout << INFO_COMMANDS << endl;
    cout << INFO_ENTER << endl;
    cout << INFO_VARS << endl;
    cout << INFO_PRINT << endl;
    cout << INFO_COMP << endl;
    cout << INFO_JOIN << endl;
    cout << INFO_EXIT << endl;

    bool running = true;
    ResultSaveState saver(SAVE_PATH);

    while (running) {
        cout << PROMPT;
        string input;
        if (!getline(cin, input)) {
            break;
        }

        if (input == INPUT_EXIT) {
            cout << INFO_EXITING << endl;
            running = false;
        }
        else {
            processCommand(input, saver);
        }
    }
}

void TreeUI::processCommand(const string& command, ResultSaveState& saver) {
    istringstream stream(command);
    string cmd;
    stream >> cmd;

    if (cmd == CMD_ENTER) {
        string formula;
        {
            string prompt;
            getline(stream, prompt);
            if (!prompt.empty() && prompt[0] == ' ') {
                prompt.erase(0, 1);
            }
            formula = prompt;
        }

        if (formula.empty()) {
            cout << ERROR_RESULT + ERROR_NO_FORMULA << endl;
            return;
        }

        Result<Tree*, Error> result = Tree::growTree<Tree*, Error>(formula);

        saver.saveToFile(result);

        if (result.isSuccess()) {
            Tree* newTree = result.getValue();
            tree = *newTree;
            delete newTree;
            cout << INFO_TREE_SUCCESS << endl;
        }
        else {
            vector<Error*>& errors = result.getErrors();
            for (int i = 0; i < errors.size(); i++) {
                cout << ERROR_RESULT << errors[i]->getError() << endl;
            }
        }

    }
    else if (cmd == CMD_VARS) {
        Result<vector<string>, Error> resultVars = tree.vars();

        saver.saveToFile(resultVars);

        if (resultVars.isSuccess()) {
            vector<string> vars = resultVars.getValue();
            cout << AVAILABLE_VARS;
            for (int i = 0; i < vars.size(); i++) {
                cout << " " << vars[i];
            }
            cout << endl;
        }
        else {
            vector<Error*>& errors = resultVars.getErrors();
            for (int i = 0; i < errors.size(); i++) {
                cout << ERROR_RESULT << errors[i]->getError() << endl;
            }
        }

    }
    else if (cmd == CMD_PRINT) {
        Result<void, Error> resultPrint = tree.print();

        saver.saveToFile(resultPrint);

        if (!resultPrint.isSuccess()) {
            vector<Error*>& errors = resultPrint.getErrors();
            for (int i = 0; i < errors.size(); i++) {
                cout << ERROR_RESULT << errors[i]->getError() << endl;
            }
        }
    }
    else if (cmd == CMD_COMP) {
        vector<double> values;
        double val;
        while (stream >> val) {
            values.push_back(val);
        }

        if (values.empty()) {
            cout << ERROR_NO_VALUES << endl;
        }
        else {
            Result<double, Error> resultComp = tree.comp(values);

            saver.saveToFile(resultComp);

            if (resultComp.isSuccess()) {
                cout << RESULT_PREFIX << resultComp.getValue() << endl;
            }
            else {
                vector<Error*>& errors = resultComp.getErrors();
                for (int i = 0; i < errors.size(); i++) {
                    cout << ERROR_RESULT << errors[i]->getError() << endl;
                }
            }
        }

    }
    else if (cmd == CMD_JOIN) {
        string formula;
        {
            string toJoin;
            getline(stream, toJoin);
            if (!toJoin.empty() && toJoin[0] == ' ') {
                toJoin.erase(0, 1);
            }
            formula = toJoin;
        }

        if (formula.empty()) {
            cout << ERROR_RESULT + ERROR_NO_FORMULA << endl;
            return;
        }

        Result<void, Error> joined = tree.join(formula);

        saver.saveToFile(joined);

        if (!joined.isSuccess()) {
            vector<Error*>& errors = joined.getErrors();
            for (int i = 0; i < errors.size(); i++) {
                cout << ERROR_RESULT << errors[i]->getError() << endl;
            }
        }
        else {
            cout << SUCC_JOIN << endl;
        }
    }
    else {
        cout << ERROR_UNKNOWN_CMD << cmd << endl;
    }
}
