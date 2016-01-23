/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/
#include "serializationconstants.h"

int floatToInt(float value)
{
    return *reinterpret_cast<int*>(&value);
}

float intToFloat(int value)
{
    return *reinterpret_cast<float*>(&value);
}

long doubleToLong(double value)
{
    return *reinterpret_cast<long*>(&value);
}

double longToDouble(long value)
{
    return *reinterpret_cast<double*>(&value);
}

char HEADER[2] = {'M', 'T'};
short VERSION = 0x0001;
