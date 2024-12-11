#include "ResultSaveState.h"

ResultSaveState::ResultSaveState(const string& fileName) : fileName(fileName) {}

ofstream ResultSaveState::openFileAtEnd() {
    ofstream file(fileName.c_str(), ios::out | ios::binary);
    if (file.good()) {
        file.seekp(0, ios::end);
    }
    return file;
}

void ResultSaveState::saveErrors(const vector<Error*>& errors) {
    ofstream file = openFileAtEnd();
    if (!file) return;

    for (int i = 0; i < errors.size(); i++) {
        file << ERROR_RESULT << errors[i]->getError() << "\n";
    }
    file.close();
}

void ResultSaveState::saveTree(const Tree* tree) {
    if (!tree) return;
    ofstream file = openFileAtEnd();
    if (!file) return;

    streambuf* originalCoutBuffer = cout.rdbuf();
    cout.rdbuf(file.rdbuf());

    tree->print();

    cout.rdbuf(originalCoutBuffer);
    file.close();
}

template <typename T>
void ResultSaveState::saveToFile(Result<T, Error>& result) {
    if (!result.isSuccess()) {
        saveErrors(result.getErrors());
    }
}

template <>
void ResultSaveState::saveToFile<Tree*>(Result<Tree*, Error>& result) {
    if (result.isSuccess()) {
        saveTree(result.getValue());
    }
    else {
        saveErrors(result.getErrors());
    }
}

template void ResultSaveState::saveToFile<void>(Result<void, Error>& result);
template void ResultSaveState::saveToFile<double>(Result<double, Error>& result);
template void ResultSaveState::saveToFile<int>(Result<int, Error>& result);
template void ResultSaveState::saveToFile<vector<string>>(Result<vector<string>, Error>& result);
