#ifndef DISK_Q_HPP
#define DISK_Q_HPP

#include <queue>
#include <vector>
#include <utility>

#include "Meta.hpp"
#include "PCB.hpp"

using namespace std;

class SCAN;
typedef pair<PCB*, metaInfo> disk_process;
typedef priority_queue<disk_process, vector<disk_process>, SCAN> disk_queue;

class SCAN {
private:
  bool reverse;
public:
  //Overloaded constructor
  SCAN(const bool& revparam = false){ reverse=revparam; }
  //Overloaded operator
  bool operator() (const disk_process& lhs, const disk_process& rhs) const {
    if (reverse) return lhs.second.getTrack() > rhs.second.getTrack();
    return (lhs.second.getTrack() < rhs.second.getTrack());
  }
};


class DiskQ {
private:
  disk_queue ascending;
  disk_queue descending ( SCAN(true) );
public:
  bool asceding_empty() const;
  bool descending_empty() const;

  unsigned int size();

  disk_process ascending_top() const;
  disk_process descending_top() const;

  void push_ascending(disk_process);
  void push_descending(disk_process);
  void pop_ascending();
  void pop_descending();

};

#endif