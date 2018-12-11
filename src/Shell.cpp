// Implementation file for Shell
#include <iostream>
#include <string>
#include <iomanip> //for setw()
#include <utility> //for pair()
#include <cmath>

#include "PCB.hpp"
#include "Shell.hpp"
#include "System.hpp"
#include "Meta.hpp"

using namespace std;

/* Public Functions */
/********************/

Shell::Shell() {
  //Prompt the user for everything
  int p, d, f;
  cout << "How many printers? ";
  cin >> p;
  cout << "How many disks? ";
  cin >> d;
  cout << "How many flash drives? ";
  cin >> f;
  
  double history;
  int burstEstimate;
  vector<int> cylinderData;
  
  cout << "Enter the history parameter (between 0 and 1): ";
  cin >> history;
  cout << "Enter initial burst estimate (in ms): ";
  cin >> burstEstimate;
  for (unsigned int i = 0; i < d; ++i){
    int tempNumber;
    cout << "Enter number of cylinders for disk_" << i << ": ";
    cin >> tempNumber;
    cylinderData.push_back(move(tempNumber));
  }
  
  unsigned int mem, proc, pg;
  cout << "Specify total memory size: ";
  cin >> mem;
  cout << "Specify max process size: ";
  cin >> proc;
  pageVerify(pg, mem);
  
  theSystem = new System(p, d, f, history, burstEstimate, cylinderData, mem, proc, pg);
  cout << "System created" << endl;
}

Shell::~Shell() {
  delete theSystem;
}

void Shell::run() {
  cout << "> ";
  //This begins the running phase of the system and awaits keyboard input
  string u_input;
  getline(cin, u_input);
  //Check against the command array to see if the command is valid
  if (u_input.empty() || u_input == " ") {
    cout << endl;
    return;
  }
  
  if (!isValid(u_input[0])){
    cout << "Invalid Command" << endl;
    return;
  }
  //process the command by offloading control to another function
  controller(u_input);
  return;
}

/* Private Functions */
/*********************/

//This function asks the timer how long the process has remained in the CPU
void Shell::reviseEstimate(){
  //if the system is not initialized or there is no current process in the CPU, DO NOTHING
  if (theSystem == nullptr || !theSystem->presentProcess()) return;
  int timeUsed;
  cout << "Enter amount of time spent in CPU (in ms): ";
  cin >> timeUsed;
  theSystem->updateEstimate(timeUsed);
}

bool Shell::isValid(const char& input){
  int i = 0;
  while (commands[i] != '\0'){
    if(commands[i] == input){
      return true;
    }
    ++i;
  }
  return false;
}

void Shell::controller(string& user_input){
  //Do a case by case switching
  char id = '\0';
  switch (user_input[0]){
    case 'A':
      addProcess();
      return;
    case 't':
      killProcess();
      return;
    case 'p':
      addPrinterJob(user_input);
      return;
    case 'P':
      id = user_input[1];
      releaseDeviceQ('P', id);
      return;
    case 'd':
      addDiskFile(user_input);
      return;
    case 'D':
      id = user_input[1];
      releaseDeviceQ('D', id);
      return;
    case 'f':
      addFlashFile(user_input);
      return;
    case 'F':
      id = user_input[1];
      releaseDeviceQ('F', id);
      return;
    case 'S':
      snapshot();
      return;
    default:
      return;
  }
}

bool Shell::devicePoll(char type, int dev_id){
  int poll = 0;
  if (type == 'p' || type == 'P'){
    poll = theSystem->getPrinterCount();
  }
  else if (type == 'd' || type == 'D'){
    poll = theSystem->getDiskCount();
  }
  else if (type == 'f' || type == 'F'){
    poll = theSystem->getFlashCount();
  }

  if (poll < dev_id){
    return false;
  }
  return true;
}

bool Shell::verify(const string& command, int& dev_id){
  char num = command[1];
  dev_id = num-'0';

  if (!devicePoll(command[0], dev_id)) {
    cout << "Device does not exist" << endl;
    return false;
  }
  return true;
}

/*
* Add a process to the ready queue of the cpu
* Generate a PID for the process
*/
void Shell::addProcess(){
  //make a new PCB with the process
  reviseEstimate();
  PCB* newProcess = new PCB(pid_count);
  ++pid_count;
  int size;
  cout << "Enter process size: ";
  cin >> size;
  if (size > theSystem->getMaxProcessSize()) {
    cout << "Process memory size exceeds maximum memory" << endl;
    return;
  }
  theSystem->readyProcess(newProcess, size);
  return;
}

/*
* Kill (terminate) the process currently in the CPU
*/
void Shell::killProcess(){
  vector<int> stats = theSystem->fareWell();
  if (!stats.empty()){
    cout << "Terminated process PID: " << stats[0] << endl;
    cout << "Terminated process Total CPU Time: " << stats[1] << endl;
    cout << "Terminated process Avg Burst Time: " << stats[2] << endl;
  }
  theSystem->terminateProcess();
  return;
}

/*
* Add a job to the proper printer's queue by using this function
*/
void Shell::addPrinterJob(const string& command){
  int printer_id;
  if(verify(command, printer_id)){
    //Prompt for metadata
    string fileName, length;
    int mem;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter memory: ";
    cin >> hex >> mem;
    cout << "Enter file length: ";
    getline(cin, length);

    //construct a metaInfo using this info
    metaInfo meta_data = metaInfo (fileName, mem, 'w', length);
    reviseEstimate();
    int transAddress;
    theSystem->addPrinterQ(printer_id, meta_data, transAddress);
    cout << "The physical address is: 0x" << hex << transAddress;
  }
  return;
}

void Shell::addDiskFile(const string& command){
  //verification phase
  int disk_id;
  if(verify(command, disk_id)){
    int cylinder_num;
    string fileName, length;
    int mem;
    char action;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter Memory: ";
    cin >> hex >> mem;
    cout << "Action (r/w): ";
    cin >> action;
    cout << "Enter file length: ";
    getline(cin, length);
    cout << "Enter cylinder number: ";
    cin >> cylinder_num;
    //TODO: Need to add constructor to metaInfo with cylinder number
    metaInfo meta_data = metaInfo(fileName, mem, action, length, cylinder_num);
    reviseEstimate();
    int transAddress;
    theSystem->addDiskQ(disk_id, meta_data, transAddress);
    cout << "The physical address is: 0x" << hex << transAddress;
  }
}

void Shell::addFlashFile(const string& command){
  //verification phase
  int flash_id;
  if(verify(command, flash_id)){
    string fileName, length;
    int mem;
    char action;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter Memory: ";
    cin >> hex >> mem;
    cout << "Action (r/w): ";
    cin >> action;
    cout << "Enter file length: ";
    getline(cin, length);

    metaInfo meta_data = metaInfo(fileName, mem, action, length);
    reviseEstimate();
    int translatedAddress;
    theSystem->addFlashQ(flash_id, meta_data, translatedAddress);
    cout << "The physical address is: 0x" << hex << translatedAddress;
  }
}

void Shell::releaseDeviceQ(char type, int dev_id){
  if(!devicePoll(type, dev_id)){
    cout << "Device does not exist" << endl;
    return;
  }
  //else,
  theSystem->reQueue(type, dev_id);
  return;
}

void Shell::snapshot(){
  //First prompt for the type of snapshot
  char type;
  cout << "Enter an option (r/p/d/f): ";
  cin >> type;
  if (type == 'r'){
    readyQStat();
  }
  else if (type == 'p' || type == 'd' || type == 'f'){
    reviseEstimate();
    devStat(type);
  }
  else{
    cout << "Invalid Option.";
    snapshot();
  }
  return;
}

void Shell::readyQStat(){
  systemTotalBurst();
  
  cout << setw(5) << "PID";
  
  //Display other stuff
  cout << setw(12) << "Total-time";
  cout << setw(16) << "Avg-burst(int)";
  cout << setw(8) << "T(next)";
  cout << setw(15) << "T(n-remaining)";
  cout << endl;

  vector<PCB*> processes;
  theSystem->getReady(processes);

  for(auto& proc: processes){
    cout << setw(5) << proc->getPID();
    cout << setw(12) << proc->getTotalTime();
    cout << setw(16) << (proc->getTotalTime()/proc->getFrequency());
    cout << setw(8) << proc->getCurrentEstimate();
    cout << setw(15) << proc->getCurrentEstimate() - proc->getTotalTime();
    cout << endl;
  }
  return;
}

void Shell::devStat(char type){
  systemTotalBurst();
  
  cout << setw(4) << "PID";
  cout << setw(12) << "Total-time";
  cout << setw(10) << "Avg-burst";
  cout << setw(10) << "Filename";
  cout << setw(10) << "PhysMem" ;
  cout << setw(5) << "R/W";
  cout << setw(8) << "Length";
  if (type == 'd') cout << setw(5) << "Cyl";
  
  cout << endl;

  vector< vector< pair<PCB*, metaInfo> > > masterStat;
  if (type == 'p'){
    theSystem->getPrinter(masterStat);
  }
  else if(type == 'd'){
    theSystem->getDisk(masterStat);
  }
  else if (type == 'f'){
    theSystem->getFlash(masterStat);
  }
  //Go over masterStat and print everything
  for (unsigned int i = 0; i < masterStat.size(); ++i){
    cout << "----" << type << i << endl;
    for (auto& eachPair: masterStat[i]) {
      //print PID
      cout << setw(4) << eachPair.first->getPID();
      cout << setw(12) << eachPair.first->getTotalTime();
      cout << setw(16) << eachPair.first->getTotalTime()/eachPair.first->getFrequency();
      cout << setw(10) << eachPair.second.getFile();
      //New memory management
      cout << setw(10) << hex << eachPair.first->translateMemory(eachPair.second.getLogicalAddress(), theSystem->getPageSize());
      cout << setw(5) << eachPair.second.getAction();
      cout << setw(8) << eachPair.second.getLength();
      if (type == 'd') cout << setw(5) << eachPair.second.getTrack();
      cout << endl;
    }
  }
}

void Shell::systemTotalBurst() {
  if (theSystem != nullptr){
    cout << "The system avg total CPU time: " << theSystem->getAvgBurst() << endl;
  }
  return;
}

void Shell::pageVerify(unsigned int& pgValue, unsigned int memSize){
  //This sanitizes the input for the page
  bool valid = false;
  while (!valid){
    cout << "Specify page size (power of 2 and factor of memory size): ";
    cin >> pgValue;
    //Sanitize it
    if (memSize % pgValue != 0){
      continue;
    }
    
    //Check for the power using the referential method for integer conversion
    int candidate = log2(pgValue);
    if (pow(2, candidate) == pgValue) valid = true;
  }
}
