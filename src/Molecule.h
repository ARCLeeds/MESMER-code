#ifndef GUARD_Molecule_h
#define GUARD_Molecule_h

//-------------------------------------------------------------------------------------------
//
// Molecule.h
//
// Author: Struan Robertson
// Date:   5/Jan/2003
//
// This header file contains the declaration of the Molecule class.
//
//-------------------------------------------------------------------------------------------

#include <memory>
#include "MesmerEnv.h"
#include "XMLPersist.h"
#include "MesmerMath.h"
#include "formatfloat.h"
#include "DensityOfStates.h"

namespace mesmer
{
  //**************************************************
  /// Basic molecule: has name and some collision parameters.
  /// Used for bath gases and unmodelled product molecules.
  class Molecule
  {
  private:

    const MesmerEnv&     m_Env;
    int            m_flag;              // count the errors during initialization
    PersistPtr     m_ppPersist;         // Conduit for I/O
    std::string    m_Name ;             // Molecule name.
    double         m_Mass ;             // Mass.
    double         m_Sigma ;            // Lennard-Jones sigma.
    double         m_Epsilon ;          // Lennard-Jones epsilon.

    //Molecule(const Molecule&) ;
    //Molecule& operator=(const Molecule&) ;

  public:
    Molecule(const MesmerEnv& Env) ;
    virtual ~Molecule(){} ;

    // Initialize Molecule.
    virtual bool InitializeMolecule(PersistPtr pp);

    PersistPtr  getPersistentPointer()     { return m_ppPersist;};
    void setPersistentPointer(PersistPtr value){m_ppPersist = value;}
    std::string getName() const            { return m_Name ; } ;
    const MesmerEnv& getEnv() const        { return m_Env; } 

    int    getFlag()                       { return m_flag; } ;
    double getMass() const                 { return m_Mass ; } ;
    double getSigma() const                { return m_Sigma ; } ;
    double getEpsilon() const              { return m_Epsilon ; } ;

    void   setName(string name)            { m_Name = name; } ;
    void   setFlag(bool value)             { if (value) ++m_flag; } ;
    void   setMass(double value)           { m_Mass = value; } ;
    void   setSigma(double value)          { m_Sigma = value; } ;
    void   setEpsilon(double value)        { m_Epsilon = value; } ;
  };

  //**************************************************
  class BathGasMolecule : public Molecule
  {
  public:
    BathGasMolecule(const MesmerEnv& Env) : Molecule(Env){}
    virtual ~BathGasMolecule(){} ;
    // Initialize BathGasMolecule.
    virtual bool InitializeMolecule(PersistPtr pp);
  };

  //**************************************************
  ///Molecule with multiple energy states. Probably not instantiated itself
  class ModelledMolecule : public Molecule
  {
    //
    // Molecular properties.
    //
    double              m_RotCstA ;          // Moment of inertia A.
    double              m_RotCstB ;          // Moment of inertia B.
    double              m_RotCstC ;          // Moment of inertia C.
    double              m_Sym ;              // Rotational symmetry number.
    double              m_ZPE ;              // Zero Point Energy. (Kcal/Mol)
    int                 m_SpinMultiplicity ; // spin multiplicity
    int                 m_grnZpe ;           // Zero point energy expressed in grains.
    DensityOfStatesCalculator *m_pDensityOfStatesCalculator ;


  public:
    std::vector<double> m_VibFreq ;          // Values of vibrational frequencies.
    //
    // Cell and grain averages.  Note: raw array used for efficiency,
    // but need to test validity of this. SHR 5/Jan/03.
    //
    std::vector<double> m_cellEne ;          // Cell mid-point energy array.
    std::vector<double> m_cellDOS ;          // Cell density of states array.
    std::vector<double> m_grainEne ;         // Grain average energy array.
    std::vector<double> m_grainDOS ;         // Grain density of states array.

    //----------------
    ModelledMolecule(const MesmerEnv& Env);
    virtual ~ModelledMolecule();

    // Initialize ModelledMolecule.
    virtual bool InitializeMolecule(PersistPtr pp);

    // Get the density of states.
    void getCellDensityOfStates(std::vector<double> &cellDOS) ;

    // Get cell energies.
    void getCellEnergies(std::vector<double> &CellEne) ;

    // Get grain density of states.
    void grnDensityOfStates(std::vector<double> &grainDOS) ;

    // Get grain energies.
    void grnEnergies(std::vector<double> &grainEne) ;

    // Get Grain Boltzmann distribution.
    void grnBoltzDist(std::vector<double> &grainBoltzDist) ;

    // Get Grain canonical partition function.
    double grnCanPrtnFn() ;

    // Calculate Density of states
    bool calcDensityOfStates();

    // Accessors.
    double get_zpe() const { return m_ZPE ; }
    void set_zpe(double value) { m_ZPE = value; }
    double get_Sym(void){return m_Sym;}
    int test_rotConsts(void);
    int  get_rotConsts(std::vector<double> &mmtsInt);
    void set_grnZpe(int grnZpe) {m_grnZpe = grnZpe ;} ;
    int  get_grnZpe() const {return m_grnZpe ;} ;

    void get_VibFreq(std::vector<double>& vibFreq){
      vibFreq.clear();
      vibFreq.assign(m_VibFreq.begin(), m_VibFreq.end());
    }

    DensityOfStatesCalculator* get_DensityOfStatesCalculator(){return m_pDensityOfStatesCalculator;}
    void set_DensityOfStatesCalculator(DensityOfStatesCalculator* value){m_pDensityOfStatesCalculator = value;}

    int getSpinMultiplicity() const        { return m_SpinMultiplicity; }
    void   setSpinMultiplicity(int value)  { m_SpinMultiplicity = value; }

    // Calculate the average grain energy and then number of states per grain.
    void calcGrainAverages() ;

    // Test the rovibrational density of states.
    virtual void testDensityOfStates() ;
  } ;

  //**************************************************
  ///Transition states have no collisional properties
  class TransitionState : public ModelledMolecule
  {
  public:
    TransitionState(const MesmerEnv& Env);
    virtual ~TransitionState(){}
    // Initialize TransitionState.
//    virtual bool InitializeMolecule(PersistPtr pp); Nothing to initialize?

  };

  //**************************************************
  ///For most molecules
  class CollidingMolecule : public ModelledMolecule
  {

    //-------------------------------
    // Variables:
    // Collision operator properties.
    //
    double              m_DeltaEdown ;         // <Delta E down> for the exponential down model.
    double              m_collisionFrequency ; // Current value of collision frequency.
    int                 m_ncolloptrsize ;      // Size of the collision operator matrix.
    dMatrix             *m_egme ;              // Matrix containing the energy grained collision operator.

    //-------------------------------
    // Calculate collision frequency.
    double collisionFrequency(double beta, const double conc, Molecule *pBathGasMolecule) ;
    // Calculate collision operator.
    bool   collisionOperator (double beta) ;

  public:
    CollidingMolecule(const MesmerEnv& Env);
    ~CollidingMolecule();

    // Initialize CollidingMolecule.
    virtual bool InitializeMolecule(PersistPtr ppp);

    // Initialize the Collision Operator.
    bool initCollisionOperator(double beta, Molecule *pBathGasMolecule) ;

    // Diagonalize the Collision Operator. See ReactionManager::diagCollisionOperator()
    //void diagCollisionOperator() ;

    // Calculate a reaction matrix element.
    double matrixElement(int eigveci, int eigvecj, std::vector<double> &k, int ndim) ;

    void copyCollisionOperator(dMatrix *CollOptr, const int size, const int locate, const double RducdOmega) const ;

    // Accessors.
    double get_collisionFrequency() const { return m_collisionFrequency ;} ;
    void set_colloptrsize(int ncolloptrsize) {m_ncolloptrsize = ncolloptrsize ;} ;
    int  get_colloptrsize() const {return m_ncolloptrsize ;} ;
  };

  // class representing pair of molecules participating one association reaction
  // this class should account for their density of states as a convolution
  class SuperMolecule : public CollidingMolecule
  {
  public:
    CollidingMolecule* m_mol1;
    ModelledMolecule*  m_mol2;

    SuperMolecule(const MesmerEnv& Env);
//     SuperMolecule(double zpe, CollidingMolecule* mol1p, ModelledMolecule* mol2p, MesmerEnv& Env);
    ~SuperMolecule();

    // Initialize SuperMolecule.
    virtual bool InitializeMolecule(PersistPtr pp);

    // Accessors.

    // set composing member of the SuperMolecule, also copy necessary properties
    void setMembers(CollidingMolecule* mol1p, ModelledMolecule* mol2p){
      m_mol1 = mol1p;
      m_mol2 = mol2p;
      m_VibFreq.assign(m_mol1->m_VibFreq.begin(), m_mol1->m_VibFreq.end());
      for (size_t i(0); i < m_mol2->m_VibFreq.size(); ++i)
        m_VibFreq.push_back(m_mol2->m_VibFreq[i]);
      set_zpe(m_mol1->get_zpe() + m_mol2->get_zpe());
      setSpinMultiplicity(m_mol1->getSpinMultiplicity() + m_mol2->getSpinMultiplicity());
      set_DensityOfStatesCalculator(m_mol1->get_DensityOfStatesCalculator());
    }

    CollidingMolecule* getMember1(){ return m_mol1;}
    ModelledMolecule * getMember2(){ return m_mol2;}

    //virtual void testDensityOfStates(const MesmerEnv &m_Env) ;

  };

}//namespace
#endif // GUARD_Molecule_h
