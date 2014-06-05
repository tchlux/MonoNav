#include <iostream>
#include "phone.h"
#include "tt_phone.h"

using namespace std;

#define MAXPHONES 5

int main()
{

  int phoneNum = 100;

  cout << "Regular Phones" << endl;

  phone onePhone (phoneNum);
  cout << "Dialing and receiving onePhone..." << endl;
  onePhone.dial(MAXPHONES);
  onePhone.receive();

  phone phones[MAXPHONES];

  for (int i = 0; i < MAXPHONES; i++) {
    phones[i].setNumber(i + 50);
    phones[i].setVolume(i);
  }

  cout << endl << "Regular phones dialing" << endl;
  for (int i = 0; i < MAXPHONES; i++) {
    phones[i].dial(MAXPHONES);
  }

  cout << endl << "Regular phones receiving" << endl;
  for (int i = 0; i < MAXPHONES; i++) {
    phones[i].receive();
  }

  cout << "Touch Tone Phones" << endl;

  tt_phone aTTphone (phoneNum);
  cout << "Dialing and receiving a aTTphone..." << endl;
  aTTphone.dial(MAXPHONES);
  aTTphone.receive();

  cout << endl << "Mixing touch tone and regular phones" << endl;
  tt_phone newphone;
  phones[0] = newphone;
  cout << endl << "Phones dialing" << endl;
  for (int i = 0; i < MAXPHONES; i++) {
    phones[i].dial(MAXPHONES);
  }
  return (0);
}
