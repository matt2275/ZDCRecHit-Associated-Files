# Instructions to Run CMSSW with Updated ZDC RecHit 



## Build instructions

### set up initial CMSSW workspace

```
export SCRAM_ARCH=el9_amd64_gcc12

cmsrel CMSSW_14_1_0_pre2
cd CMSSW_14_1_0_pre2/src
cmsenv

git cms-init

git cms-addpkg RecoLocalCalo/HcalRecAlgos
git cms-addpkg RecoLocalCalo/HcalRecProducers
git cms-addpkg DataFormats/HcalRecHit
git cms-addpkg DataFormats/HcalDetId
```
### adding new and updated files
in CMSSW/src

Note the first two files moved are related to a temporary fix to ZDC Geometry to allow the RPD digis to be processed

```
wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/HcalZDCDetId.h
mv HcalZDCDetId.h DataFormats/HcalDetId/interface/HcalZDCDetId.h

wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/classes_def.xml
mv classes_def.xml DataFormats/HcalDetId/src/classes_def.xml
```

The following files are from the Test_ZDCRecHit branch
```
wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/DataFormats/HcalRecHit/interface/ZDCRecHit.h
mv ZDCRecHit.h DataFormats/HcalRecHit/interface/ZDCRecHit.h

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/DataFormats/HcalRecHit/src/ZDCRecHit.cc
mv ZDCRecHit.cc DataFormats/HcalRecHit/src/ZDCRecHit.cc

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/DataFormats/HcalRecHit/src/classes_def.xml
mv ZDCRecHit.cc DataFormats/HcalRecHit/src/classes_def.xml

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/RecoLocalCalo/HcalRecAlgos/interface/ZdcSimpleRecAlgo_Run3.h
mv ZdcSimpleRecAlgo_Run3.h RecoLocalCalo/HcalRecAlgos/interface/ZdcSimpleRecAlgo_Run3.h

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/RecoLocalCalo/HcalRecAlgos/src/ZdcSimpleRecAlgo_Run3.cc
mv ZdcSimpleRecAlgo_Run3.cc RecoLocalCalo/HcalRecAlgos/src/ZdcSimpleRecAlgo_Run3.cc

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/RecoLocalCalo/HcalRecProducers/src/ZdcHitReconstructorRunThree.cc
mv ZdcHitReconstructorRunThree.cc RecoLocalCalo/HcalRecProducers/src/ZdcHitReconstructorRunThree.cc

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/RecoLocalCalo/HcalRecProducers/src/ZdcHitReconstructorRunThree.h
mv ZdcHitReconstructorRunThree.h RecoLocalCalo/HcalRecProducers/src/ZdcHitReconstructorRunThree.h

wget https://raw.githubusercontent.com/matt2275/cmssw/Test_ZDCRecHit/RecoLocalCalo/HcalRecProducers/python/HcalHitReconstructor_zdc_Run3_cfi.py
mv HcalHitReconstructor_zdc_Run3_cfi.py RecoLocalCalo/HcalRecProducers/python/HcalHitReconstructor_zdc_Run3_cfi.py

```
### building CMSSW
 note this build may take a while with all dependencies of HcalDetID
```
git cms-checkdeps -A -a
scram b -j 8

```

Note that you will most likely have a checksum error related to  the DataFormats/HcalRecHits/src/classes_def.xml file. 
Follow the instuctions given by the compliler which will involve adding a new version to the ZDCRecHit and updating the version
After updating clases_def.xml rebuild. 


### Getting cmsRun files
While still in CMSSW/src.

Download ZDCConditions folder from this github. 
https://github.com/matt2275/ZDCRecHit-Associated-Files/tree/main/ZDCConditions

Also Download the cmsRun file
```
wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/make_ZDC_rechits_AOD.py
```
## Running 

```
cmsRun make_ZDC_rechits_AOD.py
```


## Testing Without Analyzer

This test file while output a file with output root file with the zdcroco and zdcdigi information.

Download the file: 

```
wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/testZdcRecHits.py
```
Run via cmsRun:

```
cmsRun testZdcRecHits.py
```

## Testing Without Analyzer

This test file will product 2 output files. One file with the zdcroco and zdcdigi information and another that processes the rechits and digis into an Analyzer Tree. 

First download the HeavyIonAnalysis folder from: https://github.com/CmsHI/cmssw/tree/forest_CMSSW_14_0_X/HeavyIonsAnalysis

Add new files:

```
wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/MNZDCAnalyzerWithDigis.cc
mv HcalZDCDetId.h HeavyIOnsAnalysis/ZDCAnalysis/src/MNZDCAnalyzerWithDigis.cc

wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/MNZDCAnalyzerWithDigis_cfi.py
mv HcalZDCDetId.h HeavyIOnsAnalysis/ZDCAnalysis/python/MNZDCAnalyzerWithDigis_cfi.py
```

Download the test file: 

```
wget https://raw.githubusercontent.com/matt2275/ZDCRecHit-Associated-Files/master/testZdcRecHitsWithAnalyzer.py
```
Run via cmsRun:

```
cmsRun testZdcRecHitsWithAnalyzer.py
```



