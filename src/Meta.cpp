#include "Meta.hpp"

metaInfo::metaInfo(string fName_, string mem, char acc, string length, int trackNumber){
  fileName = fName_;
  memLocation = mem;
  action = acc;
  fileLength = length;
  track = trackNumber;
}

string metaInfo::getFile() const{
  return fileName;
}

string metaInfo::getMem() const{
  return memLocation;
}

char metaInfo::getAction() const {
  return action;
}

string metaInfo::getLength() const {
  return fileLength;
}

int metaInfo::getTrack() const {
  return track;
}