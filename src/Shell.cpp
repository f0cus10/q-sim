// Implementation file for Shell
#include <iostream>
#include <string>
#include <iomanip> //for setw()
#include <utility> //for pair()

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
  cout << "How many printers?";
  cin >> p;
  cout << "How many disks?";
  cin >> d;
  cout << "How many flash drives?";
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
  
  //TODO: Modify the constructor to take in the new parameters
  theSystem = new System(p, d, f, history, burstEstimate, cylinderData);
  cout << "System created" << endl;
}

Shell::~Shell() {
  delete theSystem;
}

void Shell::run() {
  //This begins the running phase of the system and awaits keyboard input
  cout << "> ";
  string u_input;
  getline(cin, u_input);
  //Check against the command array to see if the command is valid
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
      cout << "Invalid Command" << endl;
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
  theSystem->readyProcess(newProcess);
  ++pid_count;
  return;
}

/*
* Kill (terminate) the process currently in the CPU
*/
void Shell::killProcess(){
  //TODO: update the system's management
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
    string fileName, mem, length;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter memory: ";
    getline(cin, mem);
    cout << "Enter file length: ";
    getline(cin, length);

    //construct a metaInfo using this info
    metaInfo meta_data = metaInfo (fileName, mem, 'w', length);
    reviseEstimate();
    theSystem->addPrinterQ(printer_id, meta_data);
  }
  return;
}

void Shell::addDiskFile(const string& command){
  //verification phase
  int disk_id;
  if(verify(command, disk_id)){
    int cylinder_num;
    string fileName, mem, length;
    char action;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter Memory: ";
    getline(cin, mem);
    cout << "Action (r/w): ";
    cin >> action;
    cout << "Enter file length: ";
    getline(cin, length);
    cout << "Enter cylinder number: ";
    cin >> cylinder_num;
    //TODO: Need to add constructor to metaInfo with cylinder number
    metaInfo meta_data = metaInfo(fileName, mem, action, length, cylinder_num);
    reviseEstimate();
    theSystem->addDiskQ(disk_id, meta_data);
  }
}

void Shell::addFlashFile(const string& command){
  //verification phase
  int flash_id;
  if(verify(command, flash_id)){
    string fileName, mem, length;
    char action;
    cout << "Enter filename: ";
    getline(cin, fileName);
    cout << "Enter Memory: ";
    getline(cin, mem);
    cout << "Action (r/w): ";
    cin >> action;
    cout << "Enter file length: ";
    getline(cin, length);

    metaInfo meta_data = metaInfo(fileName, mem, action, length);
    reviseEstimate();
    theSystem->addFlashQ(flash_id, meta_data);
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
  cout << setw(7);
  cout << "PID" << endl;

  vector<PCB*> processes;
  theSystem->getReady(processes);

  for(auto& proc: processes){
    cout << setw(7);
    cout << proc->getPID() << endl;
  }
  return;
}

void Shell::devStat(char type){
  cout << setw(4) << "PID" << setw(4) << "Filename";
  cout << setw(6) << "Memstart" << setw(4) << "R/W";
  cout << setw(4) << "File Length" << endl;

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
      cout << setw(4) << eachPair.second.getFile();
      cout << setw(6) << eachPair.second.getMem();
      cout << setw(4) << eachPair.second.getAction();
      cout << setw(4) << eachPair.second.getLength();
      cout << endl;
    }
  }
}
