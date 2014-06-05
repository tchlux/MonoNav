//**********************  FILE: date.h **************************************
//
// This class contains the declarations for the Date class which models
// a date on the Gregorian calendar in the years 1800 - 2100.
//
// A Date has attributes month, day, year. The date is always a valid
// date in the given range; attempts to construct invalid dates result
// in a date with a default value of 1 (if the month is invalid), 1
// if the day is invalid), and 1800 (if the year is invalid).
//
// Methods provided for manipulating dates are below.  
// 
// Programmer: J. Ingram
// Date: February 26, 2009
// 
//**************************************************************************

#ifndef DATE_DEF
#define DATE_DEF


//*********************************************
//******        Date Declaration         ******
//*********************************************

class Date
{
 public:
  Date ();                      // constructs a Date with a default value
  Date (int m, int d, int y);   // constructs a date with month m, day d, year y

  int getMonth();               // returns the month (as an int in the range 1 -12)
  int getDay();                 // returns the day (as an int in the range 1 to
                                // the last day in the month)

  int getYear();                // returns the year (as an int)

  int daysInMonth();            // returns the number of days in the month

  bool leapYear();              // returns true if the current date is 
                                // in a leap year; false otherwise

  void printDate();             // prints the date in the form m/d/y


 private:
  int month;                    // the month (1 - 12)
  int day;                      // the day (1 - last day of the month)
  int year;                     // the year (1800 - 2100)
};

#endif

  
