#ifndef SYSTEM_HXX
#define SYSTEM_HXX

//This is the overview of the System
#include <vector>
#include <queue>

#include "PCB.hxx"
#include "Devices.hxx"

using std::vector;
using std::queue;

class System {
private:
  //TODO: Advance the next process in the ready_q to the CPU
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

  //Get device counts for the system
  unsigned int getPrinterCount();
  unsigned int getDiskCount();
  unsigned int getFlashCount();

  //Issue system calls to devices from CPU process
  void addPrinterQ(int, metaInfo);
  void addDiskQ(int, metaInfo);
  void addFlashQ(int, metaInfo);

  //Take a process out of the device queue and into the ready queue
  void reQueue(char, int);
};

#endif