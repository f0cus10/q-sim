#ifndef SHELL_HXX
#define SHELL_HXX

#include <string>
#include "System.hxx"

using std::string;

class Shell {
private:
  char commands[10] = {'A', 't', 'p', 'P', 'd', 'D', 'f', 'F', 'S','\0'};
  System* theSystem = nullptr;
  bool isValid(const char&);
  void controller(string&);
public:
  /* Default Constructor & Destructor */
  Shell();
  ~Shell();
  void run();
};

#endif