#include "iostream"
#include "fstream"
#include "string.h"
#include "Link.h"
#include "station.h"

class Thought{
  // CI: Holds a word and all of it's connections
public:
  string Word; // The word that is this thought
  Station Connections; // All thoughts this is connected to

  // Default constructor
  Thought();

  // Constructor given the word
  Thought(string & word){
    Word = word;
  };

  // Pre:  Has been initialized
  // Post: Will output the word for this thought and the word for all
  //       thoughts that it is connected to
  friend ostream & operator<<(ostream & out, Thought & t){
    out << t.Word << ": ";
    for (int w=0; w<t.Connections.size(); w++){
      out << (t.Connections[0])->Word;
      if (w < t.Connections.size() - 1)
	out << ", ";	
      t.Connections.spin();
    }
    return(out);
  }
};

// Pre:  userInput defined, done defined, p is the prompt
// Post: gets input from the user and checks to make sure not done
void userThought(string & userInput, bool & done, const char * prompt){
  std::cerr << prompt;
  userInput.clear(); // Clear old input
  cin >> userInput; // Get new user input
  done = (!userInput.compare(END_SESSION_STRING));
};

// Pre:  userInput is defined as well as stat
// Post: NULL if the thought doesn't exist yet, otherwise a pointer
Thought * findThought(string & userInput, Station & stat){
  Thought * idea = NULL; // Thought not found, yet
  for (int t=0; t<stat.size(); t++){
    if (stat[0]->Word == userInput)
      Thought * idea = stat[0];  // Found
    stat.spin(); // To reduce runtime complexity from n*n to n
  }  
  return(idea);
}

// Pre:  userInput is defined as well as stat
// Post: The thought in the station is returned, creativity used
//       if necessary
Thought * getThought(string & userInput, Station & stat){
  Thought * idea = findThought(userInput, stat);
  if (idea == NULL){
    idea = new Thought(userInput);
    stat.add(idea); // Add this idea to the station
  }
  return(idea);
};

// Pre:  userInput and stat defined
// Post: The next thought is returned (only NULL if user requested
//       build and then immediately said STOP)
Thought * think(string & userInput, Station & stat){
  Thought * idea = NULL; // No specific thought
  if (!userInput.compare(USER_BUILD_THOUGHT_STRING)) // If requested build
    idea = buildThought(stat); // go to build process
  else // else: normal thought
    idea = getThought(userInput, stat);
  // creates thought if it doesn't already exist, otherwise does nothing
  return(idea);
};

// Pre:  stat is defined
// Post: The user is allowed to build thoughts off of the one
//       specified, all thoughts are still kept in station though
Thought * buildThought(Station & stat){
  string userInput;  // Holder for user input 
  bool done = false;
  userThought(userInput, done, BUILD_ON_STRING); // See what user wants
  Thought * idea = NULL;
  if (!done){
    Station & connections = (getThought(userInput, stat))->Connections;
    userInput.clear(); // Now that the right station is found, reset
    while (!done){
      if (userInput.length() > 0){
	idea = think(userInput, stat); // get thought from mind
	if (idea != NULL)
	  connections.add(idea); // Add this idea to this thought
      }
      userThought(userInput, done, BUILD_THOUGHT_PROMPT_STRING);
    }
  }
  return(idea); // The last thought is returned
}

// Pre:  stat is defined
// Post: All of the thoughts in stat are printed to the terminal
void print(Station & stat){
  std::cerr << "stat.size(): " << stat.size() << std::endl;
  for (int t=0; t<stat.size(); t++){ // For every thought in station
    std::cerr << *(stat[0]) << std::endl; // output the thought
    stat.spin(); // Spin to reduce runtime (rather than index access)
  }
}

// Trying to learn faster, we'll see.
int main(int argc, char * argv[]){
  int Status = SUCCESSFUL_EXECUTION; // Normal execution status
  Station stat; // Holder for all thoughts
  string userInput; // Holder for user ideas
  bool done = false; // Self explained
  while (!done){
    if (userInput.length() > 0) // If there was input
      think(userInput, stat); // Think about it
    userThought(userInput, done, THOUGHT_PROMPT_STRING);
  }
  print(stat); // Print out the mind
  return(Status);
}
