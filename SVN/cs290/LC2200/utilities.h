#ifndef INCLUDED_utilities
#define INCLUDED_utilities

// PRE: num is defined. 0 <= num < 16
// POST: RV is the hex character for num
char hexChar (int num);

// PRE: num is an unsigned long long int that fits in 32 bits.
// POST: RV is a string "hhhhhhhh" that is the hexadecimal
//        representaion of num.  
char * uIntToHex (unsigned long long int num);

int hexCharToInt (char h);

long long int hex8StrToInt (char hexStr[]);

#endif
