#include "controller.h"

Controller::Controller()
{
   logic = new BaseLogic();
}

vector<string> Controller::getValuesByKey(string key, string subkey)
{
    return logic->getValuesByKey(key, subkey);
}

vector<string> Controller::getSubkeysByKey(string key, string subkey)
{
    return logic->getSubkeysByKey(key, subkey);
}

bool Controller::setNewValueData(string key, string subkey, string valueName, string valueType, string valueData)
{
    return logic->setNewValueData(key, subkey, valueName, valueType, valueData);
}

bool Controller::deleteValue(string key, string subkey, string valueName)
{
    return logic->deleteValue(key, subkey, valueName);
}

bool Controller::deleteKey(string key, string subkey)
{
    return logic->deleteKey(key, subkey);
}

bool Controller::addNewValue(string key, string subkey, string valueName, string valueType)
{
    return logic->addNewValue(key, subkey, valueName, valueType);
}

bool Controller::addNewKey(string key, string subkey, string newKeyName)
{
    return logic->addNewKey(key, subkey, newKeyName);
}
