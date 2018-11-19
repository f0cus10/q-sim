#include "PCB.hpp"

unsigned int PCB::getPID(){
  return pid;
}

char PCB::getStatus(){
  return status;
}

void PCB::setStatus(char newStatus){
  status = newStatus;
}
