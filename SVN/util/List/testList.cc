#include <iostream>
#include "List.h"
#include "Link.h"

int main(int argc, char * argv[]){

  List<int> list;
  std::cerr << "list.size(): " << list.size() << std::endl;
  list.print();
  for (int i=0; i<10; i++){
    list.append(i);
  }
  List<int> copy(list);
  std::cerr << "Copy created: " << std::endl;
  copy.print();
  std::cerr << "Actual list: " << std::endl;
  list.print();
  list.clear();
  copy.print();
  list.print();
  std::cerr << "Testing Link" << std::endl;
  Link<int> ints;
  for (int i=0; i<10; i++){
    ints.add(i);
  }
  std::cerr << "ints: " << ints << std::endl;
  std::cerr << "ints.size(): " << ints.size() << std::endl;
  std::cerr << "Removing all elements starting at back" << std::endl;
  for (int i=0; i < 8; i++)
    ints.remove(-1);
  ints.print();
  ints.remove(0); ints.print(); ints.remove(0);
  ints.print();
  return(0);
}
