#ifndef BASELOGIC_H
#define BASELOGIC_H
#include <Windows.h>
#include <string>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_LENGTH 16383

using namespace std;

class BaseLogic
{
public:
    BaseLogic();
    string* getValueByKey(string key, string subkey);
private:
    HKEY convertBaseKey(string key);
    string convertValueType(DWORD type);


};

#endif // BASELOGIC_H
