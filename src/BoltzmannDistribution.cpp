//-------------------------------------------------------------------------------------------
//
// BoltzmannDistribution.cpp
//
// Author: Chi-Hsiu Liang
// Date:   _2008_05_15_
//
// Produces Boltzmann distribution
//
//-------------------------------------------------------------------------------------------
#include "BoltzmannDistribution.h"

namespace mesmer
{
  //************************************************************
  //Global instance, defining its id (usually the only instance)
  BoltzmannDistribution theBoltzmannDistribution("Boltzmann");
  //************************************************************

  bool BoltzmannDistribution::calculateDistribution(const std::vector<double>& DOS,
                                                    const std::vector<double>& Ene,
                                                    const double& beta,
                                                    std::vector<double>& dist)
  {
    // The Boltzmann distribution applies only to particles at a high enough temperature
    // and low enough density that quantum effects can be ignored, and the particles are
    // obeying Maxwell�Boltzmann statistics.

    dist.clear();
    int vsize = static_cast<int>(DOS.size());
    // Calculate unnormalized Boltzmann dist.
    // Note the extra 10.0 is to prevent underflow, it is removed during normalization.
    for (int i = 0; i < vsize; ++i) {
      dist.push_back(exp(log(DOS[i]) - beta * Ene[i] + 10.0));
    }
    return true;
  }
}//namespace

