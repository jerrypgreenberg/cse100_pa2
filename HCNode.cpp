#include "HCNode.hpp"

bool HCNode::operator< (HCNode const & other)
{
    if (count != other.count){
        return count > other.count;
    }
    
    //counts are the same; so use the symbols for comparison
    return symbol < other.symbol; 
}

bool HCNode::comp(HCNode* one, HCNode* other) 
{
    //must dereference the pointers must or you'll get error
    return *one < *other;
}
