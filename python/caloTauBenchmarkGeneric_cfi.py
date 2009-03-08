import FWCore.ParameterSet.Config as cms


#'tauGenJets'
caloTauBenchmarkGeneric = cms.EDAnalyzer("GenericBenchmarkAnalyzer",
    OutputFile = cms.untracked.string('benchmark.root'),
    InputTruthLabel = cms.InputTag(''),
    minEta = cms.double(-1),
    maxEta = cms.double(2.8),
    recPt = cms.double(10.0),
    deltaRMax = cms.double(0.3),
    StartFromGen = cms.bool(True),
    PlotAgainstRecoQuantities = cms.bool(False),
    OnlyTwoJets = cms.bool(False),
    BenchmarkLabel = cms.string( 'CaloTaus' ),
    InputRecoLabel = cms.InputTag('')
)