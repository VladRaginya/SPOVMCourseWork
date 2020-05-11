#include "baselogic.h"

BaseLogic::BaseLogic()
{
}

string* BaseLogic::getValueByKey(string key, string subkey)
{
    DWORD dataType;
    DWORD dataSize;
    BYTE data[512];
    HKEY selectedKey;
    string value[3];
    HKEY baseKey = convertBaseKey(key);
    RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey);
    RegQueryValueExA(selectedKey, "", NULL, &dataType, data, &dataSize);

}

HKEY BaseLogic::convertBaseKey(string key)
{
    switch(key)
    {
        case "HKEY_CLASSES_ROOT": return HKEY_CLASSES_ROOT;
        case "HKEY_CURRENT_USER": return HKEY_CURRENT_USER;
        case "HKEY_LOCAL_MACHINE": return HKEY_LOCAL_MACHINE;
        case "HKEY_USERS": return HKEY_USERS;
        case "HKEY_CURRENT_CONFIG": return HKEY_CURRENT_CONFIG;
    }
}

string BaseLogic::convertValueType(DWORD type)
{
    switch(type)
    {
        case REG_SZ: return "REG_SZ";
        case REG_DWORD: return "REG_DWORD";
        case REG_BINARY: return "REG_BINARY";
        case REG_QWORD: return "REG_QWORD";
    }
}
