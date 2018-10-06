#include <string>
using std::string;

class PCB {
private:
  unsigned int pid;
  char status; //q=ready queue, (p,d,f)=devices, c=cpu
public:
  /* Overloaded Constructor */
  PCB (unsigned int id, char genStatus='q'): pid(id), status(genStatus) {}
  /* Getters */
  unsigned int getPID() { return pid; }
  char getStatus() { return status; }

  /* Setters */
  void setStatus(char newStatus){
    status = newStatus;
  }
};