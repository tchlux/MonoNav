//************************* FILE: date.cc ***********************************
//
// This file contains the definition of the Date class.
//
// Programmer: J. Ingram
// Date: February 26, 2009
//
// Usage: User-defined auxiliary files needed:
//
//        date.h,  the declaration file for the class
//
//***************************************************************************

#include "date.h"
#include <iostream>
using namespace std;


//***********************************************************************
// Constructor - constructs a default date of 1/1/1800
//
// PRE:   Date is undefined
// POST:  Date is 1/1/1800
//***********************************************************************
Date::Date()
{
  month = 1;
  day = 1;
  year = 1800;
}


//***********************************************************************
//
// Constructs a date from the parameters passed in. 
//
// PRE:  The parameters m, d, and y are defined.
// POST: If m is in the range 1 - 12, then the month is set to m
//       otherwise it is set to 1; if y is in the range 1800 - 2100
//       then the year is set to y otherwise it is set to 1800;
//       if d is in the range 1 to the last day of the month, 
//       then the day is set to d otherwise it is 1.
//***********************************************************************
Date::Date (int m, int d, int y)
{
    if (y >= 1800 && y <= 2100)
      year = y;
    else
      year = 1800;

    if (m >= 1 && m <= 12)
      month = m;
    else
      month = 1; 

    if (d >= 1 && d <= daysInMonth())
      day = d;
    else 
      day = 1;
 }


//******************************************************************
// daysInMonth determines the number of days in the month for this
// Date object
// 
// PRE:  month and year are defined
// POST: the number of days in the month is returned if the month
//       is valid; otherwise 0 is returned
//*****************************************************************
int Date::daysInMonth()
{
  int numDays;
  if (month == 4 || month == 6 || month == 9 || month == 11)
    numDays = 30;
  else if (month == 1 || month == 3 || month == 5 || month == 7 || 
	   month == 8 || month == 10 || month ==12)
    numDays = 31;
  else if (month == 2)
    if (leapYear())
      numDays = 29;
  else
    numDays = 28;
  else 
    numDays = 0;

  return numDays;
}

//***************************************************************
// leapYear determines if the current date is in a leap year
// using the rule that a year is a leap year if it is divisible
// by 400 or is divisible by 4 but not 100
//
// PRE:   year is defined
// POST:  the return value is true is the year of the current
//        date is a leap year, false otherwise.
//***************************************************************
bool Date::leapYear()
{
  return year % 400 == 0 || year % 4 == 0 && year % 100 != 0;
}


//*************************************************************
// getMonth returns the month (as an int)
//
// PRE:    month is defined
// POST:   return value is month
//*************************************************************
int Date::getMonth()
{
  return month;
}


//*************************************************************
// getDay returns the day (as an int)
//
// PRE:    day is defined
// POST:   return value is day
//*************************************************************
int Date::getDay()
{
  return day;
}


//*************************************************************
// getYear returns the year (as an int)
//
// PRE:    year is defined
// POST:   return value is year
//*************************************************************
int Date::getYear()
{
  return year;
}


//*************************************************************
// printDate outputs the date in the form month/day/year
//
// PRE:  the date is defined
// POST: the date in the form month/day/year is on the output
//       stream
//*************************************************************
void Date::printDate()
{
  cout << month << "/" << day << "/" << year << endl;
}




