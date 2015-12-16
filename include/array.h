#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;

#include <typeinfo>

template<typename T> class array
{
private:
    int size;
    T *myArray;
public:
    array(int s)
    {
        size = s;
        myArray = new T[size];
    }
}


#endif // ARRAY_H_INCLUDED
