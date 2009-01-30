// MolecularComponents.h
//
// Author: Chi-Hsiu Liang
//
// This file contains property groups of class Molecule. These groups give molecules variables and functions to perform
// tasks; from the definitions of these groups a molecule can play roles when it is required to do so.
// Classes in this file do not depend on each other and thus they can be seperated. Any of them can be added into
// a molecule (with a new() to construct an object and then pass the pointer to the molecule) when the role of the molecule
// requires the information in that group.
//-------------------------------------------------------------------------------------------

#ifndef GUARD_MolecularComponents_h
#define GUARD_MolecularComponents_h

#include <memory>
#include "MicroRate.h"
#include "DensityOfStates.h"
#include "Distribution.h"
#include "MesmerEnv.h"
#include "MesmerFlags.h"
#include "Pointer.h"

using namespace std ;
using namespace Constants ;

namespace mesmer
{

  class Molecule;

  class MolecularComponent{

  protected:
    Molecule* m_host;

    MolecularComponent():m_host(NULL){}
  };

  class gBathProperties:public MolecularComponent
  {

    //-------------------------------------------------------------------------------------------------
    // Bath gas related properties
    //-------------------------------------------------------------------------------------------------

  private:
    double         m_Sigma ;            // Lennard-Jones sigma.
    double         m_Epsilon ;          // Lennard-Jones epsilon.

    //================================================
    // CHECK FOR INPUTFILE PARAMETERS
    int m_Sigma_chk;
    int m_Epsilon_chk;
    //================================================

  public:

    //
    // Constructor, destructor and initialization
    //
    gBathProperties(Molecule* pMol);
    virtual ~gBathProperties();

    double getSigma() ;
    double getEpsilon() ;
    void   setSigma(double value);
    void   setEpsilon(double value);

  };

  class gDensityOfStates:public MolecularComponent
  {

    //-------------------------------------------------------------------------------------------------
    // Cell density of states related properties
    //-------------------------------------------------------------------------------------------------

  private:

    double m_RotCstA ;          // Moment of inertia A.
    double m_RotCstB ;          // Moment of inertia B.
    double m_RotCstC ;          // Moment of inertia C.
    double m_Sym ;              // Rotational symmetry number.

    DPoint m_ZPE ;              // Zero Point Energy. (kJ/mol)

    double m_scaleFactor ;      // scale factor for input real/imaginary vibrational frequencies
    int    m_SpinMultiplicity ; // spin multiplicity


    DensityOfStatesCalculator *m_pDensityOfStatesCalculator ;

    //================================================
    // CHECK FOR INPUTFILE PARAMETERS
    int m_RC_chk;
    int m_Sym_chk;
    int m_ZPE_chk;
    int m_scaleFactor_chk;
    int m_SpinMultiplicity_chk;
    int m_VibFreq_chk;
    std::string m_EnergyConvention;
    //================================================

    std::vector<double> m_eleExc;   // Electronic excitation(for OH, NO, NS otherwise no member).
    std::vector<double> m_VibFreq ; // Values of vibrational frequencies.

  protected:

    //------------------------
    // Cell density of states
    //------------------------
    std::vector<double> m_cellDOS ;   // Cell density of states array.


    //------------------------
    // Grain density of states
    //------------------------
    std::vector<double> m_grainEne ;  // Grain average energy array.
    std::vector<double> m_grainDOS ;  // Grain density of states array.

  public:

    //
    // Constructor, destructor and initialization
    //
    gDensityOfStates(Molecule* pMol);
    virtual ~gDensityOfStates();

    // Get cell density of states.
    void getCellDensityOfStates(std::vector<double> &cellDOS, int startingCell = 0) ;

    // Set cell  density of states.
    void setCellDensityOfStates(std::vector<double> &cellDOS) { m_cellDOS = cellDOS ; } ;

    // Get Electronic excitations
    void getEleExcitation(vector<double> &elecExci);

    // Calculate Density of states
    bool calcDensityOfStates();

    // Calculate classical energy
    double getClassicalEnergy();

    // Accessors.
    virtual double get_zpe();
    void set_zpe(const double value){ m_ZPE = value; m_ZPE_chk = 0;};
    void set_zpe(const double valueL, const double valueU, const double stepsize){
      m_ZPE.set_range(valueL, valueU, stepsize);
      m_ZPE_chk = 0;
    }
    const std::string& getEnergyConvention()const {
      return m_EnergyConvention; 
    }
    double get_Sym(void);
    int test_rotConsts(void);
    int  get_rotConsts(std::vector<double> &mmtsInt);
    virtual void get_VibFreq(std::vector<double>& vibFreq);


    virtual DensityOfStatesCalculator* get_DensityOfStatesCalculator(){
      return m_pDensityOfStatesCalculator;
    }

    virtual int getSpinMultiplicity();

    int get_cellOffset(void);

    //----------------------------------
    // Grain density of states functions
    //----------------------------------

    // Get grain density of states.
    void getGrainDensityOfStates(std::vector<double> &grainDOS, const int startGrnIdx = 0, const int ignoreCellNumber = 0) ;

    // Get grain energies.
    void getGrainEnergies(std::vector<double> &grainEne) ;

    // Get Grain canonical partition function.
    double rovibronicGrnCanPrtnFn() ;
  
  private:

    // This function checks if any of the DPoint values is different then a DOS recalculation will take place
    bool needReCalculateDOS(void){
      if (!m_ZPE.isConstant()) return true;
      return false;
    }

    // This function explicitly tell all DPoint values in this Molecule that a DOS recalculation is completed.
    void recalculateDOScompleted(void){
      m_ZPE.updateValue();
    }

    // Test the rovibrational density of states.
    virtual void testDensityOfStates() ;

    // Get scale factor for vibrational frequencies
    double get_scaleFactor();
  };

/*
Molecule energy specified in property elements with two dictRefs:
me:ZPE and me:Hf298
For example:
        <property dictRef="me:ZPE">
          <scalar convention="thermodynamic" units="kJ/mol">139.5</scalar>
        </property>
        <property dictRef="me:Hf298">
          <scalar units="kJ/mol">139.5</scalar>
        </property>

me:ZPE   - is used preferentially if it is present
         - can use any baseline, but all the molecules in the file must use the same baseline
         - the scalar can have the attribute convention="thermodynamic", in which case the
             baseline is the same as for Hf298
         - if not originally present, is calculated from me:Hf298 and inserted into the datafile
             with attributes convention="thermodynamic" and calculated=TIMESTAMP.
         - can have multiple values if the attributes lower, higher and stepsize are present.
         - can have a units attribute. The follow values are recognized:
             "kJ/mol" "kJ per mol" "kcal/mol" "kcal per mol" "wavenumber" "cm-1" "Hartree" "au"
             If the attribute is missing the default is kJ/mol.

me:Hf298 - is the Enthalpy of formation at 298K, commonly used for thermodynamic data.
             This baseline is common to all molecules so that it is possible to implement
             a library of molecules.
         - is used if me:ZPE is not present
         - can have a units attribute see above

The energy of a set of reactants and products is obtained by adding the me:ZPEs of
each of the molecules. If an arbitary baseline is used for the modelled molecules,
like C2H2 and adduct in the reaction C2H2 + OH => adduct, the ancillary molecules, like OH,
must have me:ZPE specified as zero. If a thermodynamic baseline is used for any molecule
it must be used for all, and this is checked.
*/

  class gTransitionState:public MolecularComponent
  {

    //-------------------------------------------------------------------------------------------------
    // Transition state related properties
    //-------------------------------------------------------------------------------------------------

  private:
    double m_ImFreq;            // Imaginary frequency of this barrier (For tunneling in QM calculations)
    //================================================
    // CHECK FOR INPUTFILE PARAMETERS
    int m_ImFreq_chk;
    //================================================

  public:
    //
    // Constructor, destructor and initialization
    //
    gTransitionState(Molecule* pMol);
    virtual ~gTransitionState();

    double get_ImFreq();

  };

  class gPopulation:public MolecularComponent
  {

    //-------------------------------------------------------------------------------------------------
    // Population and equilibrium fraction
    //-------------------------------------------------------------------------------------------------

  private:

    double m_initPopulation ;   // initial population of the molecule.
    double m_eqFraction ;       // equilibrium fraction of the species

  public:

    //
    // Constructor, destructor and initialization
    //
    gPopulation(Molecule* pMol);

    double getInitPopulation() const { return m_initPopulation;};
    void setInitPopulation(double value) { m_initPopulation = value;};
    double getEqFraction() const { return m_eqFraction;};
    void setEqFraction(double value){ m_eqFraction = value;};

  };

  class gWellProperties:public MolecularComponent
  {
    //-------------------------------------------------------------------------------------------------
    // Collisional redistribution related properties
    //-------------------------------------------------------------------------------------------------

  private:

    double              m_DeltaEdownExponent;  // Exponent of <Delta E down> according to the relation
    // <delta_E_down>(T) = <delta_E_down>_ref * (T / m_DeltaEdownRefTemp)^n
    // where m_DeltaEdownExponent is the exponent n
    // By default, n = 0, which means delta_E_down does not depend on temperature.
    double              m_DeltaEdownRefTemp;   // reference temperature of <Delta E down>, default 298.
    DPoint              m_DeltaEdown ;         // <Delta E down> for the exponential down model.
    double              m_collisionFrequency ; // Current value of collision frequency.
    int                 m_ncolloptrsize ;      // Size of the collision operator matrix.
    DistributionCalculator* m_pDistributionCalculator;

    //================================================
    // CHECK FOR INPUTFILE PARAMETERS
    int m_DeltaEdown_chk;
    //================================================

    double m_grainFracBeta;                    // beta used to calculate grain distribution fraction
    std::vector<double> m_grainDist ;          // Grain distribution (not normalized)
    dMatrix             *m_egme ;              // Matrix containing the energy grained collision operator.
    dMatrix             *m_egvec ;               // Eigenvectors used to diagonalize (P - I) matrix.
    std::vector<double>  m_egval;

    // Calculate collision frequency.
    double collisionFrequency(double beta, const double conc, Molecule *pBathGasMolecule) ;

    // Calculate collision operator.
    bool   collisionOperator (double beta) ;

    // Diagonalize collision operator before adding reaction terms to get eigenvectors and eigenvalues.
    void diagonalizeCollisionOperator();

    // Normalize the Collision Operator.
    void normalizeCollisionOperator();

    // Get Grain Boltzmann distribution.
    void grainDistribution(vector<double> &grainFrac, const int numberOfGrains);

    // DeltaEdown operators
    double getDeltaEdown();
    void   setDeltaEdown(const double value){ m_DeltaEdown = value; m_DeltaEdown_chk = 0;};
    void   setDeltaEdown(const double valueL, const double valueU, const double stepsize){
      m_DeltaEdown.set_range(valueL, valueU, stepsize);
      m_DeltaEdown_chk = 0;
    };
    void   setDeltaEdownRefTemp(const double value){m_DeltaEdownRefTemp = value;};
    void   setDeltaEdownExponent(const double value){m_DeltaEdownExponent = value;};
    double getDeltaEdownRefTemp (){return m_DeltaEdownRefTemp; }
    double getDeltaEdownExponent(){return m_DeltaEdownExponent;}

  public:

    //
    // Constructor, destructor and initialization
    //
    gWellProperties(Molecule* pMol);
    virtual ~gWellProperties();

    // Initialize the Collision Operator.
    bool initCollisionOperator(double beta, Molecule *pBathGasMolecule) ;

    // Calculate a reaction matrix element.
    double matrixElement(int eigveci, int eigvecj, std::vector<double> &k, int ndim) ;

    void copyCollisionOperator(qdMatrix *CollOptr, const int size, const int locate, const double RducdOmega) const ;

    void normalizedInitialDistribution(vector<double> &grainFrac, const int numberOfGrains) ;
    void normalizedGrnBoltzmannDistribution(vector<double> &grainFrac, const int numberOfGrains, const int startGrnIdx = 0, const int ignoreCellNumber = 0);

    // Accessors.
    double get_collisionFrequency() const ;
    void set_colloptrsize(int ncolloptrsize) ;
    int  get_colloptrsize() const ;

    const int get_grnZPE();
    
    const dMatrix* getEigenVectors(){ return m_egvec; }

  };

}//namespace

#endif // GUARD_MolecularComponents_h