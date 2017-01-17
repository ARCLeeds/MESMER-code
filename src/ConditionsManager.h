#ifndef GUARD_ConditionsManager_h
#define GUARD_ConditionsManager_h

#include <vector>
#include "System.h"
#include "ParallelManager.h"
#include "AnalysisData.h"

namespace mesmer
{

  struct conditionSet
  {
  public:
    conditionSet(std::string ref1, std::string ref2, std::string refReaction, double value, double error) :
      m_ref1(ref1), m_ref2(ref2), m_refReaction(refReaction), m_value(value), m_error(error), m_calcValue(0.0)
    {}

    void get_conditionSet(std::string& ref1, std::string& ref2, std::string& refReaction, double& value, double& error) {
      ref1 = m_ref1;
      ref2 = m_ref2;
      refReaction = m_refReaction;
      value = m_value;
      error = m_error;
    }

    std::string m_ref1;
    std::string m_ref2;
    std::string m_refReaction;
    double m_value;
    double m_error;
    double m_calcValue;
  };

  struct RawDataSet
  {
    std::vector<std::pair<double, double> > data; // Time series data.
    std::string m_ref1;                           // Monitored species.
    const char* m_Name;                           // Name of trace.
    double m_excessConc;                          // Concentration of excess reactant. 
  };

  // Functor to compare times in RawDataSet.
  class Before
  {
  private:
    double startT;
  public:
    Before(double start) :startT(start) {}
    bool operator()(std::pair<double, double> val) { return val.first < startT; }
  };

  // To make sure if there is a concentration or pressure definition, there is a temperature definition.
  struct CandTpair {

    double      m_concentration; // particles per cubic centimeter
    double      m_temperature; // Kelvin
    Precision   m_precision;
    std::string m_pBathGasName;
    std::map<Reaction*, double> m_excessConcs; // Reaction, conc in ppcc

    std::vector<conditionSet> m_rates;
    std::vector<conditionSet> m_yields;
    std::vector<conditionSet> m_eigenvalues;
    std::vector<RawDataSet>   m_rawDataSets;
    std::vector<PersistPtr>   m_expDataPtrs;

		AnalysisData m_analysisData;

    CandTpair(double cp_, double t_, Precision _pre, const char* _bathGas,
      const map<Reaction*, double>& _excessConcs)
      : m_concentration(cp_), m_temperature(t_), m_precision(_pre),
      m_pBathGasName(_bathGas), m_excessConcs(_excessConcs) {}

    void set_experimentalRates(PersistPtr ppData, std::string ref1, std::string ref2,
      std::string refReaction, double value, double error) {
      m_rates.push_back(conditionSet(ref1, ref2, refReaction, value, error));
      m_expDataPtrs.push_back(ppData);
    }

    void set_experimentalYields(PersistPtr ppData, std::string ref, std::string yieldTime, double value, double error) {
      m_yields.push_back(conditionSet(ref, yieldTime, std::string(""), value, error));
      m_expDataPtrs.push_back(ppData);
    }

    void set_experimentalEigenvalues(PersistPtr ppData, std::string eigenvalueID, double value, double error) {
      m_eigenvalues.push_back(conditionSet(std::string(""), std::string(""), eigenvalueID, value, error));
      m_expDataPtrs.push_back(ppData);
    }

    void set_calcRates(std::vector<double>& calcRates) {
      for (size_t i(0); i < calcRates.size(); ++i) {
        m_rates[i].m_calcValue = calcRates[i];
      }
    };

    void set_calcYields(std::vector<double>& calcYields) {
      for (size_t i(0); i < calcYields.size(); ++i) {
        m_yields[i].m_calcValue = calcYields[i];
      }
    };

    void set_calcEigenvalues(std::vector<double>& calcEigenvalues) {
      for (size_t i(0); i < calcEigenvalues.size(); ++i) {
        m_eigenvalues[i].m_calcValue = calcEigenvalues[i];
      }
    };

  };


  //****************************************************************************************************
  class ConditionsManager
  {
  public:

    ConditionsManager(System* pSys);

    // Reads the general bathgas from <me:conditions>
    bool ParseBathGas(PersistPtr ppConditions);
    // Reads the rest of  <me:conditions>
    bool ParseConditions();

    size_t      getNumPTPoints() const { return PandTs.size(); }
    double      PTPointTemp(int index) { return PandTs[index].m_temperature; }
    double      PTPointConc(int index) { return PandTs[index].m_concentration; }
    const char* PTPointBathGas(int index) { return PandTs[index].m_pBathGasName.c_str(); }
    Precision   PTPointPrecision(int index) { return PandTs[index].m_precision; }
    map<Reaction*, double> PTPointExcessConcs(int index) { return PandTs[index].m_excessConcs; }

    // An accessor method to get conditions and related properties for
    // use with plugins classes etc.
    bool getConditions(std::vector<double> &Temperature, std::vector<double> &Concentration);

    double getMaxTemperature();

    void get_experimentalRates(unsigned index, std::vector<conditionSet>& rates) const
    {
      rates = PandTs[index].m_rates;
    }

    void set_calculatedRates(unsigned index, std::vector<double>& calcRates)
    {
      PandTs[index].set_calcRates(calcRates);
    }

    void get_experimentalYields(unsigned index, std::vector<conditionSet>& yields) const
    {
      yields = PandTs[index].m_yields;
    }

    void set_calculatedYields(unsigned index, std::vector<double>& calcYields)
    {
      PandTs[index].set_calcYields(calcYields);
    }

    void get_experimentalEigenvalues(unsigned index, std::vector<conditionSet>& eigenvalues) const
    {
      eigenvalues = PandTs[index].m_eigenvalues;
    }

    void set_calculatedEigenvalues(unsigned index, std::vector<double>& calcEigenvalues)
    {
      PandTs[index].set_calcEigenvalues(calcEigenvalues);
    }

    const std::vector<RawDataSet>& get_experimentalrawDataSets(unsigned index) const
    {
      return PandTs[index].m_rawDataSets;
    }

    PersistPtr get_experimentalDataPtr(unsigned index, size_t i) const
    {
      return PandTs[index].m_expDataPtrs[i];
    }

		AnalysisData* get_analysisData(unsigned index) 
		{
			return &(PandTs[index].m_analysisData);
		}

		GeneralAnalysisData* get_generalAnalysisData()
		{
			return &generalAnalysisData ;
		}

		// Collect bath gas names from PandTs.
    void getAllBathGases(std::set<std::string>& bathGases);

    // Reconcile table across processs.
    void reconcileTable();

    // Write data table.
    void WriteDataTable() const;

    // Write calculated date to output.
    void AddCalcValToXml() const;

		// Write data table.
		void WriteAnalysisXML(PersistPtr m_ppIOPtr) ;

	private:

    bool readPTs();

    bool ReadRange(const std::string&    name,
      std::vector<double>&  vals,
      PersistPtr            ppbase,
      bool                  MustBeThere = true);

    // Write calculated date to XML.
    void WriteDataToXml(PersistPtr pp, const vector<conditionSet> &data) const;

    System* m_pSys; //parent System

    PersistPtr m_ppConditions;

    // The excess reactant concentrations as specified in <Reaction>.
    // Provides unchanging base data when excess concs are individually
    // specified in <PTPair>

    std::map<Reaction*, double> baseExcessConcs; // Reaction, conc in ppcc

    // Paired concentration and pressure points.
    std::vector<CandTpair> PandTs;

    // Location of the parallel mananger.
    ParallelManager *m_pParallelManager;

		// General analysis data.
		GeneralAnalysisData generalAnalysisData;

  };

}//namespace
#endif
