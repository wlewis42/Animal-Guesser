// This program demonstrates the BinaryTree class template.
// It builds a binary tree with 5 nodes.
#include <iostream>
#include <fstream>
#include "BinaryTree.h"
using namespace std;



int main()
{
   string userResponse;
   bool playAgain(0);
   // Create the binary tree.
   BinaryTree<string> *taxonomy_root_ptr;
   BinaryTree<string>::TreeNode *root_question;
   
   taxonomy_root_ptr->printInstructions();
   taxonomy_root_ptr->defaultTree();
   do{
      taxonomy_root_ptr->playGame();
      cout<<"Play again? [yes/no]"<<endl;
      cin>>userResponse;
      if(userResponse=="yes")
         playAgain = true;
      else
      {   
         cout<<"Thank you, for playing!\n";
         playAgain = false;
      }
   }while(playAgain);       
   // Display the values.
   // cout << "\nHere are the values in the tree:\n";
   // taxonomy_root_ptr->displayPreOrder();
   
   return 0;
}