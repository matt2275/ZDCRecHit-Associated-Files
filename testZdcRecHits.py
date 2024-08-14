import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('TestZdcRecHit')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('HeterogeneousCore.CUDACore.ProcessAcceleratorCUDA_cfi')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '140X_dataRun3_Prompt_frozen_v1', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

#-----------------------------------------
# INPUT
#-----------------------------------------

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('/store/hidata/HIRun2023A/HIForward0/AOD/16Jan2024-v1/2810000/14f851d2-7c11-4ac4-9650-3428cc184582.root'),
  
  # removing old zdcreco
  inputCommands = cms.untracked.vstring('keep *', 
      'drop *_zdcreco_*_*')
)

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

# -----------------------------------------
# CMSSW/Hcal ZDC Reconstructor
# -----------------------------------------


process.zdcreco = cms.EDProducer('ZdcHitReconstructor_Run3')
process.zdcreco.skipRPD = cms.bool(True)


process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("ProcessOut_TestZdcRecHit.root"),
    outputCommands = cms.untracked.vstring('drop *', 
        'keep doubles_zdcdigi_*_*', 
        'keep ZDCRecHitsSorted_zdcreco_*_*')
)


process.finalize = cms.EndPath(process.out)

#-----------------------------------------
# gpu test
#-----------------------------------------


process.recoPathZDC = cms.Path(
    process.zdcreco
)

#---------------



#---------------

process.schedule = cms.Schedule(
    process.recoPathZDC,
    process.finalize
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 100
