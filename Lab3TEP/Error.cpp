#include "Error.h"
using namespace std;

Error::Error(const string& errMessage) : error_message(errMessage) {}

const string& Error::getError() const {
    return error_message;
}