#include "PCB.hpp"

unsigned int PCB::getPID() const {
  return pid;
}

char PCB::getStatus() const {
  return status;
}

int PCB::getCurrentEstimate() const{
  return burstEstimate;
}

void PCB::setStatus(char newStatus){
  status = newStatus;
}

void PCB::setInitialBurst(int initialEstimate){
  burstEstimate = initialEstimate;
}
