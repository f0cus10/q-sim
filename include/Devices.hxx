#ifndef DEVICES_HXX
#define DEVICES_HXX

#include <queue>
#include <utility>

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
  Printer(unsigned int printer_id): Device(printer_id) {}
  void intake(PCB*);
};

class Flash: public Device {
public:
  Flash(unsigned int flash_id): Device(flash_id) {}
  void intake(PCB*);
};

class Disk: public Device {
public:
  Disk(unsigned int disk_id): Device(disk_id) {}
  void intake(PCB*);
};

#endif