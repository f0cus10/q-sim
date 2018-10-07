// Implementation file for Shell
#include <iostream>
#include <string>
#include <iomanip> //for setw()

#include "Shell.hxx"
#include "System.hxx"

using namespace std;

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
