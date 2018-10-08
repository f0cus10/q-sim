#ifndef SHELL_HXX
#define SHELL_HXX

#include <string>
#include "System.hxx"

using std::string;

class Shell {
private:
  /* Controlling functions */
  void addProcess();
  void killProcess();
  void addPrinterJob(const string&);
  void addDiskFile(const string&);
  void addFlashFile(const string&);
  void releaseDeviceQ(char, int);
  void snapshot();
  /* ------------- */

  char commands[10] = {'A', 't', 'p', 'P', 'd', 'D', 'f', 'F', 'S','\0'};
  System* theSystem = nullptr;
  bool isValid(const char&);
  void controller(string&);
  bool devicePoll(char, int);
  bool verify(const string&, int&);
  unsigned int pid_count = 0;
public:
  /* Default Constructor & Destructor */
  Shell();
  ~Shell();
  void run();
};

#endif