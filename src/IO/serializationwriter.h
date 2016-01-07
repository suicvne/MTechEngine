/**
  About SerializationWriter.h/SerializationWriter.cpp
  By: Mike
*/

#ifndef SERIALIZATIONWRITER_H
#define SERIALIZATIONWRITER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux
#include <climits> //climits is needed for CHAR_BIT. however, this is temporary.
#endif

namespace MTechEngine
{
namespace IO
{
class SerializationWriter
{
public:
    SerializationWriter();
    void WriteBytes(char dest[], int &pointer, char value);
    void WriteBytes(char dest[], int &pointer, short value);
    void WriteBytes(char dest[], int &pointer, int value);
    void WriteBytes(char dest[], int &pointer, long long value);
    void WriteBytes(char dest[], int &pointer, float value);
    void WriteBytes(char dest[], int &pointer, double value);
    void WriteBytes(char dest[], int &pointer, bool value);

    void WriteBytesToFile(char bytesToWrite[], int bufferSize, const char filename[]);

    /**
      Convienence methods
      */
    int floatToInt(float value);
    float intToFloat(int value);
    long doubleToLong(double value);
    double longToDouble(long value);
private:
    char HEADER[2] = {'M', 'T'}; //MT for MTechEngine
    short VERSION = 0x0001; //big endian
                            //little endian: significant bytes are at the beginning
                            //big endian: significant bytes are at the end
};
}
}
#endif // SERIALIZATIONWRITER_H
