#include "utils.h"
#include "utils_and_main_consts.h"
#include <iostream>
using namespace std;

void v_alloc_table_fill_34(int iSize)
{
    if (iSize <= 0)
    {
        cout << sErrorSize << endl;
        return;
    }
    
    int* piTable = new int[iSize];

    for (int i = 0; i < iSize; i++)
    {
        piTable[i] = 34;
    }

    for (int i = 0; i < iSize; i++)
    {
        cout << piTable[i] << " ";
    }

    cout << endl;

    delete[] piTable;
}

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY)
{
    if (iSizeX <= 0 || iSizeY <= 0)
    {
        cout << sErrorSizes << endl;
        return false;
    }

    *piTable = new int*[iSizeX];

    for (int i = 0; i < iSizeX; i++)
    {
        (*piTable)[i] = new int[iSizeY];
    }

    return true;
}

// iSizeY param is not needed, because of cascade deleting
bool b_dealloc_table_2_dim(int*** piTable, int iSizeX)
{
    if (*piTable == nullptr)
    {
        cout << sTableNotAllocated << endl;
        return false;
    }

    else if (iSizeX <= 0)
    {
        cout << sErrorSize << endl;
        return false;
    }

    for (int i = 0; i < iSizeX; i++)
    {
        delete[] (*piTable)[i];
    }

    delete[] *piTable;
    *piTable = nullptr;

    return true;
}