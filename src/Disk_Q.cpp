//
//  Disk_Q.cpp
//  OS-Scheduling
//
//  Created by Iftikhar Khan on 11/24/18.
//  Copyright © 2018 Iftikhar Khan. All rights reserved.
//

#include "Disk_Q.hpp"

bool DiskQ::ascending_empty() const {
  return ascending.empty();
}

bool DiskQ::descending_empty() const {
  return descending.empty();
}

unsigned int DiskQ::size(){
  return ascending.size() + descending.size();
}

disk_process DiskQ::ascending_top() const {
  return ascending.top();
}

disk_process DiskQ::descending_top() const {
  return descending.top();
}

void DiskQ::push_ascending(disk_process process){
  ascending.push(move(process));
}

void DiskQ::push_descending(disk_process process){
  descending.push(move(process));
}
void DiskQ::pop_ascending(){
  ascending.pop();
}

void DiskQ::pop_descending(){
  descending.pop();
}

vector<disk_process> DiskQ::iterable() {
  //Note: this algo is very in-efficient
  //Make a copy of the queues
  auto first = ascending;
  auto second = descending;
  //Iterate through them
  vector<disk_process> result;
  while (!first.empty()){
    result.push_back(move(first.top()));
    first.pop();
  }
  while (!second.empty()){
    result.push_back(move(second.top()));
    second.pop();
  }
  return result;
}
