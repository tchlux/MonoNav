#include <iostream>

#define TEST_NUM 1

// Pre:  
// Post: 
void callback(){
  std::cout << "Got it working!" << std::endl;
}

// Pre:  
// Post: 
void test( void(*callback)() ){
  std::cout << "Testing :) :)" << std::endl;
  callback();
  std::cout << "Callback called" << std::endl;
}

// Pre:  
// Post: 
int main(int argc, char * argv[]){
    int status = 0; // Normal execution status
    test(callback);
    return(status);
  }
