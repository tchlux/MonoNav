#include <iostream>
#define ENCIPHER_AMOUNT 3
#define MAX_STRING_SIZE 27
#define PROMPT "Tell me how you feel"
#define A_ORD 97
#define MOD 26
#define DECIPHER_AMOUNT MOD-ENCIPHER_AMOUNT

using namespace std;

void clearStr (char * str, int size) {
  for (int i = 0; i < size; i++) {
    str[i] = '\0';
  }
}

//Function: Gets the user's response to a prompt as a string
//Pre:  prompt is given
//Post: response as string
void getFeelings(char * prompt, char * response){
  cout << prompt; //prompt user
  cin >> response; //save response
}

//Function: Changes the characters in the string into numbers and
//          prints them as they are converted
void encryptResponse(char * str, char * encrypted){
  int ord;
  int c = 0; //index of characters in string
  while (str[c] != '\0'){
    ord = (int) str[c];
    encrypted[c] = (char) ((ord-A_ORD+ENCIPHER_AMOUNT)%MOD+A_ORD);
    c++;
  }
}

//Function: Changes the characters in the string into numbers and
//          prints them as they are converted
void decryptResponse(char * str, char * decrypted){
  int ord;
  int c = 0; //index of characters in string
  while (str[c] != '\0'){
    ord = (int) str[c];
    decrypted[c] = (char) ((ord-A_ORD+DECIPHER_AMOUNT)%MOD+A_ORD);
    c++;
  }
}

//Function: Returns user's responses encrypted
//Pre: None required, any from terminal will be ignored
//Post: Runloop
int main (int argc, char * argv[]){
  cout << "Welcome to the encrypter\n";
  char prompt[MAX_STRING_SIZE] = "Encrypt it: "; //The prompt the user will recieve
  char response[MAX_STRING_SIZE]; //initialize response storage
  char encrypted[MAX_STRING_SIZE]; //initialize encryption storage
  char decrypted[MAX_STRING_SIZE]; //initialize decryption storage
  char exit[5] = "exit";
  bool done = false;
  while (!done) {
    clearStr (response, MAX_STRING_SIZE);
    clearStr (encrypted, MAX_STRING_SIZE);
    clearStr (decrypted, MAX_STRING_SIZE);
    getFeelings(prompt, response);
    if (response[0] != exit[0]) {
      encryptResponse(response, encrypted);
      decryptResponse(encrypted, decrypted);
      cout << encrypted << endl;
      cout << decrypted << endl;
    }
    else {
      done = true;
    }
  }
  return(0);
}
