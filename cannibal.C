/*********************************************************************************************/
/*********************************************************************************************/
/**                                                                                         **/
/** Eric Bruck                                                                              **/
/** October 17, 2011                                                                        **/
/** CS 571 Artificial Intelligence                                                          **/
/** Dr. Guillen                                                                             **/
/**                                                                                         **/
/**-----------------------------------------------------------------------------------------**/
/**                      cannibal.C - Client File - g++ compiler                            **/
/**-----------------------------------------------------------------------------------------**/
/**                                                                                         **/
/** Description:                                                                            **/
/**   This program creates the root node of the tree for the cannibals and missionaries     **/
/**   problem.  The Initial state is predefined, so this state is set as the configuration  **/
/**   of the root node.  For the root node the parent node is set to NULL. The depth is set **/
/**   to 0.  The leaf number is set to 0.  All leaf nodes are set to NULL.  The location of **/
/**   of the boat is set to 'X'.  The number of missionaries and cannibals on the 'X' side  **/
/**   is set to 3.  The number of missionaries and cannibals on the 'Y' side of the river   **/
/**   is set to 0.  With the root node created, start traversing the tree using a depth     **/
/**   first search method.                                                                  **/
/**                                                                                         **/
/*********************************************************************************************/
/*********************************************************************************************/
#include<iostream>
#include "tree.h"

using namespace std;

int main()
{
  // Create the class
  SearchTree MyTree;
  // Create the root node
  node* home = new node;

  // Set the parent of the root to NULL
  home->parent = NULL;
  // Set the depth of the root to 0
  home->depth = 0;

  // Set the leaf number of the root to 0
  home->leafNum = 0;
  // Set all the child nodes to NULL
  for(int i = 0; i < 5; i++)
    { home->leaf[i] = NULL; }

  // Set the location of the boat to 'X'
  home->location = 'X';

  // Se the missionary and cannibal configuration
  home->X.missionary = 3;
  home->X.cannibal = 3;

  home->Y.missionary = 0;
  home->Y.cannibal = 0;

  // Traverse the tree to find the solution
  MyTree.travers(home);

  return 0;
}
