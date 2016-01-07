#include "serializationwriter.h"

MTechEngine::IO::SerializationWriter::SerializationWriter()
{}

///sizeof(char) = 1
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, char value)
{
    dest[(pointer)] = value;
    pointer++;
}

///sizeof(short) = 2
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, short value)
{
    //number 1, as a short
    //0x00 0x01 (0x0001)
    //extract first bit then second bit

    //shift value by 8 (8 bits in one byte), mask 0xff. extract first bit
    dest[(pointer++)] = (value >> 8) & 0xff;
    //shift zero places mask 0xff, extract second bit
    dest[(pointer++)] = (value >> 0) & 0xff;
}

///sizeof(int) = 4
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, int value)
{
    dest[(pointer++)] = (value >> 24) & 0xff;
    dest[(pointer++)] = (value >> 16) & 0xff;
    dest[(pointer++)] = (value >> 8) & 0xff;
    dest[(pointer++)] = (value >> 0) & 0xff;
}

///sizeof(long) = 8
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, long long value)
{
    dest[(pointer++)] = (value >> 56) & 0xff;
    dest[(pointer++)] = (value >> 48) & 0xff;
    dest[(pointer++)] = (value >> 40) & 0xff;
    dest[(pointer++)] = (value >> 32) & 0xff;
    dest[(pointer++)] = (value >> 24) & 0xff;
    dest[(pointer++)] = (value >> 16) & 0xff;
    //shift value by 8 (8 bits in one byte), mask 0xff. extract first bit
    dest[(pointer++)] = (value >> 8) & 0xff;
    //shift zero places mask 0xff, extract second bit
    dest[(pointer++)] = (value >> 0) & 0xff;
}

///sizeof(float) = 4
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, float value)
{
    int data = floatToInt(value);
    WriteBytes(dest, pointer, data);
}

///sizeof(double) = 8
void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, double value)
{
    long long data = doubleToLong(value);
    WriteBytes(dest, pointer, data);
}

void MTechEngine::IO::SerializationWriter::WriteBytes(char dest[], int &pointer, bool value)
{
    //bool = 1 byte ( 0 or 1 )
    dest[pointer++] = (value ? 1 : 0);
}

/**
 * @brief MTechEngine::IO::SerializationWriter::WriteBytesToFile Writes the specified byte array to a file (binary). Uses the C Standard Library
 * @param bytesToWrite The bytes to write
 * @param bufferSize The size of the buffer to write. If 0, will use the amount of bytes **present** in the bytesToWrite[]
 * @param filename The filename to write to
 */
void MTechEngine::IO::SerializationWriter::WriteBytesToFile(char bytesToWrite[], int bufferSize, const char filename[])
{
    char buffer[bufferSize];
    memset(buffer, 0, bufferSize);
    memcpy(buffer, bytesToWrite, bufferSize);

    std::ofstream ofs(filename, std::ofstream::out | std::ofstream::binary);
    ofs.write(buffer, sizeof(buffer));
    ofs.close();
    //leaving this as reference/documentation
    //FILE* file = fopen(filename, "wb");
    //fwrite(buffer, 1, sizeof(buffer), file);
    //fclose(file);
}

/**
  Convienence methods
 */

int MTechEngine::IO::SerializationWriter::floatToInt(float value)
{
    return *reinterpret_cast<int*>(&value);

    //union
    //{
    //    float input;
    //    int output;
    //} data;
    //data.input = value;
    //std::bitset<sizeof(float) * CHAR_BIT> bits(data.output);
    //return data.output;
}

float MTechEngine::IO::SerializationWriter::intToFloat(int value)
{
    return *reinterpret_cast<float*>(&value);
}

long MTechEngine::IO::SerializationWriter::doubleToLong(double value)
{
    return *reinterpret_cast<long*>(&value);
}

double MTechEngine::IO::SerializationWriter::longToDouble(long value)
{
    return *reinterpret_cast<double*>(&value);
}
