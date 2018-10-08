#include <utility>
#include <vector>

#include "Devices.hxx"
#include "PCB.hxx"
#include "Meta.hxx"

using namespace std;

Device::Device(unsigned int device_id){
  id = device_id;
}

//returns nullptr if there are no processes at the front
//else, returns the front process
PCB* Device::getProcess(){
  if (deviceQueue.size() == 0){
    return nullptr;
  }

  PCB* result = deviceQueue.front().first;
  deviceQueue.pop();
  return result;
}

//Generate a new entry for the back of the queue
void Device::intake(PCB* candidate, metaInfo meta){
  pair<PCB*, metaInfo> newMember = make_pair(candidate, move(meta));
  deviceQueue.push(newMember);
}

vector <pair<PCB*, metaInfo> > Device::stat(){
  vector<pair<PCB*, metaInfo> > result;
  auto copy = deviceQueue;
  while(!copy.empty()){
    result.push_back(copy.front());
    copy.pop();
  }
  return result;
}