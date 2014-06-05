// Pre:  num is defined, amount is + for right, - for left
// Post: num is cyclically shifted the amount given
unsigned int cyclicShift(unsigned int num, int amount);

// Pre:  hashcode is a 32 character array (33 w/ '\0') that is the hex
//       code produced by an md5 run on a password
// Post: an integer seed drawn from that md5
unsigned int makeSeed(char * hashcode, char * password);

// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_1(char * hashcode);

// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_2(char * hashcode);

// Pre:  hashcode is a 32 character MD5 fingerprint hex string
// Post: A pointer to a 6 character array created in stack space just
//       so that it's destructor gets called before it is used
char * reduction_3(char * hashcode);

char * reduction_4(char * hashcode);

char * reduction_5(char * hashcode);

char * reduction_6(char * hashcode);
