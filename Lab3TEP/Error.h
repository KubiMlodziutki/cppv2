#ifndef ERROR_H
#define ERROR_H

#include <string>
using namespace std;

class Error {
public:
    Error(const string& errMessage);
    const string& getError() const;

private:
    string error_message;
};

#endif