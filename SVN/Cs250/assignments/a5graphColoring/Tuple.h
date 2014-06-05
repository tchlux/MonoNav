#ifndef INCLUDED_Tuple
#define INCLUDED_Tuple

#include <iostream>

using namespace std;

template <class T1, class T2>
class Tuple{
  //CI:  Each data type is well defined, including comparison
  //     operator.  Comparisons will resort to the first element,
  //     possibly will be upgraded to specify element, addition must
  //     be custom written for purpose

 protected:

  T1 left; //Left data of the tuple

  T2 right; //Right data of the tuple

 public:

  //========================================
  //             Constructors
  //========================================

  //Pre:  
  //Post: Default constructor
  Tuple(){};

  //Pre:  lData and rData are defined appropriately
  //Post: saved data
  Tuple(T1 lData, T2 rData){
    left = lData;
    right = rData;
  };

  //Pre:  other is defined and satisfies CI
  //Post: Copy constructor executed
  Tuple(const Tuple<T1,T2> & other){
    (*this) = other;
  };

  //========================================
  //             Operators
  //========================================

  //Pre:  other is defined
  //Post: copy of other saved here
  Tuple & operator= (const Tuple<T1,T2> & other){
    left = other.left;
    right = other.right;
    return(*this);
  };

  //Pre:  other is defined
  //Post: if the other tuple is equal
  bool operator== (const Tuple<T1,T2> & other){
    return((left==other.left)&&(right==other.right));
  };

  //Pre:  lData is given to be filled
  //Post: left is set in lData
  void operator[] (T1 & lData){
    lData = left;
  };

  //========================================
  //              Modifiers
  //========================================

  //Pre:  lData is defined
  //Post: left is set
  void setLeft(T1 lData){
    left = lData;
  }

  //Pre:  lData is defined
  //Post: left is set
  void setRight(T2 rData){
    right = rData;
  }

  //Pre:  lData and rData are defined
  //Post: left and right are set
  void set(T1 lData, T2 rData){
    left = lData;
    right = rData;
  }

  //========================================
  //            Accessors
  //========================================

  //Pre:  
  //Post: left is returned
  T1 getLeft(){return(left);};

  //Pre:  
  //Post: right is returned
  T2 getRight(){return(right);};
   
  //========================================
  //                Output
  //========================================

  //Pre:  out is defined, T is defined
  //Post: out is returned
  friend ostream & operator<< (ostream & out, const Tuple<T1,T2> & T){
    out << "(" << T.left << ", " << T.right << ")";
    return(out);
  };

  //========================================
  //               Destructor
  //========================================

  //Pre:  
  //Post: deleted
  ~Tuple(){};

};

#endif
