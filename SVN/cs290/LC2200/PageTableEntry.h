#ifndef DEFINED_PAGETABLE
#define DEFINED_PAGETABLE

#include "constants.h"
#include "iostream"

class PageTableEntry{
  // CI: This class holds information regarding a virtual page in some
  // memory class.  It is expected that the physical page will be kept
  // track of outside of this class. It also containes a boolean for
  // whether or not this page is dirty and a counter for number of
  // words that have been used in that physical page.

protected:
  bool occupiedPage; 		// If this page is currently occupied
  bool dirtyPage;		// If this page is dirty
  ulli processID;		// PID of program in this space
  ulli virtualPage;		// The virtual page number this
				//  instance will represent
  int numWords; 		// Number of words in this entry

public:
  // Default constructor, not occupied, not dirty
  PageTableEntry(){
    occupiedPage = false;
    dirtyPage = false;
  };

  // =================
  //      Setters     
  // =================

  // Copies all of the information from pte to this
  PageTableEntry & operator=(const PageTableEntry & pte){
    occupiedPage = dirtyPage = true;
    processID = pte.processID;
    virtualPage = pte.virtualPage;
    numWords = pte.numWords;
    return(*this);
  };

  // Pre:  0 <= vP < memory size (the virtual page number), pID valid
  // Post: virtualPage is set to the given value, now this page is
  //       occupied 
  void set(ulli pID, ulli vP){ 
    processID = pID;
    virtualPage = vP; 
    occupiedPage = true;
  };

  // Resets this instances member data to initial values
  void free() { dirtyPage = occupiedPage = false; };

  // Sets the value of dirty page to the given boolean
  void dirty(bool isDirty) { dirtyPage = isDirty; };

  // Sets the number of words read into this page
  void words(int number) { numWords = number; };

  // =================
  //      getters     
  // =================

  // Returns the virtualPage for this instance
  ulli vp() const { return(virtualPage); };

  // Returns the processID for this instance
  ulli pid() const { return(processID); };
  
  // Returns bool for if this page is dirty or not
  bool dirty() const { return(dirtyPage); };

  // Returns the number of words in this page in memory
  int words() const { return(numWords); };

  // Returns whether or not this page is occupied
  bool occupied() const { return(occupiedPage); };

  // =========================
  //      Extra Operators     
  // =========================

  // Equality testing, returns true if the elements are equal in all
  //   dimensions
  bool operator==(const PageTableEntry & pte) const{
    return( (occupiedPage == pte.occupiedPage)  && 
	    (dirtyPage == pte.dirtyPage)        && 
	    (processID == pte.processID)	&&
	    (virtualPage == pte.virtualPage)	&&
	    (numWords == pte.numWords) );
  };

  // Pre:  out is defined and pte has been initialized
  // Post: The information in pte is sent to out
  friend ostream& operator<<(ostream &out, const PageTableEntry &pte){
    out << "Occupied: " << pte.occupiedPage << std::endl;
    out << "Dirty:    " << pte.dirtyPage << std::endl;
    out << "PID:      " << pte.processID << std::endl;
    out << "Virtual:  " << pte.virtualPage << std::endl;
    out << "Words:    " << pte.numWords;
    return(out);
  };

};
#endif
