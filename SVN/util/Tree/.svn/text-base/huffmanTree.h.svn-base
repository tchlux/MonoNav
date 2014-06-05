#ifndef INCLUDED_HuffmanTree
#define INCLUDED_HuffmanTree

#include "Tree.h"
#include "treeNode.h"

template <class T>
class huffmanTree : public Tree<T> {
  //CI:  huffman treeNodes always have two children or no children,
  //     there is no deleting from a huffman tree.

private:

  //========================================
  //            Private methods
  //========================================

  // Pre:  small1 & small2 are defined Nodes, internal is defined
  // Post: small1 & small2 are made children of internal
  void combine(treeNode<T> * small1, treeNode<T> * small2,
	       treeNode<T> * internal){
    internal->setLeft(small1);
    internal->setRight(small2);
  };

  //Pre:  new is defined and passed from huffmanAdd, internal is the
  //      newly created internal node that will be involved in the add
  //      process, root has two children
  //Post: new is added in the appropriate place along with the
  //      children of the root.  internal is going to be the new child
  //      of root, and it's children will be the smaller of the two
  void huffHelper(treeNode<T> * newtreeNode, treeNode<T> * internal){
    treeNode<T> * left = this->root->getLeft();
    treeNode<T> * right = this->root->getRight();
    T lData = left->getData();
    T rData = right->getData();
    T newData = newtreeNode->getData();
    if (((lData<=rData)&&(rData<=newData)) || 
	((rData<=lData)&&(lData<=newData))){
      //ASSERT: The left and right children should be combined
      combine(left, right, internal);
      this->root->setLeft(internal);
      this->root->setRight(newtreeNode);
    }
    else{
      if (((lData<=newData)&&(newData<=rData)) ||
	  ((newData<=lData)&&(lData<=rData))){
	//ASSERT: The left child and the new data should be combined
	combine(newtreeNode, left, internal);
	this->root->setLeft(internal);
      }      
      else{
	if (((newData<=rData)&&(rData<=lData)) || 
	    ((rData<=newData)&&(newData<=lData))){
	  //ASSERT: The right child and the new data should be combined
	  combine(newtreeNode, right, internal);
	  this->root->setRight(internal);
	}
      }
    }
  };

 public:

  //========================================
  //             Constructors
  //========================================

  //Pre:  
  //Post: default constructor
  huffmanTree(): Tree<T>(){};

  //Pre:  newRoot is defined
  //Post: this->root is set to the given node
  huffmanTree(treeNode<T> * newRoot): Tree<T>(newRoot){};

  // ========================================
  //             Accessors
  // ========================================

  // Pre:  c is a defined character, final is a defined short
  // Post: The size of the byte saved is returned
  unsigned int getByte(char c, int & size){
    unsigned int final = 0;
    treeNode<T> * curr = this->root;
    treeNode<T> * cLeft;
    treeNode<T> * cRight;
    while ((curr != NULL) && (curr->getData() != c)){
      cLeft = curr->getLeft();
      cRight = curr->getRight();
      if ((cLeft != NULL)&&(cLeft->getData().in(c))){
	final <<= 1;
	size += 1;
	curr = cLeft;
      }
      else{
	if ((cRight != NULL)&&(cRight->getData().in(c))){
	  final <<= 1;
	  final += 1;
	  size += 1;
	  curr = cRight;
	}
	else{
	  curr = NULL;
	  final = 0;
	  size = 0;
	}
      }
    }
    return (final);
  }

  // ========================================
  //              Modifiers
  // ========================================

  //Pre:  toDelete is defined
  //Post: The given node is deleted if it exists
  void deleteNode(treeNode<T> * toDelete){
    cerr << "huffmanTree.h Line 97:\n" 
	 << "ERROR: 'deleteNode' should not be called on"
	 << "huffmanTree object. " << endl;
  };

  //Pre:  Given data for a tree node
  //Post: The data is put in a node and sent to the normal add
  void huffAdd(T treeNodeData){
    treeNode<T> * newNode = new treeNode<T>(treeNodeData);
    huffAdd(newNode);
  };

  //Pre:  newtreeNode is defined
  //Post: The huffman tree is build accordingly
  //      NODES MUST BE INSERTED IN ASCENDING ORDER
  void huffAdd(treeNode<T> * newtreeNode){
    if (this->root == NULL){ //no this->root existed
      this->root = newtreeNode; //set the this->root to that node
    }
    else{ //there is already an existing tree
      treeNode<T> * newInternal = new treeNode<T>();
      if ((this->root->getRight() == NULL) || (this->root->getLeft() == NULL)){
	//ASSERT:  the tree only has one node currently
	newInternal->setLeft(this->root); //set the current node and the new
	newInternal->setRight(newtreeNode);// node to be children of the
	this->root = newInternal;         // new this->root
      }
      else{ //ASSERT: this->root has two children
	huffHelper(newtreeNode, newInternal); //add normally
      }
    }
    this->root->sumData(); //recalculate all of the data sums
  };

}; //end of template class tree
#endif
