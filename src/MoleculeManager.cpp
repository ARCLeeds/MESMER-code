//-------------------------------------------------------------------------------------------
//
// MoleculeManager.cpp
//
// Author: Struan Robertson
// Date:   11/Feb/2003
//
// This file contains the implementation of the MoleculeManager class.
//
//-------------------------------------------------------------------------------------------

#include <iostream>
#include "MoleculeManager.h"

using namespace std ;
namespace mesmer
{
//
// Add a new molecule to the list.
//
Molecule* MoleculeManager::addmol(string& molName, string& molType, PersistPtr ppMolList, const MesmerEnv& Env) {

  Molecule *pmolecule;
  PersistPtr ppmol = ppMolList->XmlMoveTo("molecule");
  while (ppmol){
    string id = ppmol->XmlReadValue("id");
    if (id == molName) break; // found the molecule
    ppmol = ppmol->XmlMoveTo("molecule");
  }

  //check if the molecule exists in m_molmap
  constMolIter it = m_molmap.find(molName) ;
  if (it != m_molmap.end()) { // found a molecule with the same name --> should check its type as well later.
    return it->second;
  }
  else{
    //-------------
    // Create a new Molecule of the required type.
    if(molType=="modelled")
      pmolecule = static_cast<Molecule*>(new CollidingMolecule(Env));
    else if(molType=="reactant")
      pmolecule = static_cast<Molecule*>(new CollidingMolecule(Env));
    else if(molType=="excessReactant")
      pmolecule = static_cast<Molecule*>(new ModelledMolecule(Env));
    else if(molType=="transitionState")
      pmolecule = static_cast<Molecule*>(new TransitionState(Env));
    else if(molType=="bathGas")
      pmolecule = static_cast<Molecule*>(new BathGasMolecule(Env));
    else
      pmolecule = static_cast<Molecule*>(new Molecule(Env));

    //-------------
    // Initialize Molecule from input stream.
    // Each molecule type has its own set of mandatory parameters
    if(!pmolecule->InitializeMolecule(ppmol) || pmolecule->getName().empty()){
      stringstream errorMsg;
      errorMsg << "Failed in initializing the molecule. molType = " << molType;
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      delete pmolecule; return NULL;
    } /*for the case of a SuperMolecule, if the element of source exists, the name has also to be specified.*/

    //-------------
    // Add molecule to map.
    m_molmap[molName] = pmolecule ;
  }

//    {stringstream errorMsg;
//    errorMsg << "Molecule " << molName << ", size of name = " << molName.size() << ", molecular type = " << molType;
//    obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);}


  //check if there is a SuperMolecule (must at least have one)
  if (molType == "reactant"){
    stringstream superName; superName << "source_" << sourceNumber;
    ++sourceNumber;
    PersistPtr ppSuper = ppMolList->XmlWriteElement("molecule");
    ppSuper->XmlWriteAttribute("id", superName.str());
    ppSuper->XmlWriteAttribute("me:type", "source");
    Molecule *pmolecule = static_cast<Molecule*>(new SuperMolecule(Env));
    pmolecule->InitializeMolecule(ppSuper);
    m_molmap[superName.str()] = pmolecule;
  }
  return pmolecule;
}

////
//// Add a new molecule to the list.
////
//SuperMolecule* MoleculeManager::addSuperMol(PersistPtr value) {
//  string myName = "source";
//  SuperMolecule *pmolecule = new SuperMolecule();
//  pmolecule->InitializeMolecule(value);
//  m_molmap[myName] = pmolecule;
//  return pmolecule;
//}

//
// Find a molecule in the list.
//
Molecule *MoleculeManager::find(const std::string& name) const {

  constMolIter it ;

  it = m_molmap.find(name) ;

  if (it == m_molmap.end()) {
    stringstream errorMsg;
    errorMsg << name << " is not a known Molecule.";
    obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);

    return NULL;
  }

  return it->second ;
}

}//namespace
