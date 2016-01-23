/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#ifndef SERIALIZATIONREADER_H
#define SERIALIZATIONREADER_H

#include <iostream>

#include "serializationconstants.h"

namespace MTechEngine {
namespace IO {
class SerializationReader
{
public:
    SerializationReader();
    int ReadInt(char src[], int &pointer);
};
}
}
#endif // SERIALIZATIONREADER_H
