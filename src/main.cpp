#include <iostream>
#include <fstream>
#include <sstream>
#include "System.h"

using namespace std ;
using namespace Constants ;
using namespace mesmer ;

void usage();
string version();

int main(int argc,char *argv[])
{
  if(argc<2)
  {
    usage();
    return 0;
  }
  //
  //Start the error handling system
  //
  ostream* plog=NULL;
  ofstream logstream("mesmer.log");
  if(!logstream)
    cerr << "Could not open mesmer.log for writing. Continuing without it." << endl;
  else
    plog = &logstream;

  //Wite all messages to mesmer.log, if it was opened.
  meErrorLog.SetLogStream(plog);

  ofstream osout("mesmer.test");
  if(!osout)
    cerr << "Could not open mesmer.out for writing. Continuing without it." << endl;

  //Allow writing of messages to cerr, cwarn and cinfo. Send ctest to file mesmer.test
  //Original streams restored when this goes out of context
  OStreamRedirector osr(&meErrorLog, &osout);

  //-------------------------------
  // process command line arguments
  string infilename, outfilename;
  bool nocalc=false, notimestamp=false, usecout=false;;

  for(int iarg=1; iarg<argc;++iarg)
  {
    const char* p = argv[iarg];
    if(*p=='-')
    {
      switch(*++p)
      {
      case 'w': //error level for reporting
        if(!++p) //if no digit after -w use next arg
          p=argv[++iarg];
        meErrorLog.SetOutputLevel((obMessageLevel)(*p-'0'));
        break;
      case 'o': //output filename
        if(!++p) //if no digit after -w use next arg if its not an option
          if(++iarg<argc && *argv[iarg]!='-')
            p = argv[iarg];
          else //-o option has no filename
          {
            --iarg;
            usecout = true;
            break;
          }
        outfilename = p;
        break;
      case 'p': //just parse the input file - no calculation
        nocalc=true;
        break;
      case 'n':
        notimestamp=true;
        break;
      case '?':
        usage();
        return 0;
      case 'V':
        cout << version;
        return 0;
      }
    }
    else
      infilename = p;
  }

  cinfo << version() << endl;;
  //
  // Instantiate the System collection. This holds all information
  // about reaction systems and all molecular data.
  //
  System _sys ;

  TimeCount events; unsigned int timeElapsed;

  //This is where the type of IO is decided.
  //Opens the data file and checks that its root element is me:mesmer.
  PersistPtr ppIOPtr = XMLPersist::XmlLoad(infilename, "me:mesmer");
  
  //------------
  // Parse input file

  {

    string thisEvent;
    if(infilename.empty())
      thisEvent = "Parsing xml from stdin...";
    else
       thisEvent = "Parsing input xml file... ";
    cerr << thisEvent << endl; //usually output
    cinfo << infilename << " at " << events.setTimeStamp(thisEvent) << endl;
  }

  if(!ppIOPtr || !_sys.parse(ppIOPtr))
  {
    cerr << "System parse failed." << endl;
    return -2;
  }
  
  meErrorLog.SetContext("");
  //------------------
  // Begin calculation
  {
    string thisEvent = "Calculate EGME";
    cinfo << infilename << " successfully parsed. " << thisEvent 
          << " at " << events.setTimeStamp(thisEvent) << endl;
  }

  if(nocalc)
    return 0;
  cerr << "Now calculating..." << endl;
  _sys.calculate() ;

  meErrorLog.SetContext(__FUNCTION__);
  //--------------------------------
  // Save XML document to a new file
  string thisEvent = "Save XML document to a new file";
  string saveTimeStamp = '.' + events.setTimeStamp(thisEvent, timeElapsed);
  cinfo << thisEvent << " at " << saveTimeStamp  << " -- Time elapsed: " << timeElapsed << " seconds.\n";


  if(!usecout && outfilename.empty() && !infilename.empty())
  {
    //construct outfilename from infilename by adding or replacing a timestamp
    outfilename = infilename;
    string oldTimeStamp;
    for(;;) // remove extensions and timestamps
    {
      string::size_type pos = outfilename.rfind('.');
      //Break if no more dots or if part of current or parent directory aliases
      if(pos==string::npos || outfilename[pos+1]=='/' || outfilename[pos+1]=='\\')
        break;
      //Save last timestamp (that of the input file)
      if(oldTimeStamp.empty() && !outfilename.compare(pos, 3, ".20"))
        oldTimeStamp = outfilename.substr(pos, saveTimeStamp.size());
      outfilename.erase(pos);
    }
    if(!notimestamp)
      outfilename += oldTimeStamp + saveTimeStamp;
    outfilename += ".xml";
  }

  if(!ppIOPtr->XmlSaveFile(outfilename))
    cerr << "There was an error when writing " << outfilename;
  else
  {
    meErrorLog.SetContext(""); //so no ***Error prefix
    cerr << "System saved to " + outfilename;
  }
  return 0 ;
}

void usage()
{
  cout << "Usage:\n  mesmer infilename [options]\n"
          "If there is no infilename, stdin is used.\n"
          "Options:\n"
          " -o<outfilename>\n"
          "     If -o has no outfilename, stdout is used.\n"
          "     If there is no -o option, the output file name is constructed\n"
          "     from the input file name by adding or replacing a timstamp.\n"
          " -n  No timestamp in output file name.\n"
          " -p  Parse the input file only - no calculation.\n"
          " -w# Display only warning messages that are at least as severe as:\n"
          "       0 No messages\n"
          "       1 Errors\n"
          "       2 Warnings\n"
          "       3 Information\n"
          "       4 Audit messages\n"
          " -?  Display this help text\n"
          " -V  Output Mesmer version.\n\n"
          "For example:\n"
          "  mesmer HSO2.xml     will read HSO2.xml and write the output to\n"
          "                      something like HSO2.20071031_134701.xml\n"
          "                      Using this as an iput file in the same way will produce\n"
          "                      something like HSO2.20071031_134701.20071212_200423.xml\n"
          "  mesmer HSO2.xml -n  will read HSO2.xml and write the output back to it\n"
          "  mesmer -o -w0       will silently read from cin and write to cout\n"
       << endl;
}
string version()
{
  stringstream ss;
  ss << "Mesmer " << "v0.1" << " compiled: -- "  << __DATE__ << " -- " << __TIME__ << endl;
  return ss.str();
}

/*
Output streams in Mesmer:
cout   to console as normal
clog   to console as normal
ctest  to mesmer.test

cerr  | all to mesmer.log and also, depending
cwarn | on the warning severity level, to the console
cinfo |

Output to mesmer.test and mesmer.log will be overwrite anything from
previous runs.

*/
