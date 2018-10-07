#ifndef DEVICES_HXX
#define DEVICES_HXX

#include <queue>
#include <pair>

#include "Meta.hxx"
#include "PCB.hxx"

using std::queue;
using std::pair;

class Device {
private:
  unsigned int id;
  queue< pair<PCB*, metaInfo> > deviceQueue;
protected:
  virtual void addProcess(pair<PCB*, metaInfo>);
public:
  Device(unsigned int);
  PCB* getProcess();
};

class Printer: public Device {
public:
  void intake(PCB*);
};

class Flash: public Device {
public:
  void intake(PCB*);
};

class Disk: public Device {
public:
  void intake(PCB*);
};

#endif