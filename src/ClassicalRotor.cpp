#include "ClassicalRotor.h"

using namespace std;
namespace mesmer
{
  //************************************************************
  //Global instance, defining its id (usually the only instance)
  ClassicalRotor theClassicalRotor("Classical rotors");
  //************************************************************
  // Reference: Theory of Unimolecular and Recombination Reactions, Robert G. Gilbert / Sean C. Smith
  //            Section 4.3 for the examples of how density of states are calculated from partition functions.

  // provide a function to define particular counts of the convoluted DOS of two molecules
  bool ClassicalRotor::countDimerCellDOS(SuperMolecule* rcts){
    //----------
    // Differetiating the rotors
    // <three types of rotors: (0) non-rotor (1) 2-D linear, (2) 3-D symmetric top, (3) 3-D asymmetric top>
    // hence there are 9 combinations for convolution:
    // 0-1, 0-2, 0-3, 1-1, 1-2, 1-3, 2-2, 2-3, 3-3
    // where the first three convolutions are trivial
    //

    ModelledMolecule*  p_mol1 = rcts->getMember1();
    ModelledMolecule*  p_mol2 = rcts->getMember2();

    if (!p_mol1 || !p_mol2){
      cerr << "Cannot get individual members of the SuperMolecule";
      return false;
    }

    vector<double> rotCs1; int rotor1Type = p_mol1->get_rotConsts(rotCs1);
    vector<double> rotCs2; int rotor2Type = p_mol2->get_rotConsts(rotCs2);
    vector<double> mol1CellEne;
    vector<double> mol2CellEne;
    rcts->m_cellDOS.clear();

    int MaximumCell = p_mol2->getEnv().MaxCell;
    vector<double> dimerCellDOS(MaximumCell, 0.0);
    p_mol1->getCellEnergies(mol1CellEne) ; // make sure the cell energies are calculated for both molecules.
    p_mol2->getCellEnergies(mol2CellEne) ;

    double I1 = 0., I2 = 0.,                                            //for 2-D linear rotors
           I1X = 0., I2X = 0., I1Y = 0., I2Y = 0., I1Z = 0., I2Z = 0.,  //for 3-D symmetric/asymmetric/spherical top rotors
           s1 = p_mol1->get_Sym(), q1 = static_cast<double>(p_mol1->getSpinMultiplicity()),
           s2 = p_mol2->get_Sym(), q2 = static_cast<double>(p_mol2->getSpinMultiplicity());

    /*All rotational constants are sorted --- the largest one at the head, smallest one at the tail*/


    //---------------------- Assign rotational constants ----------------------
    if      (rotor1Type  <  0){}                                                   // non-rotor
    else if (rotor1Type ==  0){ I1 = rotCs1[0]; }                                  // 2-D linear
    else                      { I1X = rotCs1[0]; I1Y = rotCs1[1]; I1Z = rotCs1[2];}// 3-D symmetric/asymmetric/spherical top
    if      (rotor2Type  <  0){}                                                   // non-rotor
    else if (rotor2Type ==  0){ I2 = rotCs2[0]; }                                  // 2-D linear
    else                      { I2X = rotCs2[0]; I2Y = rotCs2[1]; I2Z = rotCs2[2];}// 3-D symmetric/asymmetric/spherical top

    //------------------------------------------------------------------------------
    //Density of states from ILT of the product of partition functions of two rotors
    int rotorType = rotor1Type + rotor2Type;
    if      (rotorType == -8) return false;              // both not rotors
    double cnt = q1 * q2 / (s1 * s2);

    if      (rotorType <  0 && rotor1Type < rotor2Type){ // only p_mol2 a rotor
      rcts->m_cellDOS = p_mol2->m_cellDOS;
      rcts->m_cellEne = p_mol2->m_cellEne;
      return true;
    }
    else if (rotorType <  0 && rotor1Type > rotor2Type){ // only p_mol1 a rotor
      rcts->m_cellDOS = p_mol1->m_cellDOS;
      rcts->m_cellEne = p_mol1->m_cellEne;
      return true;
    }
    else if (rotorType == 0){                            // both 2-D linear
      cnt /= (I1 * I2);
      for (int i = 0; i < MaximumCell; ++i) dimerCellDOS[i] = cnt * mol1CellEne[i];
    }
    else if (rotorType == 2 && rotor1Type < rotor2Type){ // 2-D linear vs 3-D symmetric/asymmetric/spherical top
      cnt *= (4./(3.* I1 * sqrt(I2X * I2Y * I2Z)));
      for (int i = 0; i < MaximumCell; ++i) dimerCellDOS[i] = cnt * pow(mol1CellEne[i], 1.5);
    }
    else if (rotorType == 2 && rotor1Type > rotor2Type){ // 3-D symmetric/asymmetric/spherical top vs 2-D linear
      cnt *= (4./(3.* I2 * sqrt(I1X * I1Y * I1Z)));
      for (int i = 0; i < MaximumCell; ++i) dimerCellDOS[i] = cnt * pow(mol1CellEne[i], 1.5);
    }
    else if (rotorType == 4){                            // both 3-D symmetric/asymmetric/spherical top
      cnt *= (M_PI /(2. * sqrt(I1X * I1Y * I1Z * I2X * I2Y * I2Z)));
      for (int i = 0; i < MaximumCell; ++i) dimerCellDOS[i] = cnt * (mol1CellEne[i] * mol1CellEne[i]);
    }

    //-----------------------------------------------------------------------------------------------------
    // convolution of vibrational DOS onto rotational DOS -- loop through all frequencies of both molecules
    vector<double> vfMols; p_mol1->get_VibFreq(vfMols);

    // times the scale factor (the original vibrational frequencies vector still contains the unscaled values)
    for (vector<double>::size_type i = 0; i < vfMols.size(); ++i){
      vfMols[i] *= p_mol1->get_scaleFactor();
    }
    vector<double> vfMol2; p_mol2->get_VibFreq(vfMol2);
    for (vector<double>::size_type i = 0; i < vfMol2.size(); ++i){
      vfMols.push_back(vfMol2[i] * p_mol2->get_scaleFactor());
    }

    Beyer_Swinehart(vfMols, dimerCellDOS);

    //electronic degeneracy
    vector<double> eleExc1, eleExc2;
    p_mol1->getEleExcitation(eleExc1);
    p_mol2->getEleExcitation(eleExc2);
    if (!eleExc1.empty()){
      for (int j = 0; j < static_cast<int>(eleExc1.size()); ++j){
        int iele = static_cast<int>(eleExc1[j]);
        for (int i = (MaximumCell - 1); i >= (iele - 1); --i){
          dimerCellDOS[i] += dimerCellDOS[i - iele +1];
        }
      }
    }
    if (!eleExc2.empty()){
      for (int j = 0; j < static_cast<int>(eleExc2.size()); ++j){
        int iele = static_cast<int>(eleExc2[j]);
        for (int i = (MaximumCell - 1); i >= (iele - 1); --i){
          dimerCellDOS[i] += dimerCellDOS[i - iele + 1];
        }
      }
    }

    rcts->m_cellDOS = dimerCellDOS;
    rcts->m_cellEne = mol1CellEne;

    return true;
  }

  // provide a function to define particular counts of the convoluted DOS of two molecules
  bool ClassicalRotor::countCellDOS(ModelledMolecule* mol)
  {
    vector<double> VibFreq; mol->get_VibFreq(VibFreq);

    // times the scale factor
    for (vector<double>::size_type i = 0; i < VibFreq.size(); ++i){
      VibFreq[i] *= mol->get_scaleFactor();
    }

    const int MaximumCell = mol->getEnv().MaxCell;
    mol->m_cellDOS.clear(); mol->m_cellEne.clear(); //make sure there is no residue left
    //
    // Initialize density of states array using calculated rotational
    // density of state.
    //

    //From inverse Laplace transform of rotors
    vector<double> rotConst; int rotorType = mol->get_rotConsts(rotConst);
    double sym = mol->get_Sym();
    double qele = mol->getSpinMultiplicity();
    double cnt = 0.;

    for (int i = 0 ; i < MaximumCell ; ++i ) {
      mol->m_cellEne.push_back(static_cast<double>(i) + 0.5);
    }

    switch (rotorType){
      case 2: //3-D symmetric/asymmetric/spherical top
        cnt = qele * sqrt(4./(rotConst[0] * rotConst[1] * rotConst[2]))/sym ;
        for (int i = 0 ; i < MaximumCell ; ++i ) 
          mol->m_cellDOS.push_back(cnt*sqrt(mol->m_cellEne[i]));
        break;
      case 0: //2-D linear
        cnt = qele / (rotConst[0] * sym);
        for (int i = 0 ; i < MaximumCell ; ++i ) 
          mol->m_cellDOS.push_back(cnt);
        break;
      default:
        cnt = 0.;
        for (int i = 0 ; i < MaximumCell ; ++i ) 
          mol->m_cellDOS.push_back(cnt);
      }

    // Implementation of the Beyer-Swinehart algorithm.
    Beyer_Swinehart(VibFreq, mol->m_cellDOS);

    //electronic degeneracy
    vector<double> eleExc;
    mol->getEleExcitation(eleExc);
    if (!eleExc.empty()){
      for (int j = 0; j < static_cast<int>(eleExc.size()); ++j){
        int iele = static_cast<int>(eleExc[j]);
        for (int i = (MaximumCell - 1); i >= (iele - 1); --i){
          mol->m_cellDOS[i] += mol->m_cellDOS[i - iele + 1];
        }
      }
    }

    return true;
  }

}//namespace
