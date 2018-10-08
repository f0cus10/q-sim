#include "System.hxx"
#include "Devices.hxx"

using namespace std;

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
  if (currentProcess == nullptr){
    currentProcess = ready_q.front();
    ready_q.pop();
  }
  return;
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

//Device counters
unsigned int System::getPrinterCount(){
  return printers.size();
}
unsigned int System::getDiskCount(){
  return hdd.size();
}
unsigned int System::getFlashCount(){
  return flashd.size();
}

//System call issue
void System::addPrinterQ(int device, metaInfo m_data){
  printers[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
}

void System::addDiskQ(int device, metaInfo m_data){
  hdd[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
}
void System::addFlashQ(int device, metaInfo m_data){
  flashd[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
}

void System::getReady(vector<PCB*>& v){
  queue<PCB*> copy = ready_q;
  while (!copy.empty()){
    v.push_back(copy.front());
    copy.pop();
  }
  return;
}

void System::getPrinter(vector<vector<pair <PCB*, metaInfo> > >& mv){
  for(auto& p: printers){
    mv.push_back(p.stat());
  }
  return;
}
void System::getDisk(vector<vector<pair <PCB*, metaInfo> > >& mv){
  for(auto& d: hdd){
    mv.push_back(d.stat());
  }
  return;
}
void System::getFlash(vector<vector<pair <PCB*, metaInfo> > >& mv){
  for(auto& f: flashd){
    mv.push_back(f.stat());
  }
  return;
}

void System::reQueue(char type, int id){
  PCB* process = nullptr;
  if (type == 'p'){
    process = printers[id].getProcess();
  }
  else if(type == 'd'){
    process = hdd[id].getProcess();
  }
  else if(type = 'f'){
    process = flashd[id].getProcess();
  }
  if(process != nullptr) ready_q.push(process);
  return;
}

void System::advance(){
  if (currentProcess == nullptr){
    currentProcess = ready_q.front();
    ready_q.pop();
    currentProcess->setStatus('c');
  }
}