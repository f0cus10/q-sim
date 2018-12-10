#include <queue>

#include "Ready_Q.hpp"

bool ReadyQ::empty(){
  return custom_queue.empty();
}

unsigned int ReadyQ::size(){
  return custom_queue.size();
}

PCB* ReadyQ::top() const{
  return custom_queue.top();
}

void ReadyQ::push(PCB* candidate){
  custom_queue.push(candidate);
}

void ReadyQ::pop(){
  custom_queue.pop();
}

//returns a list of all the processes
vector<PCB*> ReadyQ::snapshot(){
  auto copy = custom_queue;
  vector<PCB*> result;
  while (!copy.empty()){
    result.push_back(copy.top());
    copy.pop();
  }
  return result;
}
