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

class Disk: public Device {
//Disk is an exception
public:
  Disk(unsigned int disk_id, int cylinder_number): Device(disk_id), cylinder(cylinder_number) {}
  int maxCylinder() const { return cylinder; }
private:
  int cylinder;
};

#endif
