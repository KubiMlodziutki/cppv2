#ifndef CTABLE_H
#define CTABLE_H

#include <string>
using namespace std;

class CTable
{
public:
    CTable();
    CTable(string sName, int iTableLen);
    CTable(const CTable& pcOther);
    ~CTable();

    void vSetName(string sName);
    bool bSetNewSize(int iTableLen);
    CTable* pcClone();

    // test purposes methods
    string sGetName();
    int iGetSize();

private:
    string s_name;
    int i_TableLen;
    int* piTable;

    const string sDefaultName = "def_name";
    const int iDefaultLen = 10;
    const string sCopyAddon = "_copy";
    const string sNonParamMessage = "nonparam: '";
    const string sParamMessage = "param: '";
    const string sCopyMessage = "copy: '";
    const string sDeleteMessage = "delete: '";
    const string sErrorSizeProviding = "Table length has to be greater than 0, setting to default value.";
    const string sErrorNameProviding = "Name not provided, setting to default value.";
    const string sErrorSizeSetting = "Tried to set size below 0, no changes have been made.";
    const string sErrorNameSetting = "Tried to set name to empty string, no changes have been made.";
};

void v_mod_tab(CTable* pcTab, int iNewSize);
void v_mod_tab(CTable cTab, int iNewSize);

#endif
