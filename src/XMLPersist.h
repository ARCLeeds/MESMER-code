#ifndef GUARD_XMLPersist_h
#define GUARD_XMLPersist_h

#include "oberror.h"
#include "Persistence.h"
#include "TimeCounter.h"
#include "../tinyxml/tinyxml.h"

namespace mesmer
{
class XMLPersist : public IPersist
{
protected:
  TiXmlElement* pnNode;
  TiXmlDocument* pDocument; //NULL except when XMLPersist made from XmlCreate()

private:
  //Constructor private so that reference counting cannot be subverted.
  //XMLPersist objects are made from outside only in XmlCreate().
  //They can also be made internally, e.g. in XmlMoveTo().
  XMLPersist(TiXmlElement* pn=NULL, TiXmlDocument* pdoc=NULL) : pnNode(pn), pDocument(pdoc){}
public:
  ~XMLPersist();
  operator bool() const
  {
    return pnNode!=NULL;
  }

  ///Makes an instance of XMLPersist. Opens the file and reads the contents.
  ///If title is not empty gives an error message if the title or root element
  ///does not have this name.
  static PersistPtr XmlCreate(const std::string& filename, const std::string& title="");


  ///Returns the first child element with this name, or if not found, the next sibling element with this name
  virtual PersistPtr XmlMoveTo(const std::string& name) const;
  virtual const char* XmlRead()const;
  virtual const char* XmlReadValue(const std::string& name, bool MustBeThere=true) const;
  virtual const char* XmlReadProperty( const std::string& name, bool MustBeThere=true) const;
  virtual bool XmlReadBoolean( const std::string& name)const;


  /// Inserts into XML document a new element
  virtual PersistPtr XmlWriteElement(const std::string& name);

  /// Adds an XML attribute (or equivalent)
  virtual void XmlWriteAttribute(const std::string& name, const std::string& value);

  /// Inserts into XML document a new element  containing a formatted number
  virtual void XmlWriteValueElement(const std::string& name,
                                 const double datum, const int precision=-1);

  ///Insert into XML document a new element, name, and gives it a timestamp attribute and comment
  virtual PersistPtr XmlWriteMainElement( const std::string& name,
                                  const std::string& comment, bool replaceExisting=true);

  virtual bool XmlSaveFile(const std::string& outfilename);

};

}//namespace mesmer
#endif //GUARD_XMLPersist_h
