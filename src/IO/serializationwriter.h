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

#include "serializationconstants.h"

//#ifdef __linux
//#include <climits> //climits is needed for CHAR_BIT. however, this is temporary.
//#endif

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

private:

};
}
}
#endif // SERIALIZATIONWRITER_H
