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
  
  /* Memory allocation module */
  vector<frame> vRAM;
  
public:
  /* Overloaded Constructor */
  PCB (unsigned int id, char genStatus='q'): pid(id), status(genStatus) {}
  
  /* Getters */
  unsigned int getPID() const;
  char getStatus() const;
  int getCurrentEstimate() const;

  /* Setters */
  void setStatus(char newStatus);
  void setInitialBurst(int);
  void setNewEstimate(int);
  
  /* Statistics */
  unsigned int getTotalTime() const;
  void updateTotalTime(unsigned int);
  unsigned int getFrequency() const;
};

#endif
