# Runs PFBenchmarkAnalyzer and PFJetBenchmark on PFJet sample to
# monitor performance of PFJets

import FWCore.ParameterSet.Config as cms
  
process = cms.Process("TEST")
process.load("DQMServices.Core.DQM_cfg")


process.source = cms.Source (
    "PoolSource",    
    fileNames = cms.untracked.vstring(
    # Fast
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_0.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_1.root', 
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_2.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_3.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_4.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_5.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_6.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_7.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_8.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_9.root',
       'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Fast_10.root'
     # Full
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Full_001.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Full_002.root',
       #'rfio:/castor/cern.ch/user/p/pjanot/CMSSW330pre4/aod_QCDForPF_Full_003.root'
       ),
    secondaryFileNames = cms.untracked.vstring(),
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
    
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
# The following 7 lines is to cure a bug in Generators/Pythi6Interface
# for the pythia jet gun
process.genParticlesForJets.ignoreParticleIDs.append(1)
process.genParticlesForJets.ignoreParticleIDs.append(2)
process.genParticlesForJets.ignoreParticleIDs.append(3)
process.genParticlesForJets.ignoreParticleIDs.append(4)
process.genParticlesForJets.ignoreParticleIDs.append(5)
process.genParticlesForJets.ignoreParticleIDs.append(6)
process.genParticlesForJets.ignoreParticleIDs.append(21)
process.genParticlesForJets.excludeResonances = False


process.pfJetBenchmark.OutputFile = cms.untracked.string('JetBenchmark_Fast_330pre4.root')

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