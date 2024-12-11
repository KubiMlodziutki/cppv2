#include "TreeUI.h"
#include "Tests.h"

int main() {
    Tests test1("+ a b", "Invalid input", 13);
    test1.run();

    TreeUI ui;
    ui.run();

    return 0;
}