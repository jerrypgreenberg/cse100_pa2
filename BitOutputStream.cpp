#include "BitOutputStream.hpp"

void BitOutputStream::writeBit(int bit)
{
    //buffer is now full
    if (bufi == 8){
        flush();
    }
    //move the buffer by one bit so we can append one bit 
    //to the least significant position
    buf <<= 1;
    bufi++;
    //now append the bit
    buf |= bit;
}

void BitOutputStream::writeByte(int b)
{
    unsigned char character = (unsigned char)b;
    out.put(character);
}

void BitOutputStream::writeInt(int i)
{
    for(int index = 24; index > 0; index -= 8){
        int byteInt = i>>index;
        writeByte(byteInt);
    }
}

void BitOutputStream::flush()
{
    out.put(buf);
    out.flush();
    buf = 0;
    bufi = 0;

}
