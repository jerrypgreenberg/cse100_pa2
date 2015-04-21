#include "HCTree.hpp"
#include <stack>

void HCTree::build(const vector<int>& freqs)
{
    if (freqs.size() == 0) return;
    for(int i = 0; i < 256; ++i){
        if(freqs[i] != 0)
    }
    std::priority_queue<HCNode*, std::vector<HCNode*>,HCNodePtrComp> pQueue;
    for (unsigned int i = 0; i < freqs.size(); i++){
        //skip creating new nodes if a byte doesn't exists
        //Thus, a byte would have frequency of 0
        if (freqs[i] != 0){
            //count, symbol
            leaves[i] = new HCNode(freqs[i],i);
            symbolList.push_back(i);
            //add to the queue
            pQueue.push(leaves[i]);            
        }
    }
    
    while (pQueue.size() > 1){
        HCNode *nodeOne, *nodeTwo;
        //we will pop them twice
        nodeOne = pQueue.top();
        pQueue.pop();
        nodeTwo = pQueue.top();
        pQueue.pop();
        int totalCount = nodeOne->count + nodeTwo->count;
        //create a new parent for the two nodes we extracted
        HCNode *parent = new HCNode(totalCount,nodeOne->symbol, nodeOne,nodeTwo);
        //add the two popped nodes to the new parent node
        nodeOne->p = parent;
        nodeTwo->p = parent;
       //add the new root node to the queue again
       pQueue.push(parent);
    }


    //there is only one node, that is the root
    if (pQueue.size() == 1){
        root = pQueue.top();
        pQueue.pop();    
    }

}
//Write char for length of code, char for ascII symbol, then bits for code
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
    HCNode *currNode = leaves[symbol];
    //stack of int since writeBit takes in int parameter
    stack<int> bodyStack;
    stack<int> headerStack;
    //we can't go above root since it has no parent
    while (currNode != root){
        HCNode *parentNode = currNode->p;
        if (parentNode->c0 == currNode){
            //node is on the left side of the parent
           bodyStack.push(0);
        }else{
           bodyStack.push(1);
        }
        currNode = parentNode;
    }

    for (unsigned int i = 0; i < stack.size(); i++){
        int encodedBit = stack.top();
        out.writeBit(encodedBit);
        stack.pop(); //remove each element once it's written
    }
}

int HCTree::decode(BitInputStream& in) const
{
    //start from the root and traverse down until if it is either
    //the end of the tree of we find the node
    HCNode *currNode = root;
    
    while (currNode->c0 != nullptr || currNode->c1 != nullptr){
        int bit = in.readBit();
        if (bit == 0){
            currNode = currNode->c0;
        }else if (bit == 1){
            currNode = currNode->c1;
        }else{
            return -1; //probable cause is EOF
        }

    }
    
    return currNode->symbol;
    
}

HCTree::~HCTree()
{
    clearTree(root);
    root = nullptr;
}

void HCTree::clearTree(HCNode *node)
{
    if (node != nullptr){
        //go left first and then right recursively
        clearTree(node->c0);
        clearTree(node->c1);
        //finally delete the node from the tree
        delete node;
        node = nullptr;
    }
}
