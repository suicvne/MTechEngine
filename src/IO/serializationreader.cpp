/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#include "serializationreader.h"

MTechEngine::IO::SerializationReader::SerializationReader()
{}

int MTechEngine::IO::SerializationReader::GetSizeOfFile(const char filename[])
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

//sizeof(short) is 2
short MTechEngine::IO::SerializationReader::ReadShort(char src[], int &pointer)
{
    short temp;
    temp = short(((src[pointer++] >> 8) & 0xff) | ((src[pointer++] >> 0) & 0xff));
    return temp;
}

//sizeof(int) is 4
int MTechEngine::IO::SerializationReader::ReadInt(char src[], int &pointer)
{
    int temp;
    temp = ((src[pointer++] >> 24) & 0xff)
            | ((src[pointer++] >> 16) & 0xff)
            | ((src[pointer++] >> 8) & 0xff)
            | ((src[pointer++] >> 0) & 0xff);
    return temp;
}

bool MTechEngine::IO::SerializationReader::ReadBool(char src[], int &pointer)
{
    return src[pointer++] == 1 ? true : false;
}

char MTechEngine::IO::SerializationReader::ReadChar(char src[], int &pointer)
{
    return src[pointer++];
}

long long MTechEngine::IO::SerializationReader::ReadLong(char src[], int &pointer)
{
    long long temp;
    temp = ((src[pointer++] >> 56) & 0xff)
            | ((src[pointer++] >> 48) & 0xff)
            | ((src[pointer++] >> 40) & 0xff)
            | ((src[pointer++] >> 32) & 0xff)
            | ((src[pointer++] >> 24) & 0xff)
            | ((src[pointer++] >> 16) & 0xff)
            | ((src[pointer++] >> 8) & 0xff)
            | ((src[pointer++] >> 0) & 0xff);
    return temp;
}

float MTechEngine::IO::SerializationReader::ReadFloat(char src[], int &pointer)
{
    int data = ReadInt(src, pointer);
    return intToFloat(data);
}

double MTechEngine::IO::SerializationReader::ReadDouble(char src[], int &pointer)
{
    long long data = ReadLong(src, pointer);
    return longToDouble(data);
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
#if defined __llvm__
        char buffer[length];
#else
        char buffer* = new char[length];
#endif

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

#ifndef defined __llvm__
        free(buffer);
#endif
    }

    return -1;
}

