#include "BitOutputStream.hpp"

void writeBit(int bit)
{
    //buffer is now full
    if (bufi == 0){
        flush();
    }
    //move the buffer by one bit so we can append one bit 
    //to the least significant position
    buf <<= 1;
    bufi++;
    //now append the bit
    buf |= bit;
}

void writeByte(int b)
{
    unsigned char character = (unsigned char)b;
    out.put(character);
}

void writeInt(int i)
{   //TODO
    out.write();
}

void flush()
{
    out.put(buf);
    out.flush();
    buf = 0;
    bufi = 0;

}
