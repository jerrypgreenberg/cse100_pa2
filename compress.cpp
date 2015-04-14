#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

/* Main function that is the driver for compress*/
  
int main(int argc, char* argv[]) {
    if(argc != 3){
	cerr  << "Needs two arguments." << endl;
        exit(-1);
    }
    ofstream encodeFile;
    encodeFile.open(argv[2]);
    ifstream inputFile;
    inputFile.open(argv[1]);
    vector<HCNode> inputTraversal;
    bool isFound;
    char c;
    while(inputFile.good() == true){
      inputFile.get(c);
      if(c == 10)
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
   }
   if(!inputFile.eof()){
      cerr << "Error reading input file!" << endl;
      exit(-1);  
   }
   /*DELETE ONCE DONE TESTING */
   for(vector<HCNode>::iterator it = inputTraversal.begin(); it != inputTraversal.end(); ++it){
         cout << *it << endl;
    
    }


};
