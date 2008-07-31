// -*- C++ -*-
//
// Package:    JetAna
// Class:      JetAna
// 
/**\class JetAna JetAna.cc Work/JetAna/src/JetAna.cc

 Description: <one line class summary>

 Implementation:

module pfJetAnalyzer = JetAna 
 { 
   string InputTruthLabel = 'iterativeCone5GenJets'
   string InputRecoLabel  = 'iterativeCone5PFJets'
   untracked string OutputFile = 'PFJetTester_data.root'
   bool PlotAgainstRecoQuantities = true
   string BenchmarkLabel = 'ParticleFlow'
   double recPt = 22 # -1 means no cut
   double maxEta = 3 # -1 means no cut

   bool pfjBenchmarkDebug = 0
   double deltaRMax = 0.1
 }

*/
//
// Original Author:  Michel Della Negra
//         Created:  Wed Jan 23 10:11:13 CET 2008
// $Id: JetAna.cc,v 1.1 2008/07/17 13:21:20 weng Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"

#include "RecoParticleFlow/Benchmark/interface/PFJetBenchmark.h"


using namespace edm;
using namespace reco;
using namespace std;



//
// class decleration



 
class JetAna : public edm::EDAnalyzer {
public:
  explicit JetAna(const edm::ParameterSet&);
  ~JetAna();


private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  // ----------member data ---------------------------

};
/// PFJet Benchmark

//neuhaus - comment
PFJetBenchmark PFJetBenchmark_;
string sGenJetAlgo;
string sJetAlgo;
string outjetfilename;
bool pfjBenchmarkDebug;
bool PlotAgainstReco;
double deltaRMax=0.1;
string benchmarkLabel_;
double recPt;
double maxEta;

DaqMonitorBEInterface* dbe_;
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
JetAna::JetAna(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  sGenJetAlgo = 
    iConfig.getParameter<string>("InputTruthLabel");
  sJetAlgo = 
    iConfig.getParameter<string>("InputRecoLabel");
  outjetfilename = 
    iConfig.getUntrackedParameter<string>("OutputFile");
  pfjBenchmarkDebug = 
    iConfig.getParameter<bool>("pfjBenchmarkDebug");
  PlotAgainstReco = 
    iConfig.getParameter<bool>("PlotAgainstRecoQuantities");
  deltaRMax = 
    iConfig.getParameter<double>("deltaRMax");	  
  benchmarkLabel_  = 
    iConfig.getParameter<string>("BenchmarkLabel"); 
  recPt  = 
    iConfig.getParameter<double>("recPt"); 
  maxEta = 
    iConfig.getParameter<double>("maxEta"); 
  
  dbe_ = edm::Service<DaqMonitorBEInterface>().operator->();

      
  PFJetBenchmark_.setup(
			outjetfilename,
			dbe_, 
			pfjBenchmarkDebug,
			PlotAgainstReco,
			deltaRMax,
			benchmarkLabel_, 
			recPt, 
			maxEta);
}


JetAna::~JetAna()
{
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
JetAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Typedefs to use views
  // Typedefs to use views
  typedef edm::View<reco::Candidate> candidateCollection ;
  typedef edm::View<reco::Candidate> pfcandidateCollection ;
//  typedef edm::View<reco::GenJet> candidateCollection ;
//  typedef edm::View<reco::PFJet> pfcandidateCollection ;
  
  const candidateCollection *truth_candidates;
  const pfcandidateCollection *reco_candidates;
 
  // ==========================================================
  // Retrieve!
  // ==========================================================

  { 
    // Get Truth Candidates (GenCandidates, GenJets, etc.)
    Handle<candidateCollection> truth_hnd;
    iEvent.getByLabel(sGenJetAlgo, truth_hnd);
    truth_candidates = truth_hnd.product();

    // Get Reco Candidates (PFlow, CaloJet, etc.)
    Handle<pfcandidateCollection> reco_hnd;
    iEvent.getByLabel(sJetAlgo, reco_hnd);
    reco_candidates = reco_hnd.product();

    // no longer needed with template-ized Benchmark
    //const PFCandidateCollection *pf_candidates = reco_hnd.product();
    //static CandidateCollection reco_storage = algo_->makeCandidateCollection(pf_candidates);
    //reco_candidates = &reco_storage;

  }
  if (!truth_candidates || !reco_candidates) {

    edm::LogInfo("OutputInfo") << " failed to retrieve data required by ParticleFlow Task";
    edm::LogInfo("OutputInfo") << " ParticleFlow Task cannot continue...!";
    return;

  }

  PFJetBenchmark_.process(reco_candidates, truth_candidates);
}


// ------------ method called once each job just before starting event loop  ------------
void 
JetAna::beginJob(const edm::EventSetup&)
{
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetAna::endJob() {
  PFJetBenchmark_.save();
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetAna);
