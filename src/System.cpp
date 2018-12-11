#include <cmath>
#include "System.hpp"
#include "Devices.hpp"
#include "Ready_Q.hpp"

using namespace std;

System::System (int p, int d, int f, double history, int burst, const vector<int>& cylinder,
                unsigned int mSize, unsigned int procSize, unsigned int pgSize) {
  //set the private variables
  history_constant = history;
  initialBurstEstimate = burst;
  
  memSize = mSize;
  maxProcessSize = procSize;
  pageSize = pgSize;
  
  //Generate the number of devices specified
  for(unsigned int i = 0; i < p; ++i) {
    printers.push_back(Printer(i));
  }

  for (unsigned int i = 0; i < d; ++i) {
    //TODO: Make a constructor for Disk with the right parameters
    hdd.push_back(Disk(i, cylinder[i]));
  }

  for(unsigned int i = 0; i < f; ++i) {
    flashd.push_back(Flash(i));
  }
  
  //Do memory management
  for (unsigned int i = 0;  i < memSize/pageSize; ++i){
    frame f;
    f.frame_id = i;
    memory.push(f);
  }
  
}

System::~System(){
  while(!ready_q.empty()){
    auto process = ready_q.top();
    ready_q.pop();
    delete process;
  }
}

void System::advance(){
  if(ready_q.empty() || currentProcess != nullptr){
    return;
  }
  currentProcess = ready_q.top();
  currentProcess->setStatus('c');
  ready_q.pop();
  return;
}

//Adds a process to the ready queue
void System::readyProcess(PCB* process, unsigned int processSize){
  process->setInitialBurst(initialBurstEstimate);
  process->setMemSize(ceil(processSize/pageSize));
  //see if it needs to be pushed to job pool
  if ( memory.size()*pageSize < process->getMemSize()){
    jobPool.push_back(process);
  }
  else {
    //allocate the frames accordingly
    for (unsigned int i = 0; i < process->getMemSize(); ++i){
      process->vRAM[i] = memory.front();
      memory.pop();
    }
    ready_q.push(process);
  }
  
  //If it is eligible to advance, it will 
  advance();
  return;
}

//Provides relevant information in the form of a vector before process is killed
vector<int> System::fareWell() const {
  vector<int> info;
  info.reserve(3);
  if (currentProcess != nullptr) {
    info[0] = currentProcess->getPID();
    info[1] = currentProcess->getTotalTime();
    info[2] = currentProcess->getTotalTime() / currentProcess->getFrequency();
  }
  return info;
}

vector<int> System::fareWell(PCB* givenProcess) const {
  vector<int> info;
  info.reserve(3);
  if (givenProcess != nullptr){
    info[0] = givenProcess->getPID();
    info[1] = givenProcess->getTotalTime();
    info[2] = givenProcess->getTotalTime() / givenProcess->getFrequency();
  }
  return info;
}

void System::terminateProcess(){
  //Kill the process in the cpu
  ++killedProcess;
  cumBurst += currentProcess->getTotalTime() / currentProcess->getFrequency();
  for (auto eachFrame: currentProcess->vRAM){
    memory.push(move(eachFrame));
  }
  currentProcess->vRAM.clear();
  delete currentProcess;
  //feed the next process
  if (ready_q.size() > 0) {
    currentProcess = ready_q.top();
    ready_q.pop();
  }
  else {
    currentProcess = nullptr;
  }
  return;
}

void System::terminateProcess(PCB* given){
  if (currentProcess == given){
    terminateProcess();
  }
  else{
    ++killedProcess;
    cumBurst += given->getTotalTime() / given->getFrequency();
    //Free memory
    for(auto eachFrame: given->vRAM){
      memory.push(move(eachFrame));
    }
    given->vRAM.clear();
    delete given;
    given = nullptr;
  }
  return;
}

PCB* System::find(unsigned int pid){
  //Fetch ready_queue
  if (currentProcess && currentProcess->getPID() == pid){
    return currentProcess;
  }
  auto readyData = ready_q.snapshot();
  for(auto eachProcess: readyData){
    if (eachProcess->getPID() == pid){
      return eachProcess;
    }
  }
  
  for (auto eachJob: jobPool){
    if (eachJob->getPID() == pid){
      return eachJob;
    }
  }
  return nullptr;
}
unsigned int System::getMemSize() const {
  return memSize;
}

unsigned int System::getMaxProcessSize() const {
  return maxProcessSize;
}

double System::getAvgBurst() const {
  return cumBurst/killedProcess;
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
void System::addPrinterQ(int device, metaInfo m_data, int& physical){
  if (currentProcess == nullptr){
    return;
  }
  physical = currentProcess->translateMemory(m_data.getLogicalAddress(), pageSize);
  printers[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
  
  //take the next process
  advance();
}

void System::addDiskQ(int device, metaInfo m_data, int& physical){
  if (currentProcess == nullptr){
    return;
  }
  physical = currentProcess->translateMemory(m_data.getLogicalAddress(), pageSize);
  hdd[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
  
  //take the next process in
  advance();
}
void System::addFlashQ(int device, metaInfo m_data, int& physical){
  if (currentProcess == nullptr){
    return;
  }
  physical = currentProcess->translateMemory(m_data.getLogicalAddress(), pageSize);
  flashd[device].intake(currentProcess, m_data);
  currentProcess = nullptr;
  
  //take the next process in
  advance();
}

void System::getReady(vector<PCB*>& v){
  ReadyQ copy = ready_q;
  while (!copy.empty()){
    if(copy.top() != nullptr) v.push_back(copy.top());
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

void System::updateEstimate(int timerInfo){
  if (currentProcess){
    int previous = currentProcess->getCurrentEstimate();
    int newEstimate = (history_constant * previous) + (1 - history_constant)*timerInfo;
    currentProcess->setNewEstimate(newEstimate);
  }
}
