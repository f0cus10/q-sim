#ifndef SYSTEM_HXX
#define SYSTEM_HXX

//This is the overview of the System
#include <vector>
#include <queue>

#include "frame.hpp"
#include "PCB.hpp"
#include "Devices.hpp"
#include "Ready_Q.hpp"
#include "Disk.hpp"

using std::vector;
using std::queue;

class System {
private:
  /* CPU related stats */
  double initialBurstEstimate;
  double history_constant;
  
  int killedProcess = 0;
  int cumBurst = 0;
  
  /* Memory related stats */
  unsigned int memSize;
  unsigned int maxProcessSize;
  unsigned int pageSize;
  
  vector<Printer> printers;
  vector<Disk> hdd;
  vector<Flash> flashd;
  ReadyQ ready_q;
  vector<PCB*> jobPool; //Processes waiting for memory will wait here
  queue<frame> memory; //Amount of frames available
  PCB* currentProcess = nullptr;
  void advance();
public:
  /* Overloaded Constructor for sys gen */
  // Why the hell is this so long ?!?!?!?!?! Refactor it into a vector?
  System (int, int, int, double, int, const vector<int>&, unsigned int, unsigned int, unsigned int);
  ~System();
  // Add process to the ready queue
  void readyProcess (PCB*, unsigned int);
  
  //Returns true if there is a process in the system
  bool presentProcess(){ return currentProcess != nullptr; }
  
  PCB* find(unsigned int);
  
  //Gather info before termination
  vector<int> fareWell() const;
  vector<int> fareWell(PCB*) const;
  //Terminate and de-allocate a process
  void terminateProcess();
  void terminateProcess(PCB*);
  
  /* Important Getters */
  unsigned int getMemSize() const;
  unsigned int getMaxProcessSize() const;
  unsigned int getPageSize() const {return pageSize; }
  double getAvgBurst() const;

  //Get device counts for the system
  unsigned int getPrinterCount();
  unsigned int getDiskCount();
  unsigned int getFlashCount();
  

  //Issue system calls to devices from CPU process
  void addPrinterQ(int, metaInfo, int&);
  void addDiskQ(int, metaInfo, int&);
  void addFlashQ(int, metaInfo, int&);

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
