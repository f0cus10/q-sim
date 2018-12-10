#ifndef READYQ_HXX
#define READYQ_HXX

#include <queue>
#include <vector>

#include "PCB.hpp"

using namespace std;

class SJF {
public:
  bool operator() (PCB* const lhs, PCB* const rhs) const {
    return lhs->getCurrentEstimate() < rhs->getCurrentEstimate();
  }
};

//Abstracted data structure for handling priority queues in the CPU
class ReadyQ {
public:
  bool empty();
  unsigned int size();
  PCB* top() const;
  void push(PCB*);
  void pop();
  vector<PCB*> snapshot(); //O(n) algorithm
private:
  priority_queue <PCB*, vector<PCB*>, SJF> custom_queue;
};

#endif
