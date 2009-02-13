#ifndef GUARD_XMLPersist_h
#define GUARD_XMLPersist_h

#include <string>
#include "Persistence.h"
#include "../tinyxml/tinyxml.h"
#include "MesmerTools.h"

namespace mesmer
{
///Class to implement the IPersist interface for XML files using TinyXML
///To use another XML library, or another type of data file, replace this class
///and the single reference to it in main.cpp.
class XMLPersist : public IPersist
{
protected:
  TiXmlElement* pnNode;
  TiXmlDocument* pDocument; //NULL except when XMLPersist made from XmlLoad()
  static TiXmlDocument* pDefaults;

private:
  //Constructor private so that reference counting cannot be subverted.
  //XMLPersist objects are made from outside only in XmlLoad().
  //They can also be made internally, e.g. in XmlMoveTo().
  XMLPersist(TiXmlElement* pn=NULL, TiXmlDocument* pdoc=NULL)
    : pnNode(pn), pDocument(pdoc){}
public:
  ~XMLPersist();
  operator bool() const
  {
    return pnNode!=NULL;
  }

  ///Makes an instance of XMLPersist. Opens the file and reads the contents.
  ///If title is not empty gives an error message if the title or root element
  ///does not have this name.
  static PersistPtr XmlLoad(const std::string& filename, 
                            const std::string& MesmerDir="", 
                            const std::string& title="");

  ///Returns the first child element with this name, or if not found, the next sibling element with this name
  virtual PersistPtr XmlMoveTo(const std::string& name) const;
  virtual const char* XmlRead()const;
  virtual const char* XmlReadValue(const std::string& name, bool MustBeThere=true);
  virtual double XmlReadDouble(const std::string& name, bool MustBeThere=true);

  virtual const char* XmlReadProperty( const std::string& name, bool MustBeThere=true);
  virtual double XMLPersist::XmlReadPropertyDouble(const std::string& name, bool MustBeThere);
  virtual const char* XmlReadPropertyAttribute(const std::string& name, const std::string& attName, bool MustBeThere=true);
  virtual bool XmlReadBoolean( const std::string& name);


  /// Inserts into XML document a new element
  virtual PersistPtr XmlWriteElement(const std::string& name);

  /// Adds an XML attribute (or equivalent)
  virtual void XmlWriteAttribute(const std::string& name, const std::string& value);

  /// Inserts into XML document meta data information
  ///like <metadata name="dc:source" content="LibraryMols.xml" timestamp="20080705_104810" />
  virtual PersistPtr XmlWriteMetadata(const std::string& name, const std::string& content);

  /// Inserts into XML document a new element  containing a formatted number
  virtual PersistPtr XmlWriteValueElement(const std::string& name,
                                 const double datum, const int precision=-1);

  ///Insert into XML document a new element, name, and gives it a timestamp attribute and comment
  virtual PersistPtr XmlWriteMainElement( const std::string& name,
                                 const std::string& comment, bool replaceExisting=true);
 
  ///Insert into XML document a new property element, with timestamp and units attributes (if units is not empty)

  virtual PersistPtr XmlWriteProperty( const std::string& name, 
                                 const std::string& content, const std::string& units);

  ///Replace an element, or insert a copy of an element as the first child of the current element and return a pointer to the copy
      virtual PersistPtr XmlCopy(PersistPtr ppToBeCopied, PersistPtr ppToBeReplaced=NULL);


  virtual bool XmlSaveFile(const std::string& outfilename);

private:
  ///Insert a copy of the element from defaults.xml as the last child of the current element
  bool InsertDefault(const std::string& elName, const std::string& dictRefName="");
};

}//namespace mesmer
#endif //GUARD_XMLPersist_h
