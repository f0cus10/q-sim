#include <iostream>

#include "Shell.hpp"

int main () {
  Shell sh;
  while (sh.status){
    sh.run();
  }
  return 0;
}