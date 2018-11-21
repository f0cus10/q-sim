#include "PCB.hpp"

unsigned int PCB::getPID(){
  return pid;
}

char PCB::getStatus(){
  return status;
}

int PCB::getCurrentEstimate(){
  return burstEstimate;
}

void PCB::setStatus(char newStatus){
  status = newStatus;
}

void PCB::setInitialBurst(int initialEstimate){
  burstEstimate = initialEstimate;
}
