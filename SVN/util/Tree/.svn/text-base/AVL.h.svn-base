#include "iostream"

#define BALANCED 0   // Perfectly balanced node
#define LEFT_BAL -1  // Left heavy node (more elements on left)
#define RIGHT_BAL 1  // Right heavy node (more elemenets on Right)
#define LEFT_CRIT -2 // Heavy on left and a shift is required
#define RIGHT_CRIT 2 // Heavy on right and shift is required

template <class T>
class AVLNode{
public:
  T Data;  // Holds data for this node
  int Balance; // Balance of this node
  AVLNode<T> * Left;   // Left child
  AVLNode<T> * Right;  // Right child
  AVLNode<T> * Parent; // Parent's pointer to this node

  // Default constructor
  AVLNode(){ Left = Right = Parent = NULL; Balance = 0; };

  // Constructor given data
  AVLNode(const T & data) { 
    Data = data; 
    Left = Right = Parent = NULL; 
    Balance = 0;
  };

  // Destructor (linked to child nodes for cascading delete)
  ~AVLNode(){
    if (Left != NULL)
      delete(Left);
    if (Right != NULL)
      delete(Right);
    Left = NULL;    Right = NULL; // Set children to NULL to prevent 
                                  //  accidental double free
  };

  // Pre:  ostream is defined, avl has been initialized
  // Post: All of the nodes in AVL are sent to out
  friend std::ostream & operator<<(std::ostream & out, 
				   const AVLNode<T> & n){
    if (n.Left != NULL)
      out << *n.Left << " ";
    out << n.Data << " ";
    //    out << "<" << n.Data << ">";
    out << "(" << n.Balance << ")";
    if (n.Right != NULL)
      out << " " << *n.Right;
    return(out);
  };

  // Just this data is sent to terminal rather than tree
  void print() const{
    std::cerr << "-------Node-------" << std::endl;
    std::cerr << "Data   : " << Data << std::endl;
    std::cerr << "Balance: " << Balance << std::endl;
    std::cerr << "Left is NULL  : " << (Left==NULL) << std::endl;
    std::cerr << "Right is NULL : " << (Right==NULL) << std::endl;
    std::cerr << "Parent is NULL: " << (Parent==NULL) << std::endl;
    std::cerr << "------------------" << std::endl;
  }
};


template <class T>
class AVL{
protected:
  AVLNode<T> * Root;   // Root of AVL tree
  int Size;  // Number of elements in this tree


  // Pre:  toAdd points to a defined AVLNode with data in it
  // Post: The critical node for the insertion
  AVLNode<T> * getCritical(AVLNode<T> * toAdd){
    bool inserted = false;
    AVLNode<T> * critical = NULL;
    AVLNode<T> * current = Root;
    if (current == NULL){
      inserted = true;
      Root = toAdd;
    }
    while (!inserted){
      if (toAdd->Data <= current->Data){ // If data is less
	if ((critical == NULL) && (current->Balance != BALANCED))
	  critical = current; // If this node is critcally balanced
	if (current->Left == NULL){ // If there is no left child
	  inserted = true;          
	  current->Left = toAdd;    // Insert as left child
	  toAdd->Parent = current; // Give the ref to parent
	}
	else // else: there is a left child
	  current = current->Left;  // Traverse left
      }
      else{ // else: data is greater than current
	if ((critical == NULL) && (current->Balance != BALANCED))
	  critical = current; // If this node is critically balanced
	if (current->Right == NULL){ // If there is no right child
	  inserted = true;           
	  current->Right = toAdd;     // Insert as right child
	  toAdd->Parent = current; // Give the ref to parent
	}
	else // else: there is a right child
	  current = current->Right;
      }
    }    
  Size ++; // Increment size of AVL tree
  return(critical);
  };

  // Pre:  reBal is defined and initialized, current is the node that is
  //        being traversed through, toAdd is the element being added.
  //        Both should be well defined AVLNodes with Data
  // Post: The appropriate child of current is retured based off of the
  //        toAdd comparison.  reBal is adjusted according to traversal
  AVLNode<T> * reBalAndChild(int & reBal, AVLNode<T> * current,
			     AVLNode<T> * toAdd){
    AVLNode<T> * child = NULL;  // The next node in the cycle
    if (toAdd->Data <= current->Data){
      reBal += LEFT_BAL;
      child = current->Left;
    }
    else{
      reBal += RIGHT_BAL;
      child = current->Right;
    }
    return(child);
  };

  // Pre:  toRotate is initialized and non-NULL, direction == LEFT_BAL
  //       or RIGHT_BAL
  // Post: toRotate is rotated in the direction specified
  void rotate(AVLNode<T> * toRotate, int direction){
    AVLNode<T> * toSwap; // The node that will
    if (direction == LEFT_BAL){ // Left rotation
      toSwap = toRotate->Right->Left;
      toRotate->Right->Left = toRotate;
      if (toRotate->Parent == NULL) // If this is the root
	Root = toRotate->Right;
      else if (toRotate->Parent->Left == toRotate)
	toRotate->Parent->Left = toRotate->Right;
      else
	toRotate->Parent->Right = toRotate->Right;
      toRotate->Right = toSwap;
    }
    else{ // else: right rotation
      toSwap = toRotate->Left->Right;
      toRotate->Left->Right = toRotate;
      if (toRotate->Parent == NULL) 
	Root = toRotate->Left;
      else if (toRotate->Parent->Left == toRotate)
	toRotate->Parent->Left == toRotate->Left;
      else
	toRotate->Parent->Right == toRotate->Left;
      toRotate->Left = toSwap;
    }
  }

  // Pre:  toAdd is defined
  // Post: toAdd is inserted into this AVL tree
  AVLNode<T> * addNode(AVLNode<T> * toAdd){
    AVLNode<T> * critical = getCritical(toAdd);
    AVLNode<T> * toReBal = NULL;
    if (critical != NULL){
      int reBal1 = 0;
      AVLNode<T> * child1 = reBalAndChild(reBal1, critical, toAdd);
      if (reBal1 != critical->Balance){
	critical->Balance = 0;
	toReBal = toAdd;
      }
      else{
	int reBal2 = 0;
	AVLNode<T> * child2 = reBalAndChild(reBal2, child1, toAdd);
	if (reBal1 == reBal2){
	  critical->Balance = 0;
	  toReBal = child2;
	  rotate(critical, -reBal1); // Rotate critical to balance
	}
	else{
	  std::cerr << "AVL.h Line 178: " << std::endl;
	  int reBal3 = 0;
	  toReBal = reBalAndChild(reBal3, child2, toAdd);
	  if (reBal2 == reBal3){
	    std::cerr << "AVL.h Line 182: " << std::endl;
	    critical->Balance = reBal1;
	    child1->Balance = 0;
	    std::cerr << "AVL.h Line 185: " << std::endl;
	  }
	  else
	    critical->Balance = reBal2;
	  rotate(child1, -reBal2);
	  rotate(critical, -reBal1);
	  std::cerr << "AVL.h Line 191: " << std::endl;
	}
      }
    }
    else
      toReBal = Root;
    return(toReBal);
  };

public:
  // Default constructor
  AVL(){ Root = NULL; Size = 0; };

  // Destructor
  ~AVL() { if (Root != NULL) delete(Root); };

  // Pre:  data is defined
  // Post: data is inserted into this AVL tree
  void add(const T & data){
    AVLNode<T> * toAdd = new AVLNode<T>(data);
    AVLNode<T> * toReBal = addNode(toAdd);
    while ((toReBal != NULL) && (toReBal->Data != data))
      toReBal = reBalAndChild(toReBal->Balance, toReBal, toAdd);
  };

  // Pre:  ostream is defined, avl has been initialized
  // Post: All of the nodes in AVL are sent to out
  friend std::ostream & operator<<(std::ostream & out, const AVL & avl){
    if (avl.Size > 0)
      out << *avl.Root;
    return(out);
  }
};
