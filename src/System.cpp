#include "System.hpp"
#include "Devices.hpp"

using namespace std;

System::System(int p, int d, int f) {
  //Generate the number of devices specified
  for(unsigned int i = 0; i < p; ++i) {
    printers.push_back(Printer(i));
  }

  for (unsigned int i = 0; i < d; ++i) {
    hdd.push_back(Disk(i));
  }

  for(unsigned int i = 0; i < f; ++i) {
    flashd.push_back(Flash(i));
  }
}

System::~System(){
  while(!ready_q.empty()){
    auto process = ready_q.front();
    ready_q.pop();
    delete process;
  }
}

void System::advance(){
  if(ready_q.empty() || currentProcess != nullptr){
    return;
  }
  currentProcess = ready_q.front();
  currentProcess->setStatus('c');
  ready_q.pop();
  return;
}
void System::readyProcess(PCB* process){
  ready_q.push(process);
  advance();
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
  if (currentProcess == nullptr){
    return;
  }
  printers[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
}

void System::addDiskQ(int device, metaInfo m_data){
  if (currentProcess == nullptr){
    return;
  }
  hdd[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
}
void System::addFlashQ(int device, metaInfo m_data){
  if (currentProcess == nullptr){
    return;
  }
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
  else if(type == 'f'){
    process = flashd[id].getProcess();
  }
  if(process != nullptr) ready_q.push(process);
  return;
}
