#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// binary tree template
template <typename T>
class BinaryTree
{
public:
   struct TreeNode
   {
      T value;           // The value in the node
      TreeNode *left;    // Pointer to left child node
      TreeNode *right;   // Pointer to right child node
   };
   typedef TreeNode* TreeNodePtr;       
   TreeNodePtr taxonomy_root_ptr, current_node_ptr; // Pointer to the root node   
   
   // Private member functions
   void insert(TreeNode *&, TreeNode *&);
   void destroySubTree(TreeNode *);
   void deleteNode(T, TreeNode *&);
   void makeDeletion(TreeNode *&);
   void displayInOrder(TreeNode *) const;
   void displayPreOrder(TreeNode *) const;
   void displayPostOrder(TreeNode *) const;
   
   // Constructor
   BinaryTree()
      { taxonomy_root_ptr = new BinaryTree<string>();}
      
   // Destructor
   ~BinaryTree()
      { destroySubTree(taxonomy_root_ptr); }
      
   // Binary tree operations
   void insertNode(T);
   bool searchNode(T);
   void remove(T);
   TreeNodePtr defaultTree();
   void populateTree();
   void guessAnimal(TreeNode *);
   bool isLeaf(TreeNode *);
   void playGame();
   void replaceParent(TreeNode*, string, string, string);
   void saveTree(TreeNode *&node, fstream &out);
   void constructTree(TreeNode *&root,fstream &file);
   void printInstructions();
   
   void displayInOrder() const
      {  displayInOrder(taxonomy_root_ptr); }
      
   void displayPreOrder() const
      {  displayPreOrder(taxonomy_root_ptr); }
      
   void displayPostOrder() const
      {  displayPostOrder(taxonomy_root_ptr); }
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template <class T>
void BinaryTree<T>::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
   TreeNode* parent;
   if (taxonomy_root_ptr==nullptr)
   {
      cout<<"inserting root"<<endl;
      nodePtr = newNode;                  // Insert the node.
      // cout<<"node inserted!!!"<<endl;
   }
   else if (nodePtr->left== nullptr)
   {
      cout<<"inserting left"<<endl;
      insert(nodePtr->left, newNode);     // Search the left branch
      parent = nodePtr;
      nodePtr = nodePtr->left;
   }
   else if (nodePtr->left!= nullptr)
   {
      cout<<"inserting right"<<endl;
      insert(nodePtr->right, newNode);    // Search the right branch  
      parent = nodePtr;
      nodePtr = nodePtr->right;

   }
   else
      return;
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template <typename T>
void BinaryTree<T>::insertNode(T item)
{
   TreeNode *newNode = nullptr;	// Pointer to a new node.

   // Create a new node and store num in it.
   newNode = new TreeNode;
   newNode->value = item;
   newNode->left = newNode->right = nullptr;
   
   // Insert the node.
   insert(newNode, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************
template <typename T>
void BinaryTree<T>::destroySubTree(TreeNode *nodePtr)
{
   if (nodePtr)
   {
      if (nodePtr->left)
         destroySubTree(nodePtr->left);
      if (nodePtr->right)
         destroySubTree(nodePtr->right);
      delete nodePtr;
   }
}
   
//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************
template <class T>
bool BinaryTree<T>::searchNode(T item)
{
   TreeNode *nodePtr = taxonomy_root_ptr;

   while (nodePtr)
   {
      if (nodePtr->value == item)
         return true;
      else if (item < nodePtr->value)
         nodePtr = nodePtr->left;
      else
         nodePtr = nodePtr->right;
   }
   return false;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template <class T>
void BinaryTree<T>::remove(T item)
{
   deleteNode(item, taxonomy_root_ptr);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template <class T>
void BinaryTree<T>::deleteNode(T item, TreeNode *&nodePtr)
{
   if (item < nodePtr->value)
      deleteNode(item, nodePtr->left);
   else if (item > nodePtr->value)
      deleteNode(item, nodePtr->right);
   else
      makeDeletion(nodePtr);
}

//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************
template <class T>
void BinaryTree<T>::makeDeletion(TreeNode *&nodePtr)
{
   // Define a temporary pointer to use in reattaching
   // the left subtree.
   TreeNode *tempNodePtr = nullptr;

   
   
   if (nodePtr == nullptr)
      cout << "Cannot delete empty node.\n";
   else if (nodePtr->right == nullptr)
   {
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->left;   // Reattach the left child
      delete tempNodePtr;
   }
   else if (nodePtr->left == nullptr)
   {
      tempNodePtr = nodePtr;
      nodePtr = nodePtr->right;  // Reattach the right child
      delete tempNodePtr;
   }
   // If the node has two children.
   else
   {
      // Move one node the right.
      tempNodePtr = nodePtr->right;
      // Go to the end left node.
      while (tempNodePtr->left)
         tempNodePtr = tempNodePtr->left;
      // Reattach the left subtree.
      tempNodePtr->left = nodePtr->left;
      tempNodePtr = nodePtr;
      // Reattach the right subtree.
      nodePtr = nodePtr->right;
      delete tempNodePtr;
   }
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************
template <class T>
void BinaryTree<T>::displayInOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      displayInOrder(nodePtr->left);
      cout << nodePtr->value << endl;
      displayInOrder(nodePtr->right);
   }
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************
template <class T>
void BinaryTree<T>::displayPreOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      cout << nodePtr->value << endl;
      displayPreOrder(nodePtr->left);     
      displayPreOrder(nodePtr->right);
   }
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************
template <class T>
void BinaryTree<T>::displayPostOrder(TreeNode *nodePtr) const
{
   if (nodePtr)
   {
      displayPostOrder(nodePtr->left);    
      displayPostOrder(nodePtr->right);
      cout << nodePtr->value << endl;
   }
}
template <class T>
void BinaryTree<T>::populateTree(){
   string line;
   ifstream infile("animalknowledge.txt");
   TreeNode* temp;

   while(!infile.eof())     //set each line of infile to 'line'
   {
      //insert node in tree
      getline(infile,line);
      if(line!="#")
      {
         this->insertNode(line);
         cin.clear();
      }
      else
      {
         getline(infile,line);
      }
   }
   infile.close();
   
   
}



template <class T>
void BinaryTree<T>::guessAnimal(TreeNode* guess)
{
   ofstream outfile;
   
   string response,accurate;
   string newAnimal, newQuestion;
   cout<<"I know, is it a "<<guess->value<<"?"<<endl;
   cin>>response;
   if(response=="yes")
      cout<<"I knew it all along!"<<endl;

   else if (response=="no")
   {
      cout<<"Oh, I thought I knew. What animal were you?"<<endl;
      cin>>newAnimal;
      
      cout<<"Ok, got it. A "<<newAnimal<<". I'll remember that next time.\n"
      <<"What is a yes/no question that will help me distinguish a "<<
      newAnimal<<" from a "<<guess->value<<"?"<<endl;
      cin.ignore();
      getline(cin, newQuestion);
      // cin.ignore();
      cout<<"As a "<<newAnimal<<", "<<newQuestion<<" Please answer [yes/no]\n";
      getline(cin,accurate);
      
      replaceParent(guess, newQuestion, newAnimal, accurate);

      //save tree to file
      fstream outfile;
      outfile.open("animalknowledge.txt", fstream::out);
      saveTree(taxonomy_root_ptr,outfile);
      outfile.close();
      
      cout<<"Thank you for teaching me a thing or two."<<endl;
   
   }
   

}

template <class T>
bool BinaryTree<T>::isLeaf(TreeNode* node)
{
   if(node->left==NULL&&node->right==NULL)
      return true;
   else
      return false;
}

//*********************************************
// Checks if current node is a leaf. If yes,   *
// runs guessAnimal, else, displays question   *
// and takes user input to switch to next node *
// Then destroys the tree.
//*********************************************
template <class T>
void BinaryTree<T>::playGame()
{
   fstream infile;
   string response;
   

   bool guessed = false;
   current_node_ptr = taxonomy_root_ptr;
   if(taxonomy_root_ptr!=NULL)
   {
      infile.open("animalknowledge.txt", ifstream::in);
      constructTree(taxonomy_root_ptr, infile);
      infile.close();
   }
   
   

   cout<<"Beginning game: "<<endl;
   while(!guessed)
   {
      if(BinaryTree<T>::isLeaf(current_node_ptr))
      {
         BinaryTree<T>::guessAnimal(current_node_ptr);
         guessed = true;
      }
      else
      {
         cout<<current_node_ptr->value<<"[yes/no]"<<endl;
         cin>>response;
         if(response=="yes")
            current_node_ptr = current_node_ptr->left;
         else
         {
            current_node_ptr = current_node_ptr->right;
         }
      }
   }
}


//***********************************************
// Take in parent node, swap parent data with   *
// question data                                *
// Then, add the new animal                     *
//***********************************************
template <class T>
void BinaryTree<T>::replaceParent(TreeNode* parent, string question, string newAnimal, string answer)
{
   TreeNode *newA, *oldA; 

   newA = new TreeNode;
   newA->value = newAnimal;
   newA->left = newA->right = NULL;

   oldA = new TreeNode;
   oldA->value = parent->value;
   oldA->left = oldA->right = NULL;

   string copy_old_animal;
   //save parent value (original animal)
   copy_old_animal = parent->value;


   
   if (answer=="yes")
   {
      // point parent to question
      parent->left = newA;
      //point parent to old animal
      parent->right = oldA;
      // parent holds question value
      parent->value = question;
      // question now holds new animal
      // newQ->value = newA->value;

   }
   else if(answer=="no")
   {
      parent->right = newA;
      //point parent to old animal
      parent->left = oldA;
      // parent holds question value
      parent->value = question;
      // question now holds new animal
      // newQ->value = newA->value;
      // //Parent (now a question) no child is now original animal
      // // oldA->value = copy;
   }
}

//******************************************************************
// Serialization of a binary tree using preorder traversal algorithm
// source:
// https://stackoverflow.com/questions/20005784/saving-a-binary-tree-to-a-file
//
//******************************************************************
template <class T>
void BinaryTree<T>::saveTree(TreeNode *&node, fstream &out)
{
   if(node==NULL)
   {
      out<<"#"<<endl;
   }
   else
   {
      out<<node->value<<endl;
      saveTree(node->left, out);
      saveTree(node->right, out);
   }
}


template <class T>
void BinaryTree<T>::constructTree(TreeNode *&root,fstream &file)
{
   string text;
   
   getline(file,text);
   
   if(text!="#")
   {
      root = new TreeNode;
      root->value = text;
      constructTree(root->left,file);
      constructTree(root->right,file);
   }
   else
   {
      root = NULL;
   }
}

template <class T>
typename BinaryTree<T>::TreeNodePtr BinaryTree<T>::defaultTree()
{
   TreeNode *yes_yes = new TreeNode;
   TreeNode *yes_no = new TreeNode;
   TreeNode *no_yes = new TreeNode;
   TreeNode *no_no = new TreeNode;
   TreeNode *yes = new TreeNode;
   TreeNode *no = new TreeNode;
   
   yes_yes->value = "kangaroo";
   yes_yes->left = yes_yes->right = NULL;

   yes_no->value = "mouse";
   yes_no->left = yes_no->right = NULL;
   
   no_yes->value = "trout";
   no_yes->left = no_yes->right = NULL;
   
   no_no->value = "robin";
   no_no->left = no_no->right = NULL;
   
   no->value = "Do you live underwater?";
   no->left = no_yes;
   no->right = no_no;

   yes->value = "Are you bigger than a cat?";
   yes->left = yes_yes;
   yes->right = yes_no;

   taxonomy_root_ptr->value = "Are you a mammal?";
   taxonomy_root_ptr->left = yes;
   taxonomy_root_ptr->right = no;

   return taxonomy_root_ptr;
}

template <class T>
void BinaryTree<T>::printInstructions()
{
   cout<<
   "Hello, I am Sherlock and I think I can guess what animal you are thinking of.\n"
   <<"Let's see if I am right.\n"
   <<"I will start by asking you some yes/no questions about what animal you\n"
   <<"are and you will answer me yes/no. If I am right, I win. If I am wrong,"
   <<" then, you will help me learn by telling me the new animal."<<endl;
}
#endif