#include "Meta.hpp"

metaInfo::metaInfo(string fName_, string mem, char acc, string length){
  fileName = fName_;
  memLocation = mem;
  action = acc;
  fileLength = length;
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