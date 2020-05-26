#include "baselogic.h"

BaseLogic::BaseLogic()
{
}

vector<string> BaseLogic::getValuesByKey(string key, string subkey)
{
    DWORD dataType;
    DWORD newValueIndex = 0;
    char* newValueName;
    DWORD valuesNumber;
    DWORD valueNameMaxLength;
    HKEY selectedKey;
    BYTE data[MAX_VALUE_LENGTH];
    DWORD maxLen;
    string dataString, dataBuf;
    vector<string> allValues;
    HKEY baseKey = convertBaseKey(key);
    DWORD isSuccessful;
    if(isSuccessful = RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
    }
    if(RegQueryInfoKeyA(selectedKey, NULL, NULL, NULL, NULL, NULL, NULL, &valuesNumber, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
    {
        qDebug() << "Error 2";
    }
    //if(valuesNumber == 0) return NULL;
    for(int i = 0; i < valuesNumber; i++)
    {
        memset(data, 0, sizeof data);
        valueNameMaxLength = MAX_KEY_LENGTH;
        maxLen = MAX_VALUE_LENGTH;
        isSuccessful = RegEnumValueA(selectedKey, newValueIndex, newValueName, &valueNameMaxLength, NULL, &dataType, data, &maxLen);
        if(isSuccessful != ERROR_SUCCESS)
        {
             qDebug() << isSuccessful;
        }
        newValueIndex++;
        allValues.push_back(newValueName);
        allValues.push_back(convertValueTypeToString(dataType));

        if(dataType == REG_DWORD)
        {
            DWORD dword_data;
            char buf[15];
            memcpy(&dword_data, data, sizeof(DWORD));
            dataString = itoa(dword_data, buf, 10);
        }
        if(dataType == REG_QWORD)
        {
            long long qword_data;
            char buf[30];
            memcpy(&qword_data, data, sizeof(long long));
            dataString = ltoa(qword_data, buf, 10);
        }
        if(dataType == REG_SZ)
        {

           dataString = (char*)data;
        }
        if(dataType == REG_BINARY)
        {
            char buf[maxLen];
            memcpy(buf, &data, sizeof(char)*maxLen);
            dataString = buf;
        }

        allValues.push_back(dataString);
    }
    RegCloseKey(selectedKey);

    return allValues;

}

vector<string> BaseLogic::getSubkeysByKey(string key, string subkey)
{
    DWORD newSubkeyIndex = 0;
    char newSubkeyName[MAX_KEY_LENGTH];
    DWORD subkeyNameMaxLength;
    DWORD subkeysNumber;
    HKEY selectedKey;
    string newSubkeyNameString;
    vector<string> allSubkeys;
    HKEY baseKey = convertBaseKey(key);
    RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey);
    RegQueryInfoKeyA(selectedKey, NULL, NULL, NULL, &subkeysNumber, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    //if(subkeysNumber == 0) return NULL;
    for(int i = 0; i < subkeysNumber; i++)
    {
        subkeyNameMaxLength = MAX_KEY_LENGTH;
        RegEnumKeyExA(selectedKey, newSubkeyIndex, newSubkeyName, &subkeyNameMaxLength, NULL, NULL, NULL, NULL);
        newSubkeyIndex++;
        newSubkeyNameString = newSubkeyName;
        allSubkeys.push_back(newSubkeyNameString);
    }
    RegCloseKey(selectedKey);
    return allSubkeys;
}

bool BaseLogic::setNewValueData(string key, string subkey, string valueName, string valueType, string valueData)
{
    HKEY selectedKey;
    DWORD isSuccessful;
    int dataSize;
    DWORD type = convertValueTypeToDword(valueType);
    BYTE* data;
    if(type == REG_DWORD)
    {
        DWORD dword_data = atol(valueData.c_str());
        BYTE byte_array[sizeof(DWORD)];
        memcpy(byte_array, &dword_data, sizeof(DWORD));
        data = byte_array;
        dataSize = 4;
    }
    if(type == REG_QWORD)
    {
        long long qword_data = atoll(valueData.c_str());
        BYTE byte_array[sizeof(long long)];
        memcpy(byte_array, &qword_data, sizeof(long long));
        data = byte_array;
        dataSize = 8;
    }
    if(type == REG_SZ )
    {
        data = (BYTE*)valueData.c_str();
        dataSize = valueData.size()+1;
    }
    if(type == REG_BINARY)
    {

        data = (BYTE*)valueData.c_str();
        dataSize = valueData.size();
    }

    HKEY baseKey = convertBaseKey(key);
    if(isSuccessful = RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
    }
    isSuccessful = RegSetValueExA(selectedKey, valueName.c_str(),NULL, type, data, dataSize);
    RegCloseKey(selectedKey);
    if(isSuccessful != ERROR_SUCCESS) return false;
    return true;
}

bool BaseLogic::deleteValue(string key, string subkey, string valueName)
{
    HKEY selectedKey;
    HKEY baseKey = convertBaseKey(key);
    DWORD isSuccessful;
    if(isSuccessful = RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
    }
    if(isSuccessful = RegDeleteValueA(selectedKey, valueName.c_str()) != ERROR_SUCCESS)
    {
       return false;
    }
    return true;
}

bool BaseLogic::deleteKey(string key, string subkey)
{
    HKEY baseKey = convertBaseKey(key);
    DWORD isSuccessful;
    if(isSuccessful = RegDeleteKeyA(baseKey, subkey.c_str()) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
       return false;
    }
    return true;
}

bool BaseLogic::addNewValue(string key, string subkey, string valueName, string valueType)
{
    HKEY selectedKey;
    DWORD isSuccessful;
    int dataSize;
    HKEY baseKey = convertBaseKey(key);
    DWORD type = convertValueTypeToDword(valueType);
    if(isSuccessful = RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
    }
    BYTE* data;
    if(type == REG_DWORD)
    {
        BYTE byte_array[sizeof(DWORD)] = {0,0,0,0};
        data = byte_array;
        dataSize = 4;
    }
    if(type == REG_QWORD)
    {
        BYTE byte_array[sizeof(long long)] = {0,0,0,0,0,0,0,0};
        data = byte_array;
        dataSize = 8;
    }
    if(type == REG_SZ)
    {
        data = (BYTE*)"";
        dataSize = sizeof(data)+1;
    }
    if(type == REG_BINARY)
    {
        data = NULL;
        dataSize = NULL;
    }
    isSuccessful = RegSetValueExA(selectedKey, valueName.c_str(),NULL, type, data, dataSize);
    RegCloseKey(selectedKey);
    if(isSuccessful != ERROR_SUCCESS) return false;
    return true;
}

bool BaseLogic::addNewKey(string key, string subkey, string newKeyName)
{
    HKEY selectedKey, newKey;
    DWORD isSuccessful;
    HKEY baseKey = convertBaseKey(key);
    if(isSuccessful = RegOpenKeyExA(baseKey, subkey.c_str(),0, KEY_ALL_ACCESS, &selectedKey) != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
    }
    isSuccessful = RegCreateKeyExA(selectedKey, newKeyName.c_str(),NULL, NULL, NULL, NULL, NULL, &newKey, NULL);
    RegCloseKey(selectedKey);
    RegCloseKey(newKey);
    if(isSuccessful != ERROR_SUCCESS)
    {
        qDebug() << isSuccessful;
        return false;
    }
    return true;
}

HKEY BaseLogic::convertBaseKey(string key)
{

       if(key == "HKEY_CLASSES_ROOT") return HKEY_CLASSES_ROOT;
       if(key == "HKEY_CURRENT_USER") return HKEY_CURRENT_USER;
       if(key == "HKEY_LOCAL_MACHINE") return HKEY_LOCAL_MACHINE;
       if(key == "HKEY_USERS") return HKEY_USERS;
       if(key == "HKEY_CURRENT_CONFIG") return HKEY_CURRENT_CONFIG;
}

string BaseLogic::convertValueTypeToString(DWORD type)
{
      if(type == REG_SZ) return "REG_SZ";
      if(type == REG_DWORD) return "REG_DWORD";
      if(type == REG_BINARY) return "REG_BINARY";
      if(type == REG_QWORD) return "REG_QWORD";
}

DWORD BaseLogic::convertValueTypeToDword(string type)
{
    if(type == "REG_SZ") return REG_SZ;
    if(type == "REG_DWORD") return REG_DWORD;
    if(type == "REG_BINARY") return REG_BINARY;
    if(type == "REG_QWORD") return REG_QWORD;
}


