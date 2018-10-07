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
