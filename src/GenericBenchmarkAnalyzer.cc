#include "Validation/RecoParticleFlow/interface/GenericBenchmarkAnalyzer.h"
// author: Mike Schmitt, University of Florida
// first version 11/7/2007
// extension: Leo Neuhaus & Joanna Weng 09.2008
// Performs matching and basic resolution plots of 2 candidate
// (or candidate based) collections

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"


#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include <vector>
#include <ostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>

using namespace reco;
using namespace edm;
using namespace std;

GenericBenchmarkAnalyzer::GenericBenchmarkAnalyzer(const edm::ParameterSet& iConfig)
{

  inputTruthLabel_             = iConfig.getParameter<edm::InputTag>("InputTruthLabel");
  inputRecoLabel_              = iConfig.getParameter<edm::InputTag>("InputRecoLabel");
  outputFile_                  = iConfig.getUntrackedParameter<std::string>("OutputFile");
  benchmarkLabel_              = iConfig.getParameter<std::string>("BenchmarkLabel"); 
  plotAgainstRecoQuantities_   = iConfig.getParameter<bool>("PlotAgainstRecoQuantities");
  recPt_cut                    = iConfig.getParameter<double>("recPt");
  maxEta_cut                    = iConfig.getParameter<double>("maxEta");
  deltaR_cut                    = iConfig.getParameter<double>("deltaRMax");

  if (outputFile_.size() > 0)
    edm::LogInfo("OutputInfo") << " ParticleFLow Task histograms will be saved to '" << outputFile_.c_str()<< "'";
  else edm::LogInfo("OutputInfo") << " ParticleFlow Task histograms will NOT be saved";

}

GenericBenchmarkAnalyzer::~GenericBenchmarkAnalyzer() { }

void GenericBenchmarkAnalyzer::beginJob(const edm::EventSetup& iSetup)
{

  // get ahold of back-end interface
  dbe_ = edm::Service<DQMStore>().operator->();
  
  if (dbe_) {
    //dbe_->setVerbose(1);
    string path = "PFTask/Benchmarks/" + benchmarkLabel_ + "/";
    if (plotAgainstRecoQuantities_) path += "Reco"; else path += "Gen";
    dbe_->setCurrentFolder(path.c_str());
    setup(dbe_, plotAgainstRecoQuantities_);

  }

}

void GenericBenchmarkAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  // Typedefs to use views
  typedef edm::View<reco::Candidate> candidateCollection ;
  typedef edm::View<reco::Candidate> candidateCollection ;
  
  const candidateCollection *truth_candidates;
  const candidateCollection *reco_candidates;
 
  // ==========================================================
  // Retrieve!
  // ==========================================================

  { 
    // Get Truth Candidates (GenCandidates, GenJets, etc.)
    Handle<candidateCollection> truth_hnd;
    iEvent.getByLabel(inputTruthLabel_, truth_hnd);
    truth_candidates = truth_hnd.product();

    // Get Reco Candidates (PFlow, CaloJet, etc.)
    Handle<candidateCollection> reco_hnd;
    iEvent.getByLabel(inputRecoLabel_, reco_hnd);
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

  // ==========================================================
  // Analyze!
  // ==========================================================

  fill(reco_candidates,truth_candidates,plotAgainstRecoQuantities_, recPt_cut, maxEta_cut, deltaR_cut);

}

void GenericBenchmarkAnalyzer::endJob() 
{

  // Store the DAQ Histograms
  if (outputFile_.size() != 0)
    dbe_->save(outputFile_);

}