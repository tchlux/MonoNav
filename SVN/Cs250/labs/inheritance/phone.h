#ifndef included_phone
#define included_phone

class phone{

 protected:
  // these data objects can be accessed and modified by any 
  //   derived object
  int mynum;  // the number for this object
  int volume; // the volume for this object

 public:
  // default constructor
  phone();

  // PRE: number = n is defined.
  // POST: This phone object is initialised so that 
  //       mynum = n and volume = 0
  phone(int number);

  // constructor with two parameters
  // PRE: number = n and vol = v are defined
  // POST: This phone object is initialised so that 
  //       mynum = n and volume = v
  phone(int number, int vol);

  // setters
  // PRE: number = n
  // POST: This phone object is initialised so that myum = n
  void setNumber(int number);

  // PRE: newvol = v is defined
  // POST: The volume for this object is set to v
  void setVolume (int newvol);

  // PRE: newnum = n is defined.
  // POST: OS contains "<mynum> dialing <n>
  void dial (int newnum); 

  // PRE:
  // POST: OS contains "<mynum> receiving at volume <volume>"
  void receive ();
  
  // PRE: 
  // POST: RV is the volume of this object
  int getVolume ();

  /*
  // destructor
  // PRE:
  // POST: This phone object is destroyed.
  //       OS contains "Phone number <mynum> being destroyed."
  ~phone();
  */
};

#endif
