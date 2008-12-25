# Runs PFBenchmarkAnalyzer and PFJetBenchmark on PFJet sample to
# monitor performance of PFJets

import FWCore.ParameterSet.Config as cms
  
process = cms.Process("TEST")
process.load("DQMServices.Core.DQM_cfg")


process.source = cms.Source (
    "PoolSource",    
    fileNames = cms.untracked.vstring(
    # Fast
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_0.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_1.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_2.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_3.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_4.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_5.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_6.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_7.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_8.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_9.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Fast_10.root'
    # Full
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_000.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_001.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_002.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_003.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_004.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_005.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_006.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_007.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_008.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW300pre3/aod_QCDForPF_Full_009.root'
       ),
    secondaryFileNames = cms.untracked.vstring(),
    noEventSort = cms.untracked.bool(True)
    
    )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.load("Validation.RecoParticleFlow.pfJetBenchmark_cfi")
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff") 
process.load("RecoJets.Configuration.RecoPFJets_cff") 
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.iterativeCone5PFJets.inputEtMin = 0.0

# should do a cloning
process.genParticlesForJets.ignoreParticleIDs.append(14)
process.genParticlesForJets.ignoreParticleIDs.append(12)
process.genParticlesForJets.ignoreParticleIDs.append(16)
process.genParticlesForJets.excludeResonances = False


process.pfJetBenchmark.OutputFile = cms.untracked.string('JetBenchmark.root')

process.p =cms.Path(
    process.genJetParticles+
    process.iterativeCone5GenJets+
    #process.iterativeCone5PFJets+
    process.pfJetBenchmark
    )


process.schedule = cms.Schedule(process.p)



process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options = cms.untracked.PSet(
    makeTriggerResults = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True),
    Rethrow = cms.untracked.vstring('Unknown', 
        'ProductNotFound', 
        'DictionaryNotFound', 
        'InsertFailure', 
        'Configuration', 
        'LogicError', 
        'UnimplementedFeature', 
        'InvalidReference', 
        'NullPointerError', 
        'NoProductSpecified', 
        'EventTimeout', 
        'EventCorruption', 
        'ModuleFailure', 
        'ScheduleExecutionFailure', 
        'EventProcessorFailure', 
        'FileInPathError', 
        'FatalRootError', 
        'NotFound')
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000
