# Runs PFBenchmarkAnalyzer on CaloJets an PFJets to
# compare performance and create TauBenchmarkPlot

import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")
process.load("DQMServices.Core.DQM_cfg")

process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("RecoJets.Configuration.GenJetParticles_cff")

process.load("RecoJets.Configuration.RecoGenJets_cff")

process.load("RecoJets.Configuration.RecoPFJets_cff")

process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/data11/Higgs08/Pflow/singletau_fevtfull50GeV_200.root')
)

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
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.pfAnalyzer = cms.EDAnalyzer("GenericBenchmarkAnalyzer",
    OutputFile = cms.untracked.string('TauBenchmark.root'),
    InputTruthLabel = cms.InputTag('iterativeCone5GenJets'),
    maxEta = cms.double(3.0),
    recPt = cms.double(10.0),
    deltaRMax = cms.double(0.2),
    PlotAgainstRecoQuantities = cms.bool(False),
    BenchmarkLabel = cms.string('ParticleFlow'),
    InputRecoLabel = cms.InputTag('iterativeCone5PFJets')
)

process.caloAnalyzer = cms.EDAnalyzer("GenericBenchmarkAnalyzer",
    InputTruthLabel = cms.InputTag('iterativeCone5GenJets'),
    maxEta = cms.double(3.0),
    recPt = cms.double(10.0),
    deltaRMax = cms.double(0.2),
    PlotAgainstRecoQuantities = process.pfAnalyzer.PlotAgainstRecoQuantities,
    OutputFile = process.pfAnalyzer.OutputFile,
    BenchmarkLabel = cms.string('Calo'),
    InputRecoLabel = cms.InputTag('iterativeCone5CaloJets')
 
)
# Optional 
process.pfJetAnalyzer = cms.EDAnalyzer("PFJetBenchmarkAnalyzer",
    OutputFile = process.pfAnalyzer.OutputFile, 
    InputTruthLabel = process.pfAnalyzer.InputTruthLabel, 
    maxEta = process.pfAnalyzer.maxEta,
    recPt = process.pfAnalyzer.recPt,
    PlotAgainstRecoQuantities = process.pfAnalyzer.PlotAgainstRecoQuantities,
    pfjBenchmarkDebug = cms.bool(False),
    deltaRMax = process.pfAnalyzer.deltaRMax,
    BenchmarkLabel = process.pfAnalyzer.BenchmarkLabel,
    InputRecoLabel = process.pfAnalyzer.InputRecoLabel
)


#process.pfTester = cms.EDFilter("PFTester",
#    InputPFlowLabel = cms.string('particleFlow'),
#    OutputFile = cms.untracked.string('PFTester_data.root')
#)



process.p =cms.Path(process.genParticles*process.genJetParticles*process.recoGenJets*process.pfAnalyzer*process.caloAnalyzer*process.pfJetAnalyzer)

process.schedule = cms.Schedule(process.p)

process.MessageLogger.cerr.FwkReport.reportEvery = 50
process.genParticlesForJets.ignoreParticleIDs.append(14)
process.genParticlesForJets.ignoreParticleIDs.append(12)
process.genParticlesForJets.ignoreParticleIDs.append(16)
process.genParticlesForJets.excludeResonances = False

process.PoolSource.fileNames = ['/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/08C0C180-8E82-DD11-9DAA-001617C3B78C.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/24789C0E-8E82-DD11-84CE-000423D94524.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/26C4289D-8E82-DD11-A748-000423D990CC.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/2A1A0206-8E82-DD11-9050-0019DB29C620.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/4411B47E-8E82-DD11-BC7E-001617C3B65A.root', 
    '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/486A6197-8E82-DD11-A9F7-001617C3B778.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/52494D86-8E82-DD11-BBA7-001617DBD230.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/6607020F-8E82-DD11-8ADD-000423D94E70.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/6A6BDC80-8E82-DD11-AC1B-0019DB2F3F9B.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/6C333112-8E82-DD11-BF7E-00161757BF42.root', 
    '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/72A0337E-8E82-DD11-8E06-0019DB29C614.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/B245F491-8E82-DD11-9482-000423D60FF6.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/C0AD1FF1-8D82-DD11-BD34-001617E30D40.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/C65AD820-8E82-DD11-AAC9-000423D944FC.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/CCAD70EE-8D82-DD11-B045-000423D99CEE.root', 
    '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0002/CE61AB9D-8E82-DD11-9C12-001617DBD472.root', '/store/relval/CMSSW_2_1_8/RelValZTT/GEN-SIM-DIGI-RAW-HLTDEBUG-RECO/IDEAL_V9_v1/0003/30B514E9-A682-DD11-B92F-000423D9517C.root']
