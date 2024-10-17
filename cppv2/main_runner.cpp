#include "utils.h"
#include "CTable.h"
#include "utils_and_main_consts.h"
#include <iostream>
using namespace std;

int main()
{
    // testing section 1

    v_alloc_table_fill_34(-5);
    v_alloc_table_fill_34(5);

    int** pi_table = nullptr;

    b_dealloc_table_2_dim(&pi_table, 3);

    b_alloc_table_2_dim(&pi_table, 5, -3);
    b_alloc_table_2_dim(&pi_table, 5, 3);

    pi_table[0][0] = 15;

    cout << pi_table[0][0] << endl;

    b_dealloc_table_2_dim(&pi_table, 5);

    // testing section 2

    CTable cTabNonParam;
    CTable cTabParamBAD("", -3);
    CTable cTabParam("my_table", 5);
    CTable cTabCopyConstructor(cTabParam);

    cTabParamBAD.bSetNewSize(-3);
    cTabParamBAD.vSetName("");

    cout << sTableName << cTabNonParam.sGetName() << " " + sTableSize << cTabNonParam.iGetSize() << endl;
    cout << sTableName << cTabParamBAD.sGetName() << " " + sTableSize << cTabParamBAD.iGetSize() << endl;
    cout << sTableName << cTabParam.sGetName() << " " + sTableSize << cTabParam.iGetSize() << endl;
    cout << sTableName << cTabCopyConstructor.sGetName() << " " + sTableSize << cTabCopyConstructor.iGetSize() << endl;

    cTabParamBAD.bSetNewSize(4);
    cTabParamBAD.vSetName("new_name");

    cout << sTableName << cTabParamBAD.sGetName() << " " + sTableSize << cTabParamBAD.iGetSize() << endl;

    CTable* cTabCloned = cTabParam.pcClone();

    cout << sTableName << cTabCloned->sGetName() << " " + sTableSize << cTabCloned->iGetSize() << endl;

    delete cTabCloned;

    return 0;
}