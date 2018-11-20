#include <priority_queue>

#include "PCB.hpp"

using namespace std;

class SJF {
public:
  bool operator() (const PCB*& lhs, const PCB*& rhs) const {
    //TODO: calculate algorithm
  }
}
//Abstracted data structure for handling priority queues in the CPU
class ReadyQ {
public:
  bool empty();
  unsigned int size();
  PCB* top();
  void push(PCB*);
  void pop();
private:
  priority_queue <PCB*, vector<PCB*>, SJF> custom_queue;
}
