/*

    Auther: nnyilun
    Created date: 2022/03/15
    Last update: 2022/03/15
    Description: Vector written in C language, similar to the vector in c++.
        Subscript starts at 0.
        The default initialization is 4 size, unless an array of a specific size is passed in or the user set the specified size.
        When the capacity required for inserting data is larger than the current capacity, realloc() will be used to double the capacity.
    
    Members:
        char this[0];       //pointer to itself
        void *data;         //a pointer to a space where data is stored
        size_t sizeofElem;  //size of a single element
        size_t length;      //number of elements that have been stored
        size_t capacity;    //the space occupied by the data domain, contains the unused space

    Functions: All functions are integrated into the structure named vecFunc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector{
    struct Vector this[0];
    void *data;
    size_t sizeofElem;
    size_t length;
    size_t capacity;
}vector;

struct VectorFunctions{
    
}vecFunc;
