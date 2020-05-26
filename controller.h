#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <baselogic.h>
#include <string.h>

class Controller
{
public:
    Controller();
    vector<string> getValuesByKey(string key, string subkey);
    vector<string> getSubkeysByKey(string key, string subkey);
    bool setNewValueData(string key, string subkey,string valueName, string valueType, string valueData);
    bool deleteValue(string key, string subkey, string valueName);
    bool deleteKey(string key, string subkey);
    bool addNewValue(string key, string subkey, string valueName, string valueType);
    bool addNewKey(string key, string subkey, string newKey);
private:
    BaseLogic* logic;
};

#endif // CONTROLLER_H
