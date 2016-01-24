/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#include "serializationreader.h"

MTechEngine::IO::SerializationReader::SerializationReader()
{}

short MTechEngine::IO::SerializationReader::ReadShort(char src[], int &pointer)
{
    short temp;
    temp = short(((src[pointer++] >> 8) & 0xff) | ((src[pointer++] >> 0) & 0xff));
    return temp;
}

int MTechEngine::IO::SerializationReader::ReadInt(char src[], int &pointer)
{
    return 0;
}

/**
 * @brief MTechEngine::IO::SerializationReader::ReadBytesFromFile Reads bytes from a file into a character array specified.
 * @param readInto Character array to read into.
 * @param bufferSize Initial size of the buffer.
 * @param filename Filename to read from
 * @return The new length of the file, if different.
 */
int MTechEngine::IO::SerializationReader::ReadBytesFromFile(char *readInto, int bufferSize, const char filename[])
{
    std::ifstream ifs(filename, std::ifstream::in | std::ifstream::binary);
    if(ifs) //null check
    {
        //get length of file
        ifs.seekg(0, ifs.end);
        int length = ifs.tellg();
        ifs.seekg(0, ifs.beg);

        //allocate a temporary buffer
        char buffer[length];

        ifs.read(buffer, length);
        if(ifs) //another sanity check
        {
            memcpy(readInto, buffer, length);
            return length;
        }
        else
        {
            ifs.close();
            return -1;
        }
    }

    return -1;
}

