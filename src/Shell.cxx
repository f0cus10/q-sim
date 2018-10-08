// Implementation file for Shell
#include <iostream>
#include <string>
#include <iomanip> //for setw()

#include "PCB.hxx"
#include "Shell.hxx"
#include "System.hxx"
#include "Meta.hxx"

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
  
  theSystem = new System(p, d, f);
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
      releasePrinterJob(user_input);
      return;
    case 'd':
      addDiskFile(user_input);
      return;
    case 'D':
      releaseDiskFile(user_input);
      return;
    case 'f':
      addFlashFile(user_input);
      return;
    case 'F':
      releaseFlashFile(user_input);
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
  if (type == 'p'){
    poll = theSystem->getPrinterCount();
  }
  else if (type == 'd'){
    poll = theSystem->getDiskCount();
  }
  else if (type == 'f'){
    poll = theSystem->getFlashCount();
  }

  if (poll < dev_id){
    return false;
  }
  return true;
}

/*
* Add a process to the ready queue of the cpu
* Generate a PID for the process
*/
void Shell::addProcess(){
  //TODO
  //make a new PCB with the process
  PCB* newProcess = new PCB(pid_count);
  theSystem->readyProcess(newProcess);
  ++pid_count;
  return;
}

/*
* Kill (terminate) the process currently in the CPU
*/
void Shell::killProcess(){
  //TODO
  theSystem->terminateProcess();
  return;
}

/*
* Add a job to the proper printer's queue by using this function
*/
void Shell::addPrinterJob(const string& command){
  //First, verify if the printer even exists
  char num = command[1];
  int devCount = num-'0';
  if (!devicePoll(command[0], devCount){
    cout << "Device does not exist" << endl;
    return;
  }
  //Construct a filename
  string fileName, mem, length;
  cout << "Enter filename: ";
  getline(cin, fileName);
  cout << "Enter memory: ";
  getline(cin, mem);
  cout << "Enter file length: ";
  getline(cin, length);

  //construct a metaInfo using this info
  metaInfo meta_data = metaInfo (fileName, mem, 'w', length);
  theSystem->addPrinterQ(devCount, meta_data);
  return;
}