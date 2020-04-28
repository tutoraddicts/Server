#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace ConvertDataType
{
    char IntToChar(int intVar)
    {
        std::string tempString = std::to_string(intVar);
        const char *Value = tempString.c_str();
        return *Value;
    }

    int StringToInt(std::string &stringVar)
    {
        std::stringstream s_stream(stringVar);
        int intVar = 0;
        s_stream >> intVar;
        return intVar;
    }

    const char* StringToChar(std::string &stringVar)
    {
        return stringVar.c_str();
    }
}
