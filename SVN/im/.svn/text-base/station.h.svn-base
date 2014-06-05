#ifndef DEFINED_STATION
#define DEFINED_STATION

#define SUCCESSFUL_EXECUTION 0
#define END_SESSION_STRING "STOP"
#define USER_BUILD_THOUGHT_STRING "build"

#define THOUGHT_PROMPT_STRING "Thought? "
#define BUILD_THOUGHT_PROMPT_STRING "Connection? "
#define BUILD_ON_STRING "What thought would you like to build on? "

using namespace std;

class Thought;

typedef Link<Thought*> Station; // Define what a station is (the brain)

// Pre:  userInput defined, done defined, p is the prompt
// Post: gets input from the user and checks to make sure not done
void userThought(string & userInput, bool & done, const char * prompt);

// Pre:  userInput is defined as well as stat
// Post: NULL if the thought doesn't exist yet, otherwise a pointer
Thought * findThought(string & userInput, Station & stat);

// Pre:  userInput is defined as well as stat
// Post: The thought in the station is returned, creativity used
//       if necessary
Thought * getThought(string & userInput, Station & stat);

// Pre:  userInput and stat defined
// Post: The next thought is returned (only NULL if user requested
//       build and then immediately said STOP)
Thought * think(string & userInput, Station & stat);

// Pre:  stat is defined
// Post: The user is allowed to build thoughts off of the one
//       specified, all thoughts are still kept in station though
Thought * buildThought(Station & stat);

// Pre:  stat is defined
// Post: All of the thoughts in stat are printed to the terminal
void print(Station & stat);

#endif
