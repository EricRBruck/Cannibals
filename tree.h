/*********************************************************************************************/
/*********************************************************************************************/
/**                                                                                         **/
/** Eric Bruck                                                                              **/
/** October 17, 2011                                                                        **/
/** CS 571 Artificial Intelligence                                                          **/
/** Dr. Guillen                                                                             **/
/**                                                                                         **/
/**-----------------------------------------------------------------------------------------**/
/**                      Tree.h - Header File - g++ compiler                                **/
/**-----------------------------------------------------------------------------------------**/
/**                                                                                         **/
/** Description:                                                                            **/
/**    This is the header file fot the cannibals and missionaries problem.  This file       **/
/**    defines all the structures used in the program and decares all the functions used in **/
/**    this program.  The class containing the functions is called SearchTree.              **/
/**                                                                                         **/
/*********************************************************************************************/
/*********************************************************************************************/
#ifndef TREE_H_
#define TREE_H_

using namespace std;

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Structure for each riverbank to record the missionaries and canniblas count.   **/
/**          There will be two land structures, one for each side of the river.             **/
/**          This structure will also help to determine if the cannibals outnumber the      **/
/**          missionaries on either side of the river.  If this is the case then that       **/
/**          option for solving the initial problem is invalid.                             **/
/**          We will call the riverbanks X and Y.                                           **/
/**                                                                                         **/
/** Variables:                                                                              **/ 
/**    missionary: Number of missionaries on one side of the river.                         **/
/**    cannibals: Number of cannibals on one side of the river.                             **/
/**                                                                                         **/
/*********************************************************************************************/
struct land
{
  // missionary count
  int missionary;
  //cannibal count
  int cannibal;
};

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Information needed to compare states to check is two states are the same.      **/
/**          Each time a valid state is reached, this structure is used to record the data. **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    Xmissionary: The number of missionaries in the state to be recorded.                 **/
/**    XCannibal: The number of cannibals in the state to be recorded.                      **/
/**    Location: The location of the boat in the state to be recorded.                      **/
/**                                                                                         **/
/*********************************************************************************************/
struct previousStates
{
  // Number of missionaries on the 'X' side of the river
  int Xmissionary;
  int Ymissionary;
  // Number of cannibals on the 'Y' side of the river
  int Xcannibal;
  int Ycannibal;
  char location;
};

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: A structure to contain the infomation about a state leading to the goal state. **/
/**          There will be multiple structres created to hold the state information on all  **/
/**          states leading to the goal.                                                    **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    location: Location of the boat.  Riverside 'X' or riverside 'Y'.                     **/
/**    depth: The deoth of the state.                                                       **/
/**    X: A structure containing the number of missionaries and cannibals on the 'X' side   **/
/**       of the river                                                                      **/
/**    Y: A structure containing the number of missionaries and cannibals on the 'Y' side   **/
/**       of the river                                                                      **/
/**                                                                                         **/
/*********************************************************************************************/
struct path
{
  // Location of the boat
  char location;
  // Depth in the tree the state is located
  int depth;
  // Number of missionaries and cannibals on the 'X' side of the river
  land X;
  // Number of missionaries and cannibals on the 'Y' side of the river
  land Y;
};

/*********************************************************************************************/
/**                                                                                         **/
/** Purpose: Structure for a double linked list to search for the solution to the initial   **/
/**          problem with in the tree of all possible combinations of cannibals and         **/
/**          missionaries faired across the river.                                          **/
/**                                                                                         **/
/** Variables:                                                                              **/
/**    location: A character that keeps track of the location of the boat.  This            **/
/**       character will only be X or Y depending on which side of the river the            **/
/**       boat is currently on.                                                             **/
/**    depth: A number that represents the depth of the current node in the tree.           **/
/**    X: Use the previously declared structure of land to create riverbank X.              **/
/**       This is the riverbank that all the missionaries and cannibals start on.           **/
/**    Y: Use the previously declared structure of land to create riverbank Y.              **/
/**       This is the riverbank that all the missionaries and cannibals will end on.        **/
/**    leaf: The leaves of each parent node.  This is an array of 5 leaf nodes because      **/
/**       there are 5 possible movements given the boat can only fairy 2 people at a time.  **/
/**       5 possible combinations:                                                          **/
/**           # | missionaries | cannibals                                                  **/
/**          ------------------------------                                                 **/
/**           0 |      1       |     0                                                      **/
/**          ------------------------------                                                 **/
/**           1 |      2       |     0                                                      **/
/**          ------------------------------                                                 **/
/**           2 |      0       |     1                                                      **/
/**          ------------------------------                                                 **/
/**           3 |      0       |     2                                                      **/
/**          ------------------------------                                                 **/
/**           4 |      1       |     1                                                      **/
/**          ------------------------------                                                 **/
/**    parent: The parent node to any given 5 leaves                                        **/
/**    leafNum: A number ranging from 0 to 4 that represents the leaf number to the         **/
/**       parent.  The leaf number corresponds with one of the above leaf options for       **/
/**       each parent node.                                                                 **/
/**                                                                                         **/
/*********************************************************************************************/  
struct node
{
  // The location of the boat
  // Riverbank X or riverbank Y
  char location;
  // Node depth within tree
  int depth;
  
  // Riverback Y
  land X;
  // Riverback Y
  land Y;
  
  // All the leaves for each parent node
  node* leaf[5];
  // Parent node
  node* parent;
  // Leaf number to the parent node
  int leafNum;
};

/*********************************************************************************************/
/**          Class searchTree                                                               **/
/**             private                                                                     **/
/**                numberOfStates                                                           **/
/**                visitedStates                                                            **/
/**             public                                                                      **/
/**                SearchTree                                                               **/
/**                ~SearchTree                                                              **/
/**                createNode                                                               **/
/**                invalidNode                                                              **/
/**                feiry                                                                    **/
/**                expand                                                                   **/
/**                display                                                                  **/
/*********************************************************************************************/
class SearchTree
{
 private:
  // Number of valid states visited
  int numberOfStates;
  // The valid states visited
  previousStates visitedStates[20];

  // Number of states leading to the goal state
  int pathLength;
  // The states leading to the goal state
  path fullPath[15];

 public:
  /*********************************************************************************************/
  /** Puropse: Constructor.                                                                   **/
  /*********************************************************************************************/
  SearchTree();

  /*********************************************************************************************/
  /** Puropse: Destructor.                                                                    **/
  /*********************************************************************************************/
  ~SearchTree();

  /*********************************************************************************************/
  /**  Purpose: Create a new node and link it to the parent node                              **/
  /*********************************************************************************************/
  node* createNode(node* parent, int leafNum);
  
  /*********************************************************************************************/
  /**  Purpose: If the new node is invalid, delete it.                                        **/
  /*********************************************************************************************/
  node* invalidNode(node* current);
  
  /*********************************************************************************************/
  /**  Purpose: Validate the new state.                                                       **/
  /*********************************************************************************************/
  int validate(node* validate);
  
  /*********************************************************************************************/
  /**  Purpose: Create the state for the new node.                                            **/
  /*********************************************************************************************/
  void feiry(node* feiry);
  
  /*********************************************************************************************/
  /**  Purpose: Add the valid state to the list of valid states and the list of states        **/
  /**           leading to the goal state.                                                    **/
  /*********************************************************************************************/
  node* addValidState(node* current);

  /*********************************************************************************************/
  /**  Purpose: Remove the last node entered into the set of all states leading to the goal   **/
  /**           state.  This is because the last state in the list has not valid chiled nodes.**/
  /*********************************************************************************************/
  void removeLastPathEntry();

  /*********************************************************************************************/
  /**  Purpose: Travers the tree to find the path to the goal state.                          **/
  /*********************************************************************************************/
  void travers(node* current);
  
  /*********************************************************************************************/
  /**  Purpose: Display the states leading to the goal state.                                 **/
  /*********************************************************************************************/
  void display(node* current);
};

#endif
