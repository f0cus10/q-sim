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

void PCB::setNewEstimate(int updatedValue){
  burstEstimate = updatedValue;
}

/* Statistics */
unsigned int PCB::getTotalTime() const {
  return totalBurst;
}

void PCB::updateTotalTime(unsigned int info){
  //Add to the current total
  ++numProcessorBurst;
  totalBurst += info;
  return;
}

unsigned int PCB::getAverageBurst() const {
  return numProcessorBurst;
}
