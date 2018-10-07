#include <iostream>

#include <Shell.hxx>

int main () {
  Shell sh;
  sh.bootstrap();
  sh.run();
  return 0;
}