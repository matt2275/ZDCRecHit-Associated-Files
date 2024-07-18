import FWCore.ParameterSet.Config as cms

zdcanalyzer = cms.EDAnalyzer(
   "MNZDCAnalyzerWithDigis",
   ZDCSource    = cms.InputTag('zdcreco'),
   ZDCDigiSource    = cms.InputTag('hcalDigis', 'ZDC'),
   MinZDCEn = cms.double(0.0),
   MaxZDCEn = cms.double(-1)
 ) # zdcreco

