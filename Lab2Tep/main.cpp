#include "CNumber.h"
#include <iostream>

using namespace std;

int main() {
    CNumber a("1234654645635");
    CNumber b("54321");
    CNumber c("-12345");
    CNumber d("-54321");

    cout << "a + b: " << (a + b).toStr() << endl;
    cout << "a + c: " << (a + c).toStr() << endl;
    cout << "c + a: " << (c + a).toStr() << endl;
    cout << "a + d: " << (a + d).toStr() << endl;
    cout << "c + d: " << (c + d).toStr() << endl;

    cout << "a - b: " << (a - b).toStr() << endl;
    cout << "b - a: " << (b - a).toStr() << endl;
    cout << "a - c: " << (a - c).toStr() << endl;
    cout << "c - a: " << (c - a).toStr() << endl;
    cout << "d - c: " << (d - c).toStr() << endl;
    cout << "c - d: " << (c - d).toStr() << endl;
    cout << "c - c: " << (c - c).toStr() << endl;
    cout << "a - a: " << (a - a).toStr() << endl;

    cout << "a * b: " << (a * b).toStr() << endl;
    cout << "a * c: " << (a * c).toStr() << endl;
    cout << "c * a: " << (c * a).toStr() << endl;
    cout << "a * d: " << (a * d).toStr() << endl;
    cout << "c * d: " << (c * d).toStr() << endl;

    cout << "a / b: " << (a / b).toStr() << endl;
    cout << "a / c: " << (a / c).toStr() << endl;
    cout << "c / a: " << (c / a).toStr() << endl;
    cout << "a / d: " << (a / d).toStr() << endl;
    cout << "d / c: " << (d / c).toStr() << endl;

    return 0;
}