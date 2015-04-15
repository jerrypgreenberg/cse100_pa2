#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

/* Main function that is the driver for compress*/
  
int main(int argc, char* argv[]) {
    if(argc != 3){
	cerr  << "Needs two arguments." << endl;
        exit(-1);
    }
    ofstream encodeFile;
    ifstream inputFile;
    vector<int> inputTraversal(256);
    fill(inputTraversal.begin(),inputTraversal.end(),0);
    HCTree encodeTree;
    char c = 0;
    int uniqueCount = 0;
    
    encodeFile.open(argv[2],ios::binary);
    inputFile.open(argv[1],ios::binary);
    BitOutputStream outputStream(encodeFile);
    
    if(!inputFile){
      cerr << "Couldn't open input file" << endl;
      exit(-1);
    }
  
    if(!encodeFile){
      cerr << "Couldn't open output file" << endl;
      exit(-1);
    }

    cout << "Reading Input...." << endl;
    while(inputFile.good() == true){
      inputFile.get(c);
      int curr = inputTraversal.at(c);
      if(curr == 0)
	++uniqueCount;
      curr++;
      inputTraversal[c]= curr;
    }
    cout << "Found " << uniqueCount << " unique symbols in input file of size " << sizeof(inputFile) << " bytes" << endl;
 
    if(!inputFile.eof()){
      cerr << "Error reading from input file!" << endl;
      exit(-1);
    }
    
    cout << "Building Huffman code tree...." << endl;
    encodeTree.build(inputTraversal);
    inputFile.seekg(0,inputFile.beg);
    c = 0;
    cout << "Writing to output file " << argv[2] << endl;
    
    while(inputFile.good() == true){
      inputFile.get(c);
      encodeTree.encode((byte)c,outputStream);
    }

    if(!inputFile.eof()){
      cerr << "Error writing to output file!" << endl;
      exit(-1);
    }  
    
    //Write out anything left in the buffer using flush()
    outputStream.flush();
    
       
    cout << "Output file has size " << encodeFile.tellp() << "bytes" << endl;
					
    inputFile.close();
    encodeFile.close();
     /* if(c == 10)
         continue;
      isFound = false;
      if(inputTraversal.size() == 0){
       HCNode* insert = new HCNode(1,c);
       inputTraversal.push_back(*insert);
       continue;
      }
      for(vector<HCNode>::iterator it = inputTraversal.begin(); it != inputTraversal.end(); ++it){
        if(it->symbol == c){
            it->count += 1;
	    isFound = true;
            break;
         }
        }
         if(isFound == true)
           continue;       
         HCNode* newNode = new HCNode(1,c);
         inputTraversal.push_back(*newNode);
   }*/
};
