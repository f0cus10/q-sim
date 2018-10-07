#include "System.hxx"
#include "Devices.hxx"

System::System(int p, int d, int f) {
  //Generate the number of devices specified
  for(unsigned int i = 0; i < p; ++p) {
    printers.push_back(Printer(i));
  }

  for (unsigned int i = 0; i < d; ++d) {
    hdd.push_back(Disk(i));
  }

  for(unsigned int i = 0; i < f; ++f) {
    flashd.push_back(Flash(i));
  }
}

void System::readyProcess(PCB* process){
  ready_q.push(process);
}

void System::terminateProcess(){
  //Kill the process in the cpu
  delete currentProcess;
  //feed the next process
  if (ready_q.size() > 0) {
    currentProcess = ready_q.front();
    ready_q.pop();
  }
  else {
    currentProcess = nullptr;
  }
  return;
}