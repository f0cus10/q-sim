#ifndef PCB_HXX
#define PCB_HXX

#include <string>
#include <vector>
#include "frame.hpp"

using namespace std;

class PCB {
private:
  unsigned int pid;
  char status; //q=ready queue, (p,d,f)=devices, c=cpu
  int burstEstimate;
  unsigned int totalBurst = 0; //This will track the entire time spent in the CPU
  unsigned int numProcessorBurst = 0;
  unsigned int memSize;
  
public:
  /* Memory allocation module */
  vector<frame> vRAM;
  /* Overloaded Constructor */
  PCB (unsigned int id, char genStatus='q'): pid(id), status(genStatus) {}
  
  /* Memory translation */
  unsigned int translateMemory(unsigned int, unsigned int);
  
  /* Getters */
  unsigned int getPID() const;
  char getStatus() const;
  int getCurrentEstimate() const;
  unsigned int getMemSize() const;

  /* Setters */
  void setStatus(char newStatus);
  void setInitialBurst(int);
  void setNewEstimate(int);
  void setMemSize(unsigned int);
  
  /* Statistics */
  unsigned int getTotalTime() const;
  void updateTotalTime(unsigned int);
  unsigned int getFrequency() const;
};

#endif
