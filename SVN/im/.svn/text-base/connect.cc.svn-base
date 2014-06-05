#include "iostream"
#include "Matrix.h"
#include "string"
#include "vector"

#define END_PROGRAM "END" // String for end of program

using namespace std;

bool inVector(const string & str, const vector<string> & vec){
  bool in = false;
  for (int word=0; ((!in)&&(word<vec.size())); word++){
    if (!str.compare(vec[word])){
      in = true;
    }
  }
  return(in);
}

int getIndex(string & str, vector<string> & vec){
  int ind;
  bool found = false;
  for (ind=0; ((!found)&&(ind<vec.size())); ind++){
    if (!str.compare(vec[ind])){
      found = true;
    }
  }
  return (ind-1);
}

int main(int argc, char * argv[]){
  int Status = 0; // Execution status, default to 0
  int size = 10; // Size of Matrix currently
  string input; // Holde for user input
  vector<string> words; // The words that the user inputs
  Matrix<bool> * connections = new Matrix<bool>(false, size, size);
  cout << "Type \"END\" to quit this program" << endl;
  int nextFree = 0;
  while (input.compare(END_PROGRAM)){
    std::cerr << "connections->getRows(): " << connections->getRows() << std::endl;
    if (words.size() > 0){
      cout << "[";
      for (int word=0; word<words.size(); word++){
	cout << words[word] << ", ";
      }
      cout << "\b\b]" << endl;
    }     

    cout << "New word? ";    cin >> input;    cout << endl;


    if (nextFree == size){
      size *= 2;
      Matrix<bool> * temp = new Matrix<bool>(false, size, size);
      temp->setMatrix(*connections);	delete(connections);
      connections = temp;
    }
    if (inVector(input, words)){
      int index = getIndex(input, words);
      cout << "Index found: " << index << endl;
      (*connections)[index][index] = true;
      //   (*connections)[index][nextFree] = true;
      //   (*connections)[nextFree][index] = true;
    }
    else{
      words.push_back(input.c_str());            
      nextFree++;
    }

    // }

  }
  std::cerr << "connections: " << *connections << std::endl;
  connections->write("TestConnectOut.matrix");
  return(Status);
}
