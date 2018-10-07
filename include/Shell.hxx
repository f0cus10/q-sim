#ifndef SHELL_HXX
#define SHELL_HXX

#include "System.hxx"

class Shell {
private:
  System* theSystem = nullptr;
public:
  /* Default Constructor & Destructor */
  Shell();
  ~Shell();
  void run();
};

#endif