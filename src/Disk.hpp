#ifndef DISK_HPP
#define DISK_HPP

#include "Devices.hpp"
#include "Disk_Q.hpp"

//Disk is an exceptional device. 
class Disk: public Device {
public:

  Disk(unsigned int disk_id, int cylinder_number): Device(disk_id), cylinder(cylinder_number) {}
  int maxCylinder() const { return cylinder; }
  void intake(PCB*, metaInfo);
  vector<disk_process> stat();
  PCB* getProcess();
private:
  int cylinder;
  int headPosition = 0;
  DiskQ real_queue;
};

#endif
