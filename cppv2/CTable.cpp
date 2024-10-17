#include "CTable.h"
#include <iostream>
using namespace std;

CTable::CTable()
{
    s_name = sDefaultName;
    i_TableLen = iDefaultLen;
    piTable = new int[i_TableLen];

    cout << sNonParamMessage << s_name << "'" << endl;
}

CTable::CTable(string sName, int iTableLen) : s_name(sName), i_TableLen(iTableLen)
{
    if (iTableLen <= 0)
    {
        cout << sErrorSizeProviding << endl;
        i_TableLen = iDefaultLen; 
    }

    if (sName.length() == 0)
    {
        cout << sErrorNameProviding << endl;
        s_name = sDefaultName;
    }
    
    piTable = new int[i_TableLen];

    cout << sParamMessage << s_name << "'" << endl;
}

CTable::CTable(const CTable& pcOther)
{
    s_name = pcOther.s_name + sCopyAddon;
    i_TableLen = pcOther.i_TableLen;
    piTable = new int[i_TableLen];

    for (int i = 0; i < i_TableLen; i++)
    {
        piTable[i] = pcOther.piTable[i];
    }

    cout << sCopyMessage << s_name << "'" << endl;
}

CTable::~CTable()
{
    delete[] piTable;

    cout << sDeleteMessage << s_name << "'" << endl;
}

CTable* CTable::pcClone()
{
    return new CTable(*this);
}

bool CTable::bSetNewSize(int iTableLen)
{
    if (iTableLen  <= 0)
    {
        cout << sErrorSizeSetting << endl;
        return false;
    }

    int temp_size = iTableLen;
    if (iTableLen > i_TableLen)
    {
        temp_size = i_TableLen;
    }

    int* piNewTable = new int[iTableLen];

    for (int i = 0; i < temp_size; i++)
    {
        piNewTable[i] = piTable[i];
    }

    delete[] piTable;

    i_TableLen = iTableLen;
    piTable =  piNewTable;

    return true;
}

void CTable::vSetName(string sName)
{
    if (sName.length() == 0)
    {
        cout << sErrorNameSetting << endl;
        return;
    }

    s_name = sName;
}

// this procedure will probably modify the size
void v_mod_tab(CTable* pcTab, int iNewSize)
{
    pcTab->bSetNewSize(iNewSize);
}

// this procedure will probably modify the copy
void v_mod_tab(CTable cTab, int iNewSize)
{
    cTab.bSetNewSize(iNewSize);
}

// test purposes method
string CTable::sGetName()
{
    return s_name;
}

// test purposes method
int CTable::iGetSize()
{
    return i_TableLen;
}