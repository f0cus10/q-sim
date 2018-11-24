//
//  Disk.cpp
//  OS-Scheduling
//
//  Created by Iftikhar Khan on 11/24/18.
//  Copyright © 2018 Iftikhar Khan. All rights reserved.
//
#include <utility>
#include "Disk.hpp"
#include "PCB.hpp"
#include "Meta.hpp"

void Disk::intake(PCB* process, metaInfo metaData){
  disk_process candidate = make_pair(process, metaData);
  //If cylinder num is smaller, decreasing_q
  if (headPosition > metaData.getTrack()){
    real_queue.push_descending(candidate);
  }
  //if cylinder num is greater, ascending_q
  else if (headPosition < metaData.getTrack()){
    real_queue.push_ascending(candidate);
  }
}

PCB* Disk::getProcess(){
  if (readDirection){
    auto process = real_queue.ascending_top();
    real_queue.pop_ascending();
    headPosition = process.second.getTrack();
    //Check if direction needs to be changed
    if (real_queue.asceding_empty()){
      readDirection = !readDirection;
    }
    return process.first;
  }
  
  else {
    auto process = real_queue.descending_top();
    real_queue.pop_descending();
    headPosition = process.second.getTrack();
    //Check if direction needs to be changed
    if (real_queue.descending_empty()){
      readDirection = !readDirection;
    }
    return process.first;
  }
  
}
