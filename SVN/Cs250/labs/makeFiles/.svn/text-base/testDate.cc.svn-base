//*********************************************************************
// This program tests the Date class.  It constructs a default Date
// object and prints it; then it constructs two additional Date
// objects and uses several Date class methods.
//*********************************************************************

#include "date.h"

#include <iostream>
using namespace std;

int main()
{
  int m, d, y;       // month, day, year

  Date firstDate;   // Create a default date for the Date class

  cout << "Testing Dates ..." << endl << endl;
  cout << "The default date for the class is ";
  firstDate.printDate();
  cout << endl;

  cout << "Enter a today's date..." << endl;
  cout << "Month (1 - 12): ";
  cin >> m;
  cout << "Day: ";
  cin >> d;
  cout << "Year: ";
  cin >> y;
  cout << endl;

  Date today(m, d, y);

  cout << "Enter your birthday..." << endl;
  cout << "Month (1 - 12): ";
  cin >> m;
  cout << "Day: ";
  cin >> d;
  cout << "Year: ";
  cin >> y;
  cout << endl;

  Date birthday(m, d, y);

  cout << "Today's date is: ";
  today.printDate();
  if (today.leapYear())
    cout << "We are in a leap year!" << endl;

  cout << endl << "Your birthday is: ";
  birthday.printDate();
  cout << "The month you were born has " << birthday.daysInMonth()
       << " days." << endl;

  cout << endl;

  return 0;
}

