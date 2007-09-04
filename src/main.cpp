#include <iostream>
#include <sstream>

#ifdef _WIN32
#include <conio.h>
#endif

#include "System.h"

using namespace std;

void usage();
int main(int argc,char *argv[])
{
  //
  // Instantiate the System collection. This holds all information 
  // about reaction systems and all molecular data.
  //
  mesmer::System System ;

  string inputfilename, outputfilename;
  if(argc<2)
  {
    usage();
    return -1;
  }

  inputfilename=argv[1];
  if(argc>2)
    outputfilename = argv[2];

  //This is where the type of IO is decided.
  //Opens the data file and checks that its root element is me:mesmer.
  mesmer::PersistPtr ppIOPtr = mesmer::XMLPersist::XmlCreate(inputfilename, "me:mesmer");

  //
  // Parse input.
  // 
  if(!ppIOPtr || !System.parse(ppIOPtr))
    return -2;
  clog << inputfilename << " successfully parsed. Now calculating..." <<endl;
  // 
  // Begin calculation.
  //
  System.calculate() ;

  // Save XML doc to a new file   
  if(outputfilename.empty())
  {
    string::size_type pos = inputfilename.rfind('.');
    if(pos!=string::npos)
      outputfilename = inputfilename.replace(pos, 1, "out.");
    else
      outputfilename = inputfilename + "out";
  }
  if(!ppIOPtr->XmlSaveFile(outputfilename))
  {
    stringstream errorMsg;
    errorMsg << "There was an error when writing " << outputfilename;
    mesmer::obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), mesmer::obError);
  }

/*  #ifdef _DEBUG
  //CM keep window open
  cout << "Press any key to finish" <<endl;
  getch();
  #endif
*/

  return 0 ;
}

void usage()
{
  stringstream errorMsg;
  errorMsg  << "#----- mesmer inputfilename [outputfilename] -----#\n";
  errorMsg  << "The default outputfilename is the input name\n";
  errorMsg  << "with 'out' added before the extension.\n";
  errorMsg  << "  Any existing file will be overwritten.";
  mesmer::obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), mesmer::obInfo);
}

