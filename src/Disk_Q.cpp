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

