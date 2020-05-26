#ifndef BASELOGIC_H
#define BASELOGIC_H
#include <Windows.h>
#include <winreg.h>
#include <string>
#include <vector>
#include <QDebug>
#include <shlwapi.h>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_LENGTH 16383

using namespace std;

class BaseLogic
{
public:
    BaseLogic();
    vector<string> getValuesByKey(string key, string subkey);
    vector<string> getSubkeysByKey(string key, string subkey);
    bool setNewValueData(string key, string subkey, string valueName, string valueType, string valueData);
    bool deleteValue(string key, string subkey, string valueName);
    bool deleteKey(string key, string subkey);
    bool addNewValue(string key, string subkey, string valueName, string valueType);
    bool addNewKey(string key, string subkey, string newKeyName);
private:
    HKEY convertBaseKey(string key);
    string convertValueTypeToString(DWORD type);
    DWORD convertValueTypeToDword(string type);


};

#endif // BASELOGIC_H
