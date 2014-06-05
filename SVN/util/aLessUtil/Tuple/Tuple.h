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

  T1 lData; //Left data of the tuple:: Must have copy constructor

  T2 rData; //Right data of the tuple:: Must have copy constructor

 public:

  //========================================
  //             Constructors
  //========================================

  //Pre:  
  //Post: Default constructor
  Tuple(){};

  //Pre:  lData and rData are defined appropriately
  //Post: saved data
  Tuple(T1 lD, T2 rD){
    lData = lD;
    rData = rD;
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
    lData = other.lData;
    rData = other.rData;
  };

  //Pre:  other is defined
  //Post: if the other tuple is equal
  bool operator== (const Tuple<T1,T2> & other){
    return((lData==other.lData)&&(rData==other.rData));
  };

  // =================================
  //      Modifiers and Accessors     
  // =================================

  // Pre:  
  // Post: Accesses the left element of tuple, for copy or mods
  T1 & left(){
    return(lData);
  }

  // Pre:  
  // Post: Accesses the right element of tuple, for copy or mods
  T2 & right(){
    return(rData);
  }

  // ==========================
  //      Ostream handling     
  // ==========================

  //Pre:  out is defined, T is defined
  //Post: out is returned
  friend ostream & operator<<(ostream & out, const Tuple<T1,T2> & T){
    out << "(" << T.lData << ", " << T.rData << ")";
    return(out);
  };

  // ======================
  //      Destructor!!     
  // ======================

  //Pre:  
  //Post: deleted
  ~Tuple(){};


// ==========================================
//      Outdatad compatibility functions     
// ==========================================

  //Pre:  lData is defined
  //Post: left is set
  void setLeft(T1 lD){
    lData = lD;
  };

  //Pre:  lData is defined
  //Post: left is set
  void setRight(T2 rD){
    rData = rD;
  };

  //Post: left is returned
  T1 getLeft(){return(lData);};

  //Post: right is returned
  T2 getRight(){return(rData);};

  //Pre:  lData and rData are defined
  //Post: left and right are set
  void set(T1 lD, T2 rD){
    lData = lD;
    rData = rD;
  };


};
#endif
