//This is the overview of the System
#include <vector>
#include <queue>

#include "PCB.hxx"
#include "Devices.hxx"

using std::vector;
using std::queue;

class System {
private:
  vector<Printer> printers;
  vector<Disk> hdd;
  vector<Flash> flashd;
  queue<PCB*> ready_q;
  PCB* currentProcess = nullptr;
public:
  /* Overloaded Constructor for sys gen */
  System (int, int, int);

  // Add process to the ready queue
  void readyProcess (PCB*);

  //Terminate and de-allocate a process
  void terminateProcess();
};