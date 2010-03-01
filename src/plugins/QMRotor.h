#ifndef GUARD_QMRotor_h
#define GUARD_QMRotor_h

#include "DensityOfStates.h"
#include "MolecularComponents.h"

namespace mesmer
{
  class QMRotor : public DensityOfStatesCalculator
  {
  public:

    // Provide a function to define particular counts of the DOS of a molecule.
    virtual bool countCellDOS(gDensityOfStates* mol, int MaximumCell);

    ///Constructor which registers with the list of DensityOfStatesCalculators in the base class
    //This class calculates a complete DOS: it is not an extra class. 
    QMRotor(const std::string& id) : DensityOfStatesCalculator(id, false){}
    virtual QMRotor* Clone() { return new QMRotor(*this); }

    virtual ~QMRotor() {}

  private:

    void asymmetricRotor(double A, double B, double C, int J, double kpp, vector<double> &Er) ;

  } ;

}//namespace

#endif // GUARD_QMRotor_h