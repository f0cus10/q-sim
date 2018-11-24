#ifndef DISKQ_HPP
#define DISKQ_HPP

#include <queue>
#include <vector>
#include <utility>

#include "Meta.hpp"
#include "PCB.hpp"

using namespace std;

class SCAN {
public:
  //Overloaded operator
  bool operator() (const pair<PCB*, metaInfo>& lhs, const pair<PCB*, metaInfo>& rhs) const {
    return lhs.second.getTrack() < rhs.second.getTrack();
  }
};

class DESCAN {
  bool reverse;
public:
  bool operator() (const pair<PCB*, metaInfo>& lhs, const pair<PCB*, metaInfo>& rhs) const {
    return lhs.second.getTrack() > rhs.second.getTrack();
  }
};

typedef pair<PCB*, metaInfo> disk_process;
typedef priority_queue<disk_process, vector<disk_process>, SCAN> disk_queue;
typedef priority_queue<disk_process, vector<disk_process>, DESCAN > disk_queue_descent;


class DiskQ {
private:
  disk_queue ascending;
  disk_queue_descent descending;
public:
  bool ascending_empty() const;
  bool descending_empty() const;

  unsigned int size();

  disk_process ascending_top() const;
  disk_process descending_top() const;

  void push_ascending(disk_process);
  void push_descending(disk_process);
  void pop_ascending();
  void pop_descending();

  vector<disk_process> iterable ();
};

#endif
