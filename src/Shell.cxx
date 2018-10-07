// Implementation file for Shell
#include <iostream>
#include <string>
#include <iomanip> //for setw()

#include "Shell.hxx"
#include "System.hxx"

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

/* Private Functions */
/*********************/
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

/*
* Add a process to the ready queue of the cpu
* Generate a PID for the process
*/
void Shell::addProcess(){
  //TODO
  return;
}

/*
* Kill (terminate) the process currently in the CPU
*/
void Shell::killProcess(){
  //TODO
  return;
}