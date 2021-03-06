#ifndef SYSTEM_HXX
#define SYSTEM_HXX

//This is the overview of the System
#include <vector>
#include <queue>

#include "PCB.hpp"
#include "Devices.hpp"

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
  void advance();
public:
  /* Overloaded Constructor for sys gen */
  System (int, int, int);
  ~System();
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

  //Get contents of queues
  void getReady(vector<PCB*>&);
  void getPrinter(vector<vector<pair <PCB*, metaInfo> > >&);
  void getDisk(vector<vector<pair <PCB*, metaInfo> > >&);
  void getFlash(vector<vector<pair <PCB*, metaInfo> > >&);
};

#endif