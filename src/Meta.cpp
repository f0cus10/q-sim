#include "Meta.hpp"

metaInfo::metaInfo(string fName_, string mem, char acc, string length, int trackNumber){
  fileName = fName_;
  memLocation = mem;
  action = acc;
  fileLength = length;
  track = trackNumber;
}

string metaInfo::getFile(){
  return fileName;
}

string metaInfo::getMem(){
  return memLocation;
}

char metaInfo::getAction(){
  return action;
}

string metaInfo::getLength(){
  return fileLength;
}