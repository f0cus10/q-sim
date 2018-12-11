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

void PCB::setMemSize(unsigned int memory){
  //The number of frames that should be allocated
  for (unsigned int i =0; i < memory; ++i){
    frame f;
    vRAM.push_back(f);
  }
  memSize = memory;
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

unsigned int PCB::getFrequency() const {
  return numProcessorBurst;
}

unsigned int PCB::getMemSize() const {
  return memSize;
}
