#ifndef META_HXX
#define META_HXX

#include <string>
using std::string;

class metaInfo {
private:
  string fileName; //string
  unsigned int memLocation; //logical memory address
  char action; //r=read, w=write
  string fileLength; //hex
  int track;
public:
  /* Overloaded Constructor */
  metaInfo (string, unsigned int, char, string, int trackNumber = 0);

  /* Getters */
  string getFile() const;
  string getMem() const;
  unsigned int getLogicalAddress() const;
  char getAction() const;
  string getLength() const;
  int getTrack() const;
};

#endif
