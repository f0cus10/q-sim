#ifndef META_HXX
#define META_HXX

#include <string>
using std::string;

class metaInfo {
private:
  string fileName; //string
  string memLocation; //hex
  char action; //r=read, w=write
  string fileLength; //hex
  int track;
public:
  /* Overloaded Constructor */
  metaInfo (string, string, char, string, int trackNumber = 0);

  /* Getters */
  string getFile();
  string getMem();
  char getAction();
  string getLength(); 
};

#endif