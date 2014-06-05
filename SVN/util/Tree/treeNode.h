#ifndef INCLUDED_treeNode
#define INCLUDED_treeNode
#include <iostream>

using namespace std;

template <class T>
class treeNode{
  //CI:  treeNode is an element in a Tree class, node can hold any data
  //     type
 private:
  T data; //the data 
  treeNode<T> * left; //left child
  treeNode<T> * right; //right child

  //Pre:  num1 and num2 are defined
  //Post: The larger of the two is returned
  int maximum(int num1, int num2) const{
    int max = num1;
    if (num2 > num1){
      max = num2;
    }
    return(max);
  };

  //Pre:  other is defined and has data of the same type as this
  //Post: The data values for the two are swapped
  void swap(treeNode<T> * other){
    //Swap data values
    T temp = data;
    data = other->data;
    other->setData(temp);
  }

  // Pre:  
  // Post: This node is swapped appropriately and removed
  void swapAndRemove(treeNode<T> *& toThis){
    int leftHeight = left->height(); //get left height
    int rightHeight = right->height(); //get right height
    treeNode<T> * toSwap; //storage for rightMost pointer
    if (maximum(leftHeight,rightHeight) == leftHeight){
      //ASSERT: the left subtree height is greater
      toSwap = left->rightMost();
      swap(toSwap);
    }
    else{ //the right subtree is larger
      //ASSERT: the right subtree height is greater
      toSwap = right->leftMost();
      swap(toSwap);
    }
    deleteNode(toSwap, toThis);
  };

  // Pre:  newHead is supposed to take the place of this, newHead is
  //       non-NULL and toThis is the pointer to this
  // Post: newHead is set as the location for toThis and this is freed
  void quickRemove(treeNode<T> *& newHead, treeNode<T> *& toThis){
    toThis = newHead; //pass the newHead up
    newHead = NULL; //set the pointer to newHead to NULL to avoid
    //       recursive deletion
    delete(this); //free this from memory since it is removed
  };

  //Pre:  toDelete is defined, toThis is the pointer to this node
  //Post: if left or right is the node to be deleted it is removed,
  //      otherwise the found variable is returned as false
  bool deleteHelper(treeNode<T> * toDelete, treeNode<T> *& toThis){
    bool found = false; //assume that it is not found to start
    if (((left==NULL) || (!(*left==*toDelete)))
	&& (*toDelete == *this)){ //check to make
      //sure this is the deepest node of this value
      found = true; //we have found the perpetrator!
      if (left == NULL){ //left isn't defined
	quickRemove(right, toThis); //remove and replace this
      }
      else{ //left is defined
	if (right == NULL){ //right isn't defined
	  quickRemove(left, toThis); //remove and replace this
	}
	else{ //both left and right are defined
	  swapAndRemove(toThis); //swap and remove this node
	}
      }
    }
    return(found);
  };

 public:

  //========================================
  //           Constructors
  //========================================

  //Pre:  
  //Post: default constructor
  treeNode(){
    left = NULL;
    right = NULL;
  };

  //Pre:  newData is defined
  //Post: newData is saved to data
  treeNode(T newData){
    data = newData;
    left = NULL;
    right = NULL;
  };

  //========================================
  //             Destructor
  //========================================

  //Pre:  
  //Post: left and right are deleted
  ~treeNode(){
    if (left != NULL){
      delete(left);
    }
    if (right != NULL){
      delete(right);
    }
  };

  //========================================
  //              Operators
  //========================================

  //Pre:  other is defined
  //Post: bool for if this.data > other.data
  bool operator> (const treeNode<T> & other) const{
    return(data>other.data);
  };

  //Pre:  other is defined
  //Post: bool for if this.data < other.data
  bool operator< (const treeNode<T> & other) const{
    return(data<other.data);
  };

  //Pre:  other is defined
  //Post: bool for if this.data >= other.data
  bool operator>= (const treeNode<T> & other) const{
    return(data>=other.data);
  };

  //Pre:  other is defined
  //Post: bool for if this.data <= other.data
  bool operator<= (const treeNode<T> & other) const{
    return(data<=other.data);
  };

  //Pre:  other is defined
  //Post: bool for if this.data == other.data
  bool operator== (const treeNode<T> & other) const{
    return(data==other.data);
  };

  //========================================
  //       Modifiers:  "set" methods
  //========================================

  //Pre:  newtreeNode is defined
  //Post: the left child is set to newtreeNode
  void setLeft(treeNode<T> * newtreeNode){
    left = newtreeNode;
  };

  //Pre:  newtreeNode is defined
  //Post: the right child is set to newtreeNode
  void setRight(treeNode<T> * newtreeNode){
    right = newtreeNode;
  };

  //Pre:  newData is defined
  //Post: data is updated with its new value
  void setData(T newData){
    data = newData;
  };

  //========================================
  //            Accessors
  //========================================

  //Pre:  
  //Post: data is returned after being dereferenced
  T getData() const {return(data);};

  //Pre:  
  //Post: The right child pointer is returned
  treeNode<T> * getRight() const {return(right);};

  //Pre:  
  //Post: The left child pointer is returned
  treeNode<T> * getLeft() const {return(left);};

  //Pre:  
  //Post: Return the max height at the current node
  int height() const{
    int max = 0; //height holder
    if (right != NULL){ //if there is a right child
      max = right->height(); //get it's height
    }
    if (left != NULL){ //if there is a left child
      max = maximum(max, left->height()); //get the max of the left
      //(and possibly the right) and set it to max
    }
    return(max+1); //return max + 1 (for including current node)
  };

  //Pre:  
  //Post: The leftmost descendant is returned
  treeNode<T> * leftMost(){
    treeNode<T> * bottomLeft = this;
    if (left != NULL){
      bottomLeft = left->leftMost();
    }
    return(bottomLeft);
  };

  //Pre:  
  //Post: The rightmost descendant is returned
  treeNode<T> * rightMost(){
    treeNode<T> * bottomRight = this;
    if (right != NULL){
      bottomRight = right->rightMost();
    }
    return(bottomRight);
  };

  //========================================
  //            Operations
  //========================================

  //Pre:  newtreeNode is defined
  //Post: addSorted called recursively 'til the final location's found
  void addLeft(treeNode<T> * newtreeNode){
    if (left == NULL){
      left = newtreeNode;
    }
    else{
      left->addSorted(newtreeNode);
    }
  };

  //Pre:  newtreeNode is defined
  //Post: addSorted called recursively 'til the final location's found
  void addRight(treeNode<T> * newtreeNode){
    if (right == NULL){
      right = newtreeNode;
    }
    else{
      right->addSorted(newtreeNode);
    }
  };

  //Pre:  newtreeNode is defined
  //Post: newtreeNode is added in a traditional binary tree sorted order
  void addSorted(treeNode<T> * newtreeNode){
    if (*newtreeNode > *this){
      addRight(newtreeNode);
    }
    else{
      addLeft(newtreeNode);
    }
  };

  //Pre:  toDelete is defined
  //Post: 
  void deleteNode(treeNode<T> * toDelete, treeNode<T> *& toThis){
    if (! deleteHelper(toDelete, toThis)){ //if the delete helper did not delete
      if ((*toDelete > *this)&&(right != NULL)){
	right->deleteNode(toDelete, right);
      }
      else{
	if (left != NULL){
	  left->deleteNode(toDelete, left);
	}
      }
    }
  };

  //Pre:  All nodes either have no children or two (strictly huffman tree)
  //Post: All child nodes' data is summed, and then the sum of the
  //      data of the children of this node is saved to data.
  //      Properly handles cases where the child is a NULL pointer
  void sumData(){
    if ((right != NULL)&&(left != NULL)){
      right->sumData();      
      left->sumData();
      //ASSERT: all child data has been updated
      data = right->data + left->data;
    }
  };

  //========================================
  //              Output
  //========================================

  //Pre:  out is defined, N is defined
  //Post: depth first, in binary sorted tree, should be ascending
  //      order 
  friend ostream & operator<< (ostream & out, const treeNode<T> & N){
    if (N.left != NULL){ //if there is a left child
      out << *N.left; //print that
    }
    out << N.data; //print the data
    if (N.right != NULL){ //if there is a right child
      out << *N.right; //print that
    }
    return(out);
  };
};

#endif
