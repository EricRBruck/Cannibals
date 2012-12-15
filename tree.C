/*********************************************************************************************/
/*********************************************************************************************/
/**                                                                                         **/
/** Eric Bruck                                                                              **/
/** October 17, 2011                                                                        **/
/** CS 571 Artificial Intelligence                                                          **/
/** Dr. Guillen                                                                             **/
/**                                                                                         **/
/**-----------------------------------------------------------------------------------------**/
/**                     Tree.C - Implimentation File - g++ compiler                         **/
/**-----------------------------------------------------------------------------------------**/
/**                                                                                         **/
/** Description:                                                                            **/
/**    This is the implementation file for the cannibals and missonaries problem.           **/
/**    This file continas the following functions:                                          **/
/**       SearchTree                                                                        **/
/**       ~SearchTree                                                                       **/
/**       createNode                                                                        **/
/**       invalidNode                                                                       **/
/**       validate                                                                          **/
/**       feiry                                                                             **/
/**       addValidState                                                                     **/
/**       removeLastPathEntry                                                               **/
/**       display                                                                           **/
/**       travers                                                                           **/
/**                                                                                         **/
/*********************************************************************************************/
/*********************************************************************************************/
#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

// The maximum depth of the tree
#define MAX_DEPTH 100

// A node assigned to all invalid states found in the tree
// The node is NULL
node *redFlag;

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Constructor of the class SearcTree.  This function initializes all variables   **/
/**          in the class.  All the variables are private.                                  **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    visitedStates: An array that contains a list of all the previously visited states.   **/
/**       This array has a maximum value of 20 elements                                     **/
/**       Each element in the array is a previousStates structure.  This structure contains **/
/**       the number of missionaries on both sides of the river and the number of cannibals **/
/**       on each side of the river.  The previousStates structure also contains the        **/
/**       location of the bote.  Each case of missionary and cannibal formation has two     **/
/**       distinct states, i.e. which side of the river the boat is on.                     **/
/**    visitedStates[].Xmissionary: The number of missionaries on the X side of the river.  **/
/**       Initialized to: 0                                                                 **/
/**       Valid values: int 0, 1, 2, or 3                                                   **/
/**    visitedStates[].Xcannibal: The number of cannibals on the X side of the river.       **/
/**       Initialized to: 0                                                                 **/
/**       Valid values: int 0, 1, 2, or 3                                                   **/
/**    visitedStates[].Ymissionary: The number of missionaries on the Y side of the river.  **/
/**       Initialized to: 0                                                                 **/
/**       Valid values: int 0, 1, 2, or 3                                                   **/
/**    visitedStates[].Ycannibal: The number of cannibals on the Y side of the river.       **/
/**       Initialized to: 0                                                                 **/
/**       Valid values: int 0, 1, 2, or 3                                                   **/
/**    visitedStates[].location: The location of the boat.                                  **/
/**       Initialized to: 'Q'                                                               **/
/**       Valid values: 'X' or 'Y'                                                          **/
/**    numberOfStates: The number of states in the visitedStates array                      **/
/**       Valid values: 0-20                                                                **/
/**    pathLength: The number of valid states to the final goal, i.e. all cannibals and     **/
/**       missionaries on the 'Y' side of the river.  This number is initialized to 15      **/
/**       so the while loop will go through all the elements in the fullPath array and      **/
/**       reset the values.  By the end of the while loop this number will be 0.            **/
/**       Valid values: 0-15                                                                **/
/**                                                                                         **/
/*********************************************************************************************/
SearchTree::SearchTree()
{
  // Initialize all the values in the array containing all the visited states
  for(int i = 0; i < 20; i++)
    {
      // Number of missionaries on both sides of the river
      visitedStates[i].Xmissionary = 0;
      visitedStates[i].Ymissionary = 0;
      // Number of cannibals on both sides of the river
      visitedStates[i].Xcannibal = 0;
      visitedStates[i].Ycannibal = 0;
      // The side of the river the boat is on
      visitedStates[i].location = 'Q';
    }

  // The number of visited states
  numberOfStates = 0;

  // The number of states leading to the goal state
  // Set to 15 only for the while loop.  The larges this number can be is 15
  // By the end of the while look pathLength will be 0
  pathLength = 15;
  // Initialize all the values of the states leading to the goal state 
  while(pathLength != 0)
    { removeLastPathEntry(); }
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: The destructor for the SearchTree class.  This does nothing.                   **/
/**                                                                                         **/
/*********************************************************************************************/
SearchTree::~SearchTree()
{ ; }

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Create a new node in the tree and initialize all the elements within the node  **/
/**          structure.                                                                     **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    parent: The parent of the node being created.                                        **/
/**    leafNum: The leaf of the parent this node is being created in.                       **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    temp: A temporary node to hold all the information of the new node while it is       **/
/**       initialized.                                                                      **/
/**    temp->leafNum: The leaf number this node is in relation to the parent node.  There   **/
/**       are only 5 leafs for each parent.                                                 **/
/**       Valid values: 0-4                                                                 **/
/**    temp->leaf: An array of 5 that will contain all the child nodes of this new parent   **/
/**       node.                                                                             **/
/**       initialized to: NULL                                                              **/
/**       Valid Values: A new node                                                          **/
/**    temp->parent: This points to the parent node of the newly created node.              **/
/**       Valid values: The parent node                                                     **/
/**    temp->depth: The current depth in the tree with the addition of this new node.       **/
/**       Valid values: 0-100 (This limit is set by MAX_DEPTH)                              **/
/**                                                                                         **/
/** Return:                                                                                 **/
/**    temp: Return the node that was created to become the current node being expanded.    **/
/**                                                                                         **/
/*********************************************************************************************/
node* SearchTree::createNode(node *parent, int leafNum)
{
  // New node
  node *temp;
  temp = new node;

  // The leaf number of the parent node
  temp->leafNum = leafNum;

  // Set all the leaf nodes of the new node to NULL  
  for(int i = 0; i < 5; i++)
    { temp->leaf[i] = NULL; }
  
  // Paoint the new node to its parent node
  temp->parent = parent;
  // Set the depth of the new node
  temp->depth = parent->depth + 1;
  // Set the leaf of the parent node to the new node
  parent->leaf[leafNum] = temp;
  
  return temp;
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Delete any invalid nodes and have them point to a null node.                   **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    current: The invalid node to be deleted                                              **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    invalidLeaf: The invalid leaf number of the parent node.                             **/
/**    redFlag: A null node that all invalid nodes will point to.                           **/
/**                                                                                         **/
/** Return:                                                                                 **/
/**    current: The parent node of the invalid node.  This will become the new current node **/
/**                                                                                         **/
/*********************************************************************************************/
node* SearchTree::invalidNode(node *current)
{
  // The leaf number of the invalid node
  int invalidLeaf = current->leafNum;
  
  // Change the current node to the parent node of the invalid node
  current = current->parent;
  // Delete the invalid node
  delete current->leaf[invalidLeaf];
  // Make the leaf that is the invalid node point to a NULL node
  current->leaf[invalidLeaf] = redFlag;
  
  return current;
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Verify if the new node created is a valid state.                               **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    validate: The node to be validated.                                                  **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    Xmis: The number of missionaries on the 'X' side of the river.                       **/
/**    Ymis: The number of missionaries on the 'Y' side of the river.                       **/
/**    Xcan: The number of cannibals on the 'X' side of the river.                          **/
/**    Ycan: The number of cannibals on the 'Y' side of the river.                          **/
/**                                                                                         **/
/** Return:                                                                                 **/
/**    An integer is returned.  This number is 0, 1, or 2 depending on the validity of the  **/
/**    new node.                                                                            **/
/**       0: The new node is an invalid state because of one of the following               **/
/**          There are more cannibals then missionaries on the 'X' side of the river.       **/
/**          There are more cannibals then missionaries on the 'Y' side of the river.       **/
/**          There are fewer then 0 missionaries on the 'X' or 'Y' side of the river.       **/
/**          There are grater then 3 missionaries on the 'X' or 'Y' side of the river.      **/
/**          There are fewer then 0 cannibals on the 'X' or 'Y' side of the river.          **/
/**          There are grater then 3 cannibals on the 'X' or 'Y' side of the river.         **/
/**          The new node is a state that has previously been visited.                      **/
/**       1: The new node is a valid state                                                  **/
/**       2: The new node is the goal state.  This only occures when there are 3 cannibals  **/
/**          and 3 missionaries on the 'Y' side of the river.                               **/
/**                                                                                         **/
/*********************************************************************************************/
int SearchTree::validate(node *validate)
{
  // Number of missionaries on the 'X' and 'Y' side of the river in the new state
  int Xmis = validate->X.missionary;
  int Ymis = validate->Y.missionary;

  // Number ofcannibals on the 'X' and 'Y' side of the river in the new state
  int Xcan = validate->X.cannibal;
  int Ycan = validate->Y.cannibal;
  
  //cout<<Xcan<<" "<<Xmis<<" "<<Ycan<<" "<<Ymis<<endl;
  // If the new state is invalid
  if((Xcan > Xmis && Xmis !=0) || (Ycan > Ymis && Ymis !=0)
     || Xmis > 3 || Xmis < 0 || Ymis > 3 || Ymis < 0
     || Xcan > 3 || Xcan < 0 || Ycan > 3 || Ycan < 0)
    { return 0; }
  // If the new state is the goal state
  else if(Ycan == 3 && Ymis == 3)
    { return 2; }
  else
    {
      // Go through all the previously visited states
      for(int i = 0; i < numberOfStates; i++)
	{
	  // If the new state is a previously visited state
	  if(visitedStates[i].Xmissionary == Xmis
	     && visitedStates[i].Xcannibal == Xcan
	    && visitedStates[i].location == validate->location)
	    { return 0; }
	}
      // If the new state is a valid state and not the goal state
      return 1;
    }
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Create the state for a new node created.  Add subract missionaries and         **/
/**          cannibals to both side of the river.                                           **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    feiry: The current node to create the new state with.                                **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    numM: The number of missionaries to move across the river.                           **/
/**    numC: The number of cannibals to move across the rive.                               **/
/**                                                                                         **/
/** Algorithem: depending on the leaf number of the current node in relation to the paretnt **/
/**             determins the number of missionaries and cannibals that eill be moved       **/
/**             across the river.                                                           **/
/**             Leaf number = 0: move 1 missionary across the river.                        **/
/**             Leaf number = 1: move 2 missionarys across the river.                       **/
/**             Leaf number = 2: move 1 cannibal across the river.                          **/
/**             Leaf number = 3: move 2 cannibals across the river.                         **/
/**             Leaf number = 4: move 1 missionary and 1 cannibal across the river.         **/
/**             After the number of cannibals and missionaries to move is decided, add and  **/
/**             subtract those numbers from the current state, then change the side of the  **/
/**             river the boat is on                                                        **/
/**                                                                                         **/
/*********************************************************************************************/
void SearchTree::feiry(node *feiry)
{
  // The number of missionaries and cannibals to move across the river
  int numM, numC;
  numM = 0;
  numC = 0;
  
  // Switch statement determined by the leaf number of the current node
  switch (feiry->leafNum)
    {
      // Move 1 missionary
    case 0:
      numM = 1;
      break;
      
      // Move 2 missionaries
    case 1:
      numM = 2;
      break;
      
      // Move 1 cannibal
    case 2:
      numC = 1;
      break;
      
      // Move 2 cannibals
    case 3:
      numC = 2;
      break;
      
      // Move i missionary and 1 cannibal
    case 4:
      numM = 1;
      numC = 1;
      break;
    }

  // If the boat is on the 'X' side of the river
  // Subtract the number of missionraies and cannibals moved from the 'X' side of the river
  // Add the number of missionraies and cannibals moved from the 'Y' side of the river
  // Change the boat location to 'Y'
  if(feiry->depth % 2 != 0)
    {
      feiry->X.missionary -= numM;
      feiry->Y.missionary += numM;
      feiry->X.cannibal -= numC;
      feiry->Y.cannibal += numC;
      feiry->location = 'Y';
    }
  // If the boat is on the 'Y' side of the river
  // Subtract the number of missionraies and cannibals moved from the 'Y' side of the river
  // Add the number of missionraies and cannibals moved from the 'X' side of the river
  // Change the boat location to 'Y'
  else
    {
      feiry->X.missionary += numM;
      feiry->Y.missionary -= numM;
      feiry->X.cannibal += numC;
      feiry->Y.cannibal -= numC;
      feiry->location = 'X';
    }
  
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Display the information for a node.                                            **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    current: The node to be displayed.                                                   **/
/**                                                                                         **/
/*********************************************************************************************/
void SearchTree::display(node *current)
{
  cout << "------Final State Node Info------\n"
       << "Depth: " << current->depth << "\n"
       << "Current location: " << current->location << "\n"
       << "Missionary(X):    " << current->X.missionary << "\n"
       << "Cannibal(X):      " << current->X.cannibal << "\n"
       << "Missionary(Y):    " << current->Y.missionary << "\n"
       << "Cannibal(Y):      " << current->Y.cannibal << "\n"
       << "---------------------------------\n";
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Add all valid visited states to the visitedStates array and the array          **/
/**          contining only the valid states that lead to the goal state.  The visitedStates**/
/**          array contains all the valid visited states to prevent traversal of those      **/
/**          same states further down the tree.  The FullPath only contains the visited     **/
/**          states that lead to the goal state.  If a valid state and not falid child      **/
/**          states, then that node is removed form the fullPath array.                     **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    current: The node to be added to the array of all visited states and the array of all**/
/**       states leading to the goal state.                                                 **/
/**                                                                                         **/
/*********************************************************************************************/
node* SearchTree::addValidState(node *current)
{
  // Add state to the array of all visited states
  visitedStates[numberOfStates].Xmissionary = current->X.missionary;
  visitedStates[numberOfStates].Ymissionary = current->Y.missionary;
  visitedStates[numberOfStates].Xcannibal = current->X.cannibal;
  visitedStates[numberOfStates].Ycannibal = current->Y.cannibal;
  visitedStates[numberOfStates].location = current->location;

  // Increase the total number of visited states
  numberOfStates++;

  // Add state to the array of states keading to the goal state
  fullPath[pathLength].location = current->location;
  fullPath[pathLength].depth = current->depth;
  fullPath[pathLength].X.missionary = current->X.missionary;
  fullPath[pathLength].Y.missionary = current->Y.missionary;
  fullPath[pathLength].X.cannibal = current->X.cannibal;
  fullPath[pathLength].Y.cannibal = current->Y.cannibal;

  // Increase the total number of states leading to the goal state
  pathLength++;
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Remove a valid node that does not have any valid leaf nodes.  Menaing this is  **/
/**          node does not lead to the goal state.                                          **/
/**                                                                                         **/
/*********************************************************************************************/
void SearchTree::removeLastPathEntry()
{
  // Decrease the total path length by one
  pathLength--;

  // Reset all the values for the last node in the list
  fullPath[pathLength].location = 'Q';
  fullPath[pathLength].depth = -1;
  fullPath[pathLength].X.missionary = 0;
  fullPath[pathLength].X.cannibal = 0;
  fullPath[pathLength].Y.missionary = 0;
  fullPath[pathLength].Y.cannibal = 0;
}

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Travers the tree to find a path to the goal state.  The goal state is where    **/
/**          there are 3 missionaries and 3 cannibals on the 'Y' side of the river.  The    **/
/**          initial state is where there are 3 missionaries and 3 cannibals in the 'X'     **/
/**          side of the river.                                                             **/
/**                                                                                         **/
/** Arguments:                                                                              **/
/**    current: The root node of the tree.  The root node is declared in the client file    **/
/**       names cannibal.C.  This is the node to start expanding to find the goal state.    **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    validMove: A number that ranges from 0 to 2 returned from the validate function to   **/
/**       determin if the current state is a valid state.                                   **/
/**       validMove = 0: The state is not valid                                             **/
/**       validMove = 1: The state is valid                                                 **/
/**       validMove = 2: The state is the goal state                                        **/
/**    temp: a tempory place holder for a node.                                             **/
/**    tempLeafNum: A tempory place holder for the number of the leaf.                      **/
/**                                                                                         **/
/** Algorithem: Add the current node (the root node) to the list of all visited node and    **/
/**             visited nodes that lead to the goal state.  Start a while loop to travers   **/
/**             the leaf nodes from the root node.  This while loop will go untill the goal **/
/**             state is found or the tree reaches a defined depth (MAX_DEPTH defined to be **/
/**             100).  Go through all the leaf node of the current parent node and find the **/
/**             next null leaf node, i.e. a leaf node that has not been expanded.  If a     **/
/**             NULL leaf is found create a new node and set it to the current node.  none  **/
/**             of the leafs are null, this implies that all the child nodes are invalid    **/
/**             states.  At this point set the current node to the parent node.  Then delete**/
/**             the previously current node.  Then make the current node the next leaf of   **/
/**             the current node.  The node that was just deleted is not part of the path   **/
/**             leading to the goal state so it is removed from the list of states leading  **/
/**             to the goal state.  At the end of the for loop a new node has been created. **/
/**             If the current node is not the root node then set the current nodes state   **/
/**             to the state of the parent node.  Move the missionaries and cannibals based **/
/**             on the leaf number of the current node to creat a new state.  Validate this **/
/**             new state.  The return value after validating the current state determins if**/
/**             the state is valid or not.  If the state is valid, add the new state to the **/
/**             list of visited states and the list of states leading to the goal state.    **/
/**             If the current state is invalid, delete the node and have the leaf point to **/
/**             a NULL node.  If the current state is the goal state, add the state to the  **/
/**             list of all visited states and the list of states leading to the goal state.**/
/**             Then display all the states leading to the goal state.  At this point leave **/
/**             the while loop.  You have achieved your goal.                               **/
/**                                                                                         **/
/*********************************************************************************************/
void SearchTree::travers(node *current)
{
  // A value that represents wether a state is valid or not
  int validMove = 0;
  // A temp node
  node *temp;
  temp = new node;
  // A lemp value to hold the leaf number
  int tempLeafNum = 0;
  
  // A NULL node that all the invalud node state point to
  redFlag = new node;

  // Add the root node to the list of visited nodes
  addValidState(current);
  
  // Stay in the while loop as long as the current depth of the tree is less 
  // then the defind max depth and the goal state has not been found
  while(current->depth < MAX_DEPTH)
    {
      // Go through all the child nodes of the current node
      for(int i = 0; i < 5; i++)
	{
	  // If one of the child nodes is NULL
	  // i.e. the node has not been expanded
	  if(current->leaf[i] == NULL)
	    {
	      // Create a new node
	      current = createNode(current, i);
	      break;
	    }

	  // If all the child nodes have been expanded
	  else if(i == 4)
	    {
	      // Change the temp leaf number to the next leaf of the parent node
	      tempLeafNum = current->leafNum + 1;
	      // Set current to the parent of the current node
	      current = current->parent;
	      // Set the current node to the next leaf to be checked
	      current = createNode(current, tempLeafNum);
	      // Remove the last node from the list of nodes leading to the goal state
	      removeLastPathEntry();
	      //cout<<"^^Contains No Valid States^^"<<endl;
	    }
	}
      
      // If the current node is not the root node
      if(current->depth > 0)
	{
	  // Set the current configuration of missionaries and cannibals the that of the parents
	  current->X.cannibal = current->parent->X.cannibal;
	  current->Y.cannibal = current->parent->Y.cannibal;
	  
	  current->X.missionary = current->parent->X.missionary;
	  current->Y.missionary = current->parent->Y.missionary;
	}
      
      // Move the cannibals and missionaries
      feiry(current);
      
      // Check the validity of the new state
      validMove = validate(current);

      // If the current state is valid
      if(validMove == 1)
	{
	  // Add the current state to the list of all visited states 
	  // and list of states leading to goal state
	  addValidState(current);
	  //display(current);  
	}
      // If current state is invalid
      else if(validMove == 0)
	{
	  // Delete the invalid state and set the current node to the returned null state
	  current = invalidNode(current);
	}
      // If current state is the goal state
      else if(validMove == 2)
	{
	  // Add the current state to the list of all visited states 
	  // and list of states leading to goal state
	  addValidState(current);

	  // Display the list if states leading to goal state
	  display(current);

	  cout<<"=====States====="<<endl;
	  for(int i = 0; i < pathLength; i++)
	    {
	      cout<<"Depth: "<<fullPath[i].depth<<endl;
	      cout<<"location: "<<fullPath[i].location<<endl;
	      cout<<"("<<fullPath[i].X.cannibal<<" "<<fullPath[i].X.missionary<<" : "
		  <<fullPath[i].Y.cannibal<<" "<<fullPath[i].Y.missionary<<")"<<endl;
	      //cout<<"Xmis: "<<fullPath[i].X.missionary<<endl;
	      //cout<<"Xcan: "<<fullPath[i].X.cannibal<<endl;
	      //cout<<"Ymis: "<<fullPath[i].Y.missionary<<endl;
	      //cout<<"Ycan: "<<fullPath[i].Y.cannibal<<endl;
	      cout<<"================"<<endl;
	    }
	  return;
	}
    }
}
