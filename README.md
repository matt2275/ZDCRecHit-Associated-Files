# TnP tree producer

* Copy of:

  ```
  git clone git@github.com:sscruz/Tnp94.git MuonAnalysis/TagAndProbe -b 94_newSelector
  ```



## Recipe

```
cmsrel CMSSW_10_2_5
cd CMSSW_10_2_5/src
cmsenv

git cms-merge-topic HuguesBrun:updateL3MuonCollectionsToMatch
git clone git@github.com:KyeongPil-Lee/MuonAnalysis-TagAndProbe.git MuonAnalysis/TagAndProbe -b 102X
git cms-addpkg PhysicsTools/PatAlgos

vi PhysicsTools/PatAlgos/plugins/PATMuonProducer.cc
# -- change the line:
# -- bool simInfoIsAvailalbe = iEvent.getByToken(simInfo_,simInfo); ->
# -- bool simInfoIsAvailalbe=false;

git cms-addpkg MuonAnalysis/MuonAssociators

vi MuonAnalysis/MuonAssociators/python/patMuonsWithTrigger_cff.py
# -- add several lines by following the section below ("Update of patMuonsWithTrigger_cff.py")

scram b -j 4 >&scram.log&
tail -f scram.log
```





### Update of patMuonsWithTrigger_cff.py

Several lines should be added & updated to make patMuonsWithTrigger be able to recognize OldMu100

1) Below

```
patTrigger = cms.EDProducer("TriggerObjectFilterByCollection",
    src = cms.InputTag("patTriggerFull"),
    collections = cms.vstring("hltL1extraParticles", "hltGmtStage2Digis", "hltL2MuonCandidates", "hltIterL3MuonCandidates","hltIterL3FromL2MuonCandidates","hltHighPtTkMuonCands", "hltGlbTrkMuonCands", "hltMuTrackJpsiCtfTrackCands", "hltMuTrackJpsiEffCtfTrackCands", "hltMuTkMuJpsiTrackerMuonCands","hltTracksIter"),
)
```

, add the line:

```
patTrigger.collections.append( "hltOldL3MuonCandidates" ) # -- for OldMu100
```



2) below

```
muonMatchHLTL3 = muonTriggerMatchHLT.clone(matchedCuts = cms.string('coll("hltIterL3MuonCandidates")'), maxDeltaR = 0.1, maxDPtRel = 10.0)
```

, add the line:

```
muonMatchHLTOldL3 = muonTriggerMatchHLT.clone(matchedCuts = cms.string('coll("hltOldL3MuonCandidates")'), maxDeltaR = 0.1, maxDPtRel = 10.0)
```



3) Update ```patTriggerMatchers1Mu``` by:

```
patTriggerMatchers1Mu = cms.Sequence(
      #muonMatchHLTL1 +   # keep off by default, since it is slow and usually not needed
      muonMatchHLTL2 +
      muonMatchHLTL3 +
      muonMatchHLTOldL3 +
      muonMatchHLTL3T +
      muonMatchHLTL3fromL2 +
      muonMatchHLTTkMu
)
```



4) Update ```patTriggerMatchers1MuInputTags``` by:

```
patTriggerMatchers1MuInputTags = [
    #cms.InputTag('muonMatchHLTL1','propagatedReco'), # fake, will match if and only if he muon did propagate to station 2
    #cms.InputTag('muonMatchHLTL1'),
    cms.InputTag('muonMatchHLTL2'),
    cms.InputTag('muonMatchHLTL3'),
    cms.InputTag('muonMatchHLTOldL3'),
    cms.InputTag('muonMatchHLTL3T'),
    cms.InputTag('muonMatchHLTL3fromL2'),
    cms.InputTag('muonMatchHLTTkMu'),
]
```



5) Below

```
process.muonMatchHLTL3.resolveAmbiguities = False
```

, add the line

```
process.muonMatchHLTOldL3.resolveAmbiguities = False
```



## Recipe (for 94X)

It is same for 102X, but ```expectedNnumberOfMatchedStations``` function should be added in ```Muon.h``` and ```Muon.cc```

```
cmsrel CMSSW_9_4_4
cd CMSSW_9_4_4/src
cmsenv

git cms-merge-topic HuguesBrun:updateL3MuonCollectionsToMatch
git clone git@github.com:KyeongPil-Lee/MuonAnalysis-TagAndProbe.git MuonAnalysis/TagAndProbe -b 102X
git cms-addpkg PhysicsTools/PatAlgos

vi PhysicsTools/PatAlgos/plugins/PATMuonProducer.cc
# -- change the line:
# -- bool simInfoIsAvailalbe = iEvent.getByToken(simInfo_,simInfo); ->
# -- simInfoIsAvailalbe=false;

git cms-addpkg MuonAnalysis/MuonAssociators

vi MuonAnalysis/MuonAssociators/python/patMuonsWithTrigger_cff.py
# -- add several lines by following the section: "Update of patMuonsWithTrigger_cff.py"

# -- add expectedNnumberOfMatchedStations variable to muon object (for new high pT ID)
git cms-addpkg DataFormats/MuonReco
vi DataFormats/MuonReco/interface/Muon.h
# -- add the line: https://github.com/cms-sw/cmssw/blob/CMSSW_10_2_X/DataFormats/MuonReco/interface/Muon.h#L247

vi DataFormats/MuonReco/src/Muon.cc
# -- add the lines: https://github.com/cms-sw/cmssw/blob/CMSSW_10_2_X/DataFormats/MuonReco/src/Muon.cc#L136-L153

scram b -j 4 >&scram.log&
tail -f scram.log
```



## Recipe (10_6_X)

Setup is exactly same with 10_2_X case

### CAVEAT

* Wrong variables in ```tagVariables``` makes **errors** in 10_6_X
  * e.g. ```ExtraIsolationVariables```, ```nSplitTk  = cms.InputTag("splitTrackTagger")```
  * They are not calculated for tag muons, but probe muons: tag muon does not have such valueMap
  * It was ignored in the previous CMSSW and just fill the dummy numbers in the branch, but in CMSSW_10_6_X, it makes error
  * **All of them should be commented out**
    * Example: ```test/zmumu/tp_from_aod_MC_105X_mc2017_realistic_v7.py```



### For UL2016 production under CMSSW_10_6_X

1. ```MuonAnalysis/MuonAssociators/python/patMuonsWithTrigger_cff.py``` only recognize ```hltIterL3MuonCandidates``` which used in 2017 and 2018 data
   -> It should be updated to recognize 2016 version of L3 candidate (```hltL3MuonCandidates```)

```
vi MuonAnalysis/MuonAssociators/python/patMuonsWithTrigger_cff.py
# -- replace all hltIterL3MuonCandidates with hltL3MuonCandidates
```



2. Also, ```tnp_aod_Data_arg.py``` requires ```"!triggerObjectMatchesByCollection('hltIterL3MuonCandidates').empty()"``` for tag muons: it should be updated to:
   ```"!triggerObjectMatchesByCollection('hltL3MuonCandidates').empty()"```

(the config for MC sample doesn't have this line: it doesn't need to be updated)



### Recipe (11_0_0_patch1 or later)

Setup is exactly same with 10_2_X case, except for one thing: add

```
patMuonsWithoutTrigger.addInverseBeta = cms.bool(False)
```

in ```MuonAnalysis/MuonAssociator/python/patMuonsWithTrigger_cff.py```

* Without above fix, [PhysicsTools/PatAlgos/plugins/PATMuonProducer.cc](PhysicsTools/PatAlgos/plugins/PATMuonProducer.cc) makes error below:

  ```
  ----- Begin Fatal Exception 23-Mar-2020 06:02:49 CET-----------------------
  An exception of category 'InvalidReference' occurred while
     [0] Processing  Event run: 1 lumi: 232294 event: 38096058 stream: 0
     [1] Running path 'tagAndProbe'
     [2] Calling method for module PATMuonProducer/'patMuonsWithoutTrigger'
  Exception Message:
  ValueMap: no associated value for given product and index
  ----- End Fatal Exception -------------------------------------------------
  ```

  which comes from the line L621:

  ```
        if (addInverseBeta_) {
          aMuon.readTimeExtra((*muonsTimeExtra)[muonRef]);
        }
  ```

  * "muonsTimeExtra" token is valid and correctly loaded in the code, but ```(*muonsTimeExtra)[muonRef]``` seems not work
  * simInfo ([code](https://github.com/cms-sw/cmssw/blob/CMSSW_11_0_X/PhysicsTools/PatAlgos/plugins/PATMuonProducer.cc#L625-L641)) is also similar situation; the token is valid, but it makes error if it brings a value from the valueMap
    * That's why ```bool simInfoIsAvailalbe = false``` is put by hand (it is not controllable at the python configuration level)

