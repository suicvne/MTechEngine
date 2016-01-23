/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#pragma once
#ifndef SERIALIZATIONCONSTANTS
#define SERIALIZATIONCONSTANTS

extern int floatToInt(float value);
extern float intToFloat(int value);
extern long doubleToLong(double value);
extern double longToDouble(long value);

extern char HEADER[2]; //MT for MTechEngine
extern short VERSION; //big endian
                        //little endian: significant bytes are at the beginning
                        //big endian: significant bytes are at the end

#endif // SERIALIZATIONCONSTANTS

