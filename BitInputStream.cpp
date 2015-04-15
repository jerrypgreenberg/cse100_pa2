#include "BitInputStream.hpp"

int BitInputStream::readBit()
{
    //buffer is empty so we need to fill it first
    if (bufi == 8){
        if (in.eof()) return -1;

        buf = in.get();
        //now buffer is full
        bufi = 0;
    }

    bufi++;
    int bitVal = (buf >> (8 - bufi)) & 1; 
    return bitVal;   
}

int BitInputStream::readByte()
{
    if (in.eof()) return -1;
    return in.get(); //get the next byte
}

int BitInputStream::readInt()
{
    //we are going to append one byte at a time to fill up 32 bits
    int resultVal = 0;
    for (int i = 24; i > 0; i = i-8){
        if (in.eof()) return -1;
        
        int intRead = in.get();
        intRead <<= i;
        resultVal |= intRead;
        
    } 
    return resultVal;
    
}

