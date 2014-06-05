#include "iostream"
#include "PageTableEntry.h"

int main(){
  PageTableEntry pte; // For testing the class
  std::cerr << "pte.occupied(): " << pte.occupied() << std::endl;
  std::cerr << "pte.vp(): " << pte.vp() << std::endl;
  std::cerr << "pte.pid(): " << pte.pid() << std::endl;
  std::cerr << "pte.dirty(): " << pte.dirty() << std::endl;
  std::cerr << "setting pid to 0" << std::endl;
  std::cerr << "setting vp to 1" << std::endl;
  pte.set(0,1);
  std::cerr << "pte.occupied(): " << pte.occupied() << std::endl;
  std::cerr << "pte.pid(): " << pte.pid() << std::endl;
  std::cerr << "pte.vp(): " << pte.vp() << std::endl;
  std::cerr << "Setting dirty bit to true" << std::endl;
  pte.dirty(true);
  std::cerr << "pte.dirty(): " << pte.dirty() << std::endl;
  std::cerr << "Freeing information" << std::endl;
  pte.free();
  std::cerr << "pte.occupied(): " << pte.occupied() << std::endl;
  std::cerr << "pte.vp(): " << pte.vp() << std::endl;
  std::cerr << "pte.pid(): " << pte.pid() << std::endl;
  std::cerr << "pte.dirty(): " << pte.dirty() << std::endl;
return(0);
}
