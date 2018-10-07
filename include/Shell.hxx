#include <iostream>
#include <string>
#include <iomanip> //for setw()

#include "System.hxx"

using namespace std;

class Shell {
private:
  System* theSystem = nullptr;
public:
  void bootstrap();
  void run();
};