import FWCore.ParameterSet.Config as cms

jets = 'iterativeCone5CaloJets'

caloJetBenchmark = cms.EDAnalyzer("GenericBenchmarkAnalyzer",
    OutputFile = cms.untracked.string('JetBenchmark.root'),
    InputTruthLabel = cms.string('iterativeCone5GenJets'),
    maxEta = cms.double(3.0),
    recPt = cms.double(10.0),
    deltaRMax = cms.double(0.2),
    PlotAgainstRecoQuantities = cms.bool(False),
    BenchmarkLabel = cms.string( jets ),
    InputRecoLabel = cms.string( jets )
)
