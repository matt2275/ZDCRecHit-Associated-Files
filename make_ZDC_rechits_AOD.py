import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECOgpu')
# process = cms.Process('RECOgpu', eras.Run2_2018)
# process = cms.Process('RECOgpu', eras.Run3_2023)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('HeterogeneousCore.CUDACore.ProcessAcceleratorCUDA_cfi')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '140X_dataRun3_Prompt_frozen_v1', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

#-----------------------------------------
# INPUT
#-----------------------------------------

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('/store/hidata/HIRun2023A/HIForward0/AOD/16Jan2024-v1/2810000/015b7c65-f17d-45d5-9858-a81d7e779bc5.root'),
  inputCommands = cms.untracked.vstring('keep *', 
      'drop *_zdcreco_*_*')
)

# process.hltGetRaw = cms.EDAnalyzer( "HLTGetRaw",
    # RawDataCollection = cms.InputTag( "rawDataCollector" )
# )

# process.input = cms.Path( process.hltGetRaw )

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
# process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")

process.load("RecoLuminosity.LumiProducer.bunchSpacingProducer_cfi")




# -----------------------------------------
# CMSSW/Hcal ZDC Reconstructor
# -----------------------------------------


process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_Run3_cfi")

process.zdcreco.ignoreRPD = cms.bool(True)


# import RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_Run3_cfi
# process.zdcrereco = RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_Run3_cfi.zdcreco.clone()
# process.zdcrereco.ignoreRPD = cms.bool(True)


process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")



# Salavat's fix to allow hardcoded REAL ZDC info
# CONDDIR = '/conditions/'   #  directory with txt conditions in the local release area  
CONDDIR = 'ZDC_Conditions/'   #  directory with txt conditions in the local release area  

process.es_prefer = cms.ESPrefer('HcalTextCalibrations','es_ascii')
process.es_ascii = cms.ESSource('HcalTextCalibrations',
    input = cms.VPSet(
       cms.PSet(
          object = cms.string('ChannelQuality'),
          file   = cms.FileInPath(CONDDIR+'ChannelQuality_ZDC.txt')
       ),
      cms.PSet(
          object = cms.string('Pedestals'),
          file   = cms.FileInPath(CONDDIR+'Pedestals_ZDC.txt')
          # file   = cms.FileInPath(CONDDIR+'Pedestals_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('EffectivePedestals'),
          file   = cms.FileInPath(CONDDIR+'EffectivePedestals_ZDC.txt')
          # file   = cms.FileInPath(CONDDIR+'Pedestals_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('PedestalWidths'),
          file   = cms.FileInPath(CONDDIR+'PedestalWidths_ZDC_wIntro.txt')
      ),
      cms.PSet(
          object = cms.string('EffectivePedestalWidths'),
          file   = cms.FileInPath(CONDDIR+'EffectivePedestalWidths_ZDC_wIntro.txt')
      ),
      cms.PSet(
          object = cms.string('Gains'),
          file   = cms.FileInPath(CONDDIR+'Gains_ZDC_NonZeroRPD_Corrected.txt')
      ),
      cms.PSet(
          object = cms.string('TimeCorrs'),
          file   = cms.FileInPath(CONDDIR+'TimeCorrs_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('LUTCorrs'),
          file   = cms.FileInPath(CONDDIR+'LUTCorrs_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('ElectronicsMap'),
          file   = cms.FileInPath(CONDDIR+'ElectronicsMap_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('QIEData'),
          file   = cms.FileInPath(CONDDIR+'QIEData_ZDC_AVG.txt')
      ),
      cms.PSet(
          object = cms.string('QIETypes'),
          file   = cms.FileInPath(CONDDIR+'QIETypes_ZDC.txt')
      ),
      cms.PSet(
          object = cms.string('LongRecoParams'),
          file   = cms.FileInPath(CONDDIR+'LongRecoParams.txt')
      ),
      cms.PSet(
          object = cms.string('RespCorrs'),
          file   = cms.FileInPath(CONDDIR+'RespCorrs_ZDC.txt')
      )
   )
)

#-----------------------------------------
# OUTPUT
#-----------------------------------------

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("TestZDCRecHits_Run3.root"),
    outputCommands = cms.untracked.vstring('drop *', 
        'keep doubles_zdcdigi_*_*', 
        'keep ZDCRecHitsSorted_zdcreco_*_*')
)



process.finalize = cms.EndPath(process.out)


#-----------------------------------------
# schudeling
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

# # comment out to run zdcana since can only handle 1 thread/stream
process.options = cms.untracked.PSet(
    # numberOfThreads = cms.untracked.uint32(8),
    # numberOfStreams = cms.untracked.uint32(8),
    # SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000
