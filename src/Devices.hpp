#ifndef DEVICES_HXX
#define DEVICES_HXX

#include <queue>
#include <utility>
#include <vector>

#include "Meta.hpp"
#include "PCB.hpp"

using namespace std;

class Device {
private:
  unsigned int id;
  queue< pair<PCB*, metaInfo> > deviceQueue;
  void sanitize();
protected:
  void addProcess(pair<PCB*, metaInfo>);
public:
  Device(unsigned int);
  PCB* getProcess();
  void intake(PCB*, metaInfo);
  vector <pair<PCB*, metaInfo> > stat();
};

class Printer: public Device {
public:
  Printer(unsigned int printer_id): Device(printer_id) {}
};

class Flash: public Device {
public:
  Flash(unsigned int flash_id): Device(flash_id) {}
};

#endif
