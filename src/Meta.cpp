#include <string>
#include "Meta.hpp"

using namespace std;

metaInfo::metaInfo(string fName_, unsigned int mem, char acc, string length, int trackNumber){
  fileName = fName_;
  memLocation = mem;
  action = acc;
  fileLength = length;
  track = trackNumber;
}

string metaInfo::getFile() const{
  return fileName;
}

/* DEPRECATED */
string metaInfo::getMem() const{
  return to_string(memLocation);
}

unsigned int metaInfo::getLogicalAddress() const {
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
