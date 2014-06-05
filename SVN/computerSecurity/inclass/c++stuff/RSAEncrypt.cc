#include <iostream>
#define A 1
#define B 2

using namespace std;

//Pre:  
//Post: 
int * extended (int a, int b){
  int *return_struct;
  if (b == 0) {
    return_struct = new int[3];
    return_struct[0] = a;
    return_struct[1] = 1;
    return_struct[2] = 2;
  }
  else{
    int q = a/b;
    int m = a%b;
    return_struct = extended(b,m);
    int temp = return_struct[2];
    return_struct[2] = return_struct[1] - q*temp;
    return_struct[1] = temp;
  }
  return(return_struct);
}

int diffieHelman(

//Pre:  
//Post: 
int main(int argc, char * argv[]){
  int a = A;
  int b = B;
  int * return_value;
  return_value = extended(a, b);
  cout << "Return Value: " << return_value << endl;
}
    
