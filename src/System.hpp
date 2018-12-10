#ifndef SYSTEM_HXX
#define SYSTEM_HXX

//This is the overview of the System
#include <vector>
#include <queue>

#include "PCB.hpp"
#include "Devices.hpp"
#include "Ready_Q.hpp"
#include "Disk.hpp"

using std::vector;
using std::queue;

class System {
private:
  double initialBurstEstimate;
  double history_constant;
  
  vector<Printer> printers;
  vector<Disk> hdd;
  vector<Flash> flashd;
  ReadyQ ready_q;
  PCB* currentProcess = nullptr;
  void advance();
public:
  /* Overloaded Constructor for sys gen */
  System (int, int, int, double, int, const vector<int>&);
  ~System();
  // Add process to the ready queue
  void readyProcess (PCB*);
  
  //Returns true if there is a process in the system
  bool presentProcess(){ return currentProcess != nullptr; }
  
  //Gather info before termination
  vector<int> fareWell() const;
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
  
  //Make a new estimate for the process
  void updateEstimate(int);

  //Get contents of queues
  void getReady(vector<PCB*>&);
  void getPrinter(vector<vector<pair <PCB*, metaInfo> > >&);
  void getDisk(vector<vector<pair <PCB*, metaInfo> > >&);
  void getFlash(vector<vector<pair <PCB*, metaInfo> > >&);
};

#endif
