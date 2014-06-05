#ifndef INCLUDED_Tree
#define INCLUDED_Tree

#include <iostream>
#include "treeNode.h"

using namespace std;

template <class T>
class Tree {
  //CI:  Tree is the head of a tree data type, root is a pointer to a
  //     treeNode or NULL, and only treeNodes can be elements in the
  //     subsequent tree

protected:

  treeNode<T> * root; //the node that the Tree points to

public:

  //========================================
  //             Constructors
  //========================================

  //Pre:  
  //Post: default constructor
  Tree(){
    root = NULL;
  };

  //Pre:  data is defined
  //Post: root is set to a new treeNode with the given data
  Tree(T & data){
    treeNode<T> * startingtreeNode = new treeNode<T>(data);
    root = startingtreeNode;
  };

  //Pre:  startingtreeNode is defined
  //Post: root is set to the given node
  Tree(treeNode<T> * startingtreeNode){
    root = startingtreeNode;
  };

  //========================================
  //             Destructor
  //========================================

  //Pre:  
  //Post: root is deleted
  ~Tree(){
    if (root != NULL){
      delete(root);
    }
  };

  //========================================
  //             Accessors
  //========================================

  //Pre:  
  //Post: root is returned
  treeNode<T> * getRoot() const{
    return(root);
  };

  //========================================
  //             Modifiers
  //========================================

  // Pre:  data is defined
  // Post: A new treeNode is created with given data and set as root
  void setRoot(T & data){
    treeNode<T> * startingtreeNode = new treeNode<T>(data);
    setRoot(startingtreeNode);
  }

  //Pre:  startingtreeNode is defined
  //Post: root is set to the given node
  void setRoot(treeNode<T> * startingtreeNode){
    root = startingtreeNode;
  };

  // Pre:  data is defined
  // Post: data is put into a tree node and added to the tree
  void add(T data){
    treeNode<T> * newtreeNode = new treeNode<T>(data);
    add(newtreeNode);
  }

  //Pre:  new is defined
  //Post: new is added in traditional tree sorted order
  void add(treeNode<T> * newtreeNode){
    if (root == NULL){ //no root existed
      root = newtreeNode; //set the root to that node
    }
    else{
      root->addSorted(newtreeNode);
    }
  };

  //Pre:  toDelete is defined
  //Post: The given node is deleted if it exists
  void deleteNode(treeNode<T> * toDelete){
    cerr << "Tree.h Line 104: Delete node called" << endl;
    if (root != NULL){//root is a valid Node
      root->deleteNode(toDelete, root);
    }
  };
  
  // Pre:  data is defined
  // Post: deleteNode is called given a newNode with given data
  void deleteNode(T & data){
    treeNode<T> * toDelete = new treeNode<T>(data);
    deleteNode(toDelete);
  };

  //========================================
  //               Output
  //========================================

  //Pre:  out is defined, T is defined
  //Post: out is modified with the contents of T
  friend ostream & operator<< (ostream & out, const Tree<T> & tree){
    out << *tree.root; //print the root
    return(out); //return the ostream object
  };

}; //end of template class tree

#endif
