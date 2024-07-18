// -*- C++ -*-
//
// Package:    Demo/MNZDCAnalyzerWithDigis
// Class:      MNZDCAnalyzerWithDigis
//
/**\class MNZDCAnalyzerWithDigis MNZDCAnalyzerWithDigis.cc Demo/MNZDCAnalyzerWithDigis/plugins/MNZDCAnalyzerWithDigis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Thu, 23 Sep 2021 21:03:52 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"

#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

struct MyZDCDigi {
  int n;
  float chargefC[10][50];
  int adc[10][50];
  int tdc[10][50];
  int zside[50];
  int section[50];
  int channel[50];
};

using reco::TrackCollection;



class MNZDCAnalyzerWithDigis : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit MNZDCAnalyzerWithDigis(const edm::ParameterSet&);
  ~MNZDCAnalyzerWithDigis();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
   const edm::EDGetTokenT<QIE10DigiCollection> ZDCDigiToken_;  //used to select what tracks to read from configuration file
   const edm::EDGetTokenT<edm::SortedCollection<ZDCRecHit>> ZDCToken_;  //used to select what tracks to read from configuration file
   edm::ESGetToken<HcalDbService, HcalDbRecord> hcalDatabaseToken_;
  double MinZDCEn_;
  double MaxZDCEn_;
   edm::Service<TFileService> fs;
   TTree* t1;
   
   
     MyZDCDigi zdcDigi;
   
   // tree branch variables
   int zdc_n;
   float zdc_e[50];
   int zdc_side[50];
   int zdc_section[50];
   int zdc_channel[50];
   
   
   float ZDCp_Total_Energy;
   int ZDCp_EM_n;
   int ZDCp_EM_Channel[5];
   float ZDCp_EM_Energy[5];
   float ZDCp_EM_Time[5];
   float ZDCp_EM_TDCtime[5];
   float ZDCp_EM_ChargeWeightedTime[5];
   float ZDCp_EM_EnergySOIp1[5];
   float ZDCp_EM_ratioSOIp1[5];
   int ZDCp_HAD_n;
   int ZDCp_HAD_Channel[4];
   float ZDCp_HAD_Energy[4];
   float ZDCp_HAD_Time[4];
   float ZDCp_HAD_TDCtime[4];
   float ZDCp_HAD_ChargeWeightedTime[4];
   float ZDCp_HAD_EnergySOIp1[4];
   float ZDCp_HAD_ratioSOIp1[4];
   int ZDCp_RPD_n;
   int ZDCp_RPD_Channel[16];
   float ZDCp_RPD_Energy[16];
   float ZDCp_RPD_Time[16];
   float ZDCp_RPD_TDCtime[16];
   float ZDCp_RPD_ChargeWeightedTime[16];
   float ZDCp_RPD_EnergySOIp1[16];
   float ZDCp_RPD_ratioSOIp1[16];
   
   float ZDCm_Total_Energy;
   int ZDCm_EM_n;
   int ZDCm_EM_Channel[5];
   float ZDCm_EM_Energy[5];
   float ZDCm_EM_Time[5];
   float ZDCm_EM_TDCtime[5];
   float ZDCm_EM_ChargeWeightedTime[5];
   float ZDCm_EM_EnergySOIp1[5];
   float ZDCm_EM_ratioSOIp1[5];
   int ZDCm_HAD_n;
   int ZDCm_HAD_Channel[4];
   float ZDCm_HAD_Energy[4];
   float ZDCm_HAD_Time[4];
   float ZDCm_HAD_TDCtime[4];
   float ZDCm_HAD_ChargeWeightedTime[4];
   float ZDCm_HAD_EnergySOIp1[4];
   float ZDCm_HAD_ratioSOIp1[4];
   int ZDCm_RPD_n;
   int ZDCm_RPD_Channel[16];
   float ZDCm_RPD_Energy[16];
   float ZDCm_RPD_Time[16];
   float ZDCm_RPD_TDCtime[16];
   float ZDCm_RPD_ChargeWeightedTime[16];
   float ZDCm_RPD_EnergySOIp1[16];
   float ZDCm_RPD_ratioSOIp1[16];
   

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MNZDCAnalyzerWithDigis::MNZDCAnalyzerWithDigis(const edm::ParameterSet& iConfig) :
      ZDCDigiToken_(consumes<QIE10DigiCollection>(iConfig.getParameter<edm::InputTag>("ZDCDigiSource"))), 
      ZDCToken_(consumes<edm::SortedCollection<ZDCRecHit>>(iConfig.getParameter<edm::InputTag>("ZDCSource"))), 
      hcalDatabaseToken_(esConsumes<HcalDbService, HcalDbRecord>()),
      MinZDCEn_(iConfig.getParameter<double>("MinZDCEn")),
      MaxZDCEn_(iConfig.getParameter<double>("MaxZDCEn"))
      {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();

#endif
  //now do what ever initialization is needed
}

MNZDCAnalyzerWithDigis::~MNZDCAnalyzerWithDigis() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void MNZDCAnalyzerWithDigis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;
  
  zdc_n = 0;
  ZDCp_Total_Energy = 0;
  ZDCp_EM_n =0;
  ZDCp_HAD_n =0;
  ZDCp_RPD_n =0;  
  ZDCm_Total_Energy = 0;
  ZDCm_EM_n =0;
  ZDCm_HAD_n =0;
  ZDCm_RPD_n =0;
  for (unsigned int i = 0; i < 50; i++) {
  zdc_e[i] = 0;
  zdc_side[i] = -99;
  zdc_section [i]= -99;
  zdc_channel[i] = -99;
  
  if(i>=16) continue;
  ZDCp_RPD_Channel[i] = -99;
  ZDCp_RPD_Energy[i] = -99;
  ZDCp_RPD_Time[i] = -99;
  ZDCp_RPD_TDCtime[i] = -99;
  ZDCp_RPD_ChargeWeightedTime[i] = -99;
  ZDCp_RPD_EnergySOIp1[i] = -99;
  // ZDCp_RPD_TimeSOIp1[i] = -99; 

  ZDCm_RPD_Channel[i] = -99;
  ZDCm_RPD_Energy[i] = -99;
  ZDCm_RPD_Time[i] = -99;
  ZDCm_RPD_TDCtime[i] = -99;
  ZDCm_RPD_ChargeWeightedTime[i] = -99;
  ZDCm_RPD_EnergySOIp1[i] = -99;
  // ZDCm_RPD_TimeSOIp1[i] = -99;  

  if(i>=5) continue;
  ZDCp_EM_Channel[i] = -99;
  ZDCp_EM_Energy[i] = -99;
  ZDCp_EM_Time[i] = -99;
  ZDCp_EM_TDCtime[i] = -99;
  ZDCp_EM_ChargeWeightedTime[i] = -99;
  ZDCp_EM_EnergySOIp1[i] = -99;
  // ZDCp_EM_TimeSOIp1[i] = -99; 

  ZDCm_EM_Channel[i] = -99;
  ZDCm_EM_Energy[i] = -99;
  ZDCm_EM_Time[i] = -99;
  ZDCm_EM_TDCtime[i] = -99;
  ZDCm_EM_ChargeWeightedTime[i] = -99;
  ZDCm_EM_EnergySOIp1[i] = -99;
  // ZDCm_EM_TimeSOIp1[i] = -99;

  if(i>=4) continue;
  ZDCp_HAD_Channel[i] = -99;
  ZDCp_HAD_Energy[i] = -99;
  ZDCp_HAD_Time[i] = -99;
  ZDCp_HAD_TDCtime[i] = -99;
  ZDCp_HAD_ChargeWeightedTime[i] = -99;
  ZDCp_HAD_EnergySOIp1[i] = -99;
  // ZDCp_HAD_TimeSOIp1[i] = -99; 

  ZDCm_HAD_Channel[i] = -99;
  ZDCm_HAD_Energy[i] = -99;
  ZDCm_HAD_Time[i] = -99;
  ZDCm_HAD_TDCtime[i] = -99;
  ZDCm_HAD_ChargeWeightedTime[i] = -99;
  ZDCm_HAD_EnergySOIp1[i] = -99;
  // ZDCm_HAD_TimeSOIp1[i] = -99;     
  }
  
    edm::Handle<ZDCRecHitCollection> zdcrechits;
   iEvent.getByToken(ZDCToken_, zdcrechits);
    // zdc_n = zdcrechits->size();   
    int nhits = 0;
    for (auto const& rh : *zdcrechits) {
      HcalZDCDetId zdcid = rh.id();
      if (nhits  < 50) {
       float energy = rh.energy();
       int side = zdcid.zside();
       int section = zdcid.section();
       zdc_e[nhits] = energy;
       zdc_side[nhits] = side;
       zdc_section[nhits] = section;
       zdc_channel[nhits] = zdcid.channel();
       if(side >0 ){
         if(section==1){
            ZDCp_Total_Energy+= energy;
           ZDCp_EM_Channel[ZDCp_EM_n] = zdcid.channel();
           ZDCp_EM_Energy[ZDCp_EM_n] = energy;
           ZDCp_EM_Time[ZDCp_EM_n] = rh.time();
           ZDCp_EM_TDCtime[ZDCp_EM_n] = rh.TDCtime();
           ZDCp_EM_ChargeWeightedTime[ZDCp_EM_n] = rh.chargeWeightedTime();
           ZDCp_EM_EnergySOIp1[ZDCp_EM_n] = rh.energySOIp1();
           ZDCp_EM_ratioSOIp1[ZDCp_EM_n] = rh.ratioSOIp1(); 
           ZDCp_EM_n++;
         }
         if(section==2){
           ZDCp_Total_Energy+= energy;
           ZDCp_HAD_Channel[ZDCp_HAD_n] = zdcid.channel();
           ZDCp_HAD_Energy[ZDCp_HAD_n] = energy;
           ZDCp_HAD_Time[ZDCp_HAD_n] = rh.time();
           ZDCp_HAD_TDCtime[ZDCp_HAD_n] = rh.TDCtime();
           ZDCp_HAD_ChargeWeightedTime[ZDCp_HAD_n] = rh.chargeWeightedTime();
           ZDCp_HAD_EnergySOIp1[ZDCp_HAD_n] = rh.energySOIp1();
           ZDCp_HAD_ratioSOIp1[ZDCp_HAD_n] = rh.ratioSOIp1(); 
           ZDCp_HAD_n++;
         }
         if(section==4){
           ZDCp_RPD_Channel[ZDCp_RPD_n] = zdcid.channel();
           ZDCp_RPD_Energy[ZDCp_RPD_n] = energy;
           ZDCp_RPD_Time[ZDCp_RPD_n] = rh.time();
           ZDCp_RPD_TDCtime[ZDCp_RPD_n] = rh.TDCtime();
           ZDCp_RPD_ChargeWeightedTime[ZDCp_RPD_n] = rh.chargeWeightedTime();
           ZDCp_RPD_EnergySOIp1[ZDCp_RPD_n] = rh.energySOIp1();
           ZDCp_RPD_ratioSOIp1[ZDCp_RPD_n] = rh.ratioSOIp1(); 
           ZDCp_RPD_n++; 
         }
       }
       
       if(side <0 ){
         if(section==1){
           ZDCm_Total_Energy+= energy;
           ZDCm_EM_Channel[ZDCm_EM_n] = zdcid.channel();
           ZDCm_EM_Energy[ZDCm_EM_n] = energy;
           ZDCm_EM_Time[ZDCm_EM_n] = rh.time();
           ZDCm_EM_TDCtime[ZDCm_EM_n] = rh.TDCtime();
           ZDCm_EM_ChargeWeightedTime[ZDCm_EM_n] = rh.chargeWeightedTime();
           ZDCm_EM_EnergySOIp1[ZDCm_EM_n] = rh.energySOIp1();
           ZDCm_EM_ratioSOIp1[ZDCm_EM_n] = rh.ratioSOIp1(); 
           ZDCm_EM_n++;
         }
         if(section==2){
           ZDCm_Total_Energy+= energy;
           ZDCm_HAD_Channel[ZDCm_HAD_n] = zdcid.channel();
           ZDCm_HAD_Energy[ZDCm_HAD_n] = energy;
           ZDCm_HAD_Time[ZDCm_HAD_n] = rh.time();
           ZDCm_HAD_TDCtime[ZDCm_HAD_n] = rh.TDCtime();
           ZDCm_HAD_ChargeWeightedTime[ZDCm_HAD_n] = rh.chargeWeightedTime();
           ZDCm_HAD_EnergySOIp1[ZDCm_HAD_n] = rh.energySOIp1();
           ZDCm_HAD_ratioSOIp1[ZDCm_HAD_n] = rh.ratioSOIp1(); 
           ZDCm_HAD_n++;
         }
         if(section==4){
           ZDCm_RPD_Channel[ZDCm_RPD_n] = zdcid.channel();
           ZDCm_RPD_Energy[ZDCm_RPD_n] = energy;
           ZDCm_RPD_Time[ZDCm_RPD_n] = rh.time();
           ZDCm_RPD_TDCtime[ZDCm_RPD_n] = rh.TDCtime();
           ZDCm_RPD_ChargeWeightedTime[ZDCm_RPD_n] = rh.chargeWeightedTime();
           ZDCm_RPD_EnergySOIp1[ZDCm_RPD_n] = rh.energySOIp1();
           ZDCm_RPD_ratioSOIp1[ZDCm_RPD_n] = rh.ratioSOIp1(); 
           ZDCm_RPD_n++; 
         }
       }
       // StandAlone_nt.ZDC_saturation[nhits] = static_cast<int>( rh.flagField(HcalCaloFlagLabels::ADCSaturationBit) );
      }

      nhits++;
    } // end loop zdc rechits 
    
    zdc_n = nhits;  
    
    edm::Handle<QIE10DigiCollection> zdcdigis;
    iEvent.getByToken(ZDCDigiToken_, zdcdigis);
    
    edm::ESHandle<HcalDbService> conditions = iSetup.getHandle(hcalDatabaseToken_);
    
    nhits = 0;


    for (auto it = zdcdigis->begin(); it != zdcdigis->end(); it++) {
       
      const QIE10DataFrame digi = static_cast<const QIE10DataFrame>(*it);

      HcalZDCDetId zdcid = digi.id();
       int side = zdcid.zside();
       int section = zdcid.section();
       int channel = zdcid.channel();
      if(section== 1 && channel> 5) continue; // ignore extra EM channels 
      
      
      CaloSamples caldigi;

      //const ZDCDataFrame & rh = (*zdcdigis)[it];

        const HcalQIECoder* qiecoder = conditions->getHcalCoder(zdcid);
        const HcalQIEShape* qieshape = conditions->getHcalShape(qiecoder);
        HcalCoderDb coder(*qiecoder, *qieshape);
        //        coder.adc2fC(rh,caldigi);
        coder.adc2fC(digi, caldigi);


      if (nhits < 50) {
        zdcDigi.zside[nhits] = side;
        zdcDigi.section[nhits] = section;
        zdcDigi.channel[nhits] = channel;

        for (int ts = 0; ts < digi.samples(); ts++) {

          zdcDigi.chargefC[ts][nhits] = caldigi[ts];
          zdcDigi.adc[ts][nhits] = digi[ts].adc();
          zdcDigi.tdc[ts][nhits] = digi[ts].le_tdc();
        }
      }
      nhits++;
    }  // end loop zdc rechits

    zdcDigi.n = nhits;
    
    t1->Fill();

// #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // // if the SetupData is always needed
  // auto setup = iSetup.getData(setupToken_);
  // // if need the ESHandle to check if the SetupData was there or not
  // auto pSetup = iSetup.getHandle(setupToken_);
// #endif
}

// ------------ method called once each job just before starting event loop  ------------
void MNZDCAnalyzerWithDigis::beginJob() {
  // please remove this method if not needed
  t1 = fs->make<TTree>("Events", "Events");
  
  t1->Branch("zdc_n",&zdc_n);
  t1->Branch("zdc_e",zdc_e,"zdc_e[zdc_n]/F");
  t1->Branch("zdc_side",zdc_side,"zdc_side[zdc_n]/I");
  t1->Branch("zdc_section",zdc_section,"zdc_section[zdc_n]/I");
  t1->Branch("zdc_channel",zdc_channel,"zdc_channel[zdc_n]/I");
  
  t1->Branch("ZDCp_Total_Energy",&ZDCp_Total_Energy);
  t1->Branch("ZDCp_EM_n", &ZDCp_EM_n);
  t1->Branch("ZDCp_EM_Channel", ZDCp_EM_Channel, "ZDCp_EM_Channel[ZDCp_EM_n]/I");
  t1->Branch("ZDCp_EM_Energy", ZDCp_EM_Energy, "ZDCp_EM_Energy[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_EM_Time", ZDCp_EM_Time, "ZDCp_EM_Time[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_EM_TDCtime", ZDCp_EM_TDCtime, "ZDCp_EM_TDCtime[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_EM_ChargeWeightedTime", ZDCp_EM_ChargeWeightedTime, "ZDCp_EM_ChargeWeightedTime[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_EM_EnergySOIp1", ZDCp_EM_EnergySOIp1, "ZDCp_EM_EnergySOIp1[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_EM_ratioSOIp1", ZDCp_EM_ratioSOIp1, "ZDCp_EM_ratioSOIp1[ZDCp_EM_n]/F");
  t1->Branch("ZDCp_HAD_n", &ZDCp_HAD_n );
  t1->Branch("ZDCp_HAD_Channel", ZDCp_HAD_Channel, "ZDCp_HAD_Channel[ZDCp_HAD_n]/I");
  t1->Branch("ZDCp_HAD_Energy", ZDCp_HAD_Energy, "ZDCp_HAD_Energy[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_HAD_Time", ZDCp_HAD_Time, "ZDCp_HAD_Time[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_HAD_TDCtime", ZDCp_HAD_TDCtime, "ZDCp_HAD_TDCtime[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_HAD_ChargeWeightedTime", ZDCp_HAD_ChargeWeightedTime, "ZDCp_HAD_ChargeWeightedTime[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_HAD_EnergySOIp1", ZDCp_HAD_EnergySOIp1, "ZDCp_HAD_EnergySOIp1[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_HAD_ratioSOIp1", ZDCp_HAD_ratioSOIp1, "ZDCp_HAD_ratioSOIp1[ZDCp_HAD_n]/F");
  t1->Branch("ZDCp_RPD_n", &ZDCp_RPD_n );
  t1->Branch("ZDCp_RPD_Channel", ZDCp_RPD_Channel, "ZDCp_RPD_Channel[ZDCp_EM_n]/I");
  t1->Branch("ZDCp_RPD_Energy", ZDCp_RPD_Energy, "ZDCp_RPD_Energy[ZDCp_RPD_n]/F");
  t1->Branch("ZDCp_RPD_Time", ZDCp_RPD_Time, "ZDCp_RPD_Time[ZDCp_RPD_n]/F");
  t1->Branch("ZDCp_RPD_TDCtime", ZDCp_RPD_TDCtime, "ZDCp_RPD_TDCtime[ZDCp_RPD_n]/F");
  t1->Branch("ZDCp_RPD_ChargeWeightedTime", ZDCp_RPD_ChargeWeightedTime, "ZDCp_RPD_ChargeWeightedTime[ZDCp_RPD_n]/F");
  t1->Branch("ZDCp_RPD_EnergySOIp1", ZDCp_RPD_EnergySOIp1, "ZDCp_RPD_EnergySOIp1[ZDCp_RPD_n]/F");
  t1->Branch("ZDCp_RPD_ratioSOIp1", ZDCp_RPD_ratioSOIp1, "ZDCp_RPD_ratioSOIp1[ZDCp_RPD_n]/F");
  
  t1->Branch("ZDCm_Total_Energy",&ZDCm_Total_Energy);
  t1->Branch("ZDCm_EM_n", &ZDCm_EM_n);
  t1->Branch("ZDCm_EM_Channel", ZDCm_EM_Channel, "ZDCm_EM_Channel[ZDCm_EM_n]/I");
  t1->Branch("ZDCm_EM_Energy", ZDCm_EM_Energy, "ZDCm_EM_Energy[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_EM_Time", ZDCm_EM_Time, "ZDCm_EM_Time[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_EM_TDCtime", ZDCm_EM_TDCtime, "ZDCm_EM_TDCtime[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_EM_ChargeWeightedTime", ZDCm_EM_ChargeWeightedTime, "ZDCm_EM_ChargeWeightedTime[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_EM_EnergySOIp1", ZDCm_EM_EnergySOIp1, "ZDCm_EM_EnergySOIp1[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_EM_ratioSOIp1", ZDCm_EM_ratioSOIp1, "ZDCm_EM_ratioSOIp1[ZDCm_EM_n]/F");
  t1->Branch("ZDCm_HAD_n", &ZDCm_HAD_n );
  t1->Branch("ZDCm_HAD_Channel", ZDCm_HAD_Channel, "ZDCm_HAD_Channel[ZDCm_HAD_n]/I");
  t1->Branch("ZDCm_HAD_Energy", ZDCm_HAD_Energy, "ZDCm_HAD_Energy[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_HAD_Time", ZDCm_HAD_Time, "ZDCm_HAD_Time[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_HAD_TDCtime", ZDCm_HAD_TDCtime, "ZDCm_HAD_TDCtime[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_HAD_ChargeWeightedTime", ZDCm_HAD_ChargeWeightedTime, "ZDCm_HAD_ChargeWeightedTime[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_HAD_EnergySOIp1", ZDCm_HAD_EnergySOIp1, "ZDCm_HAD_EnergySOIp1[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_HAD_ratioSOIp1", ZDCm_HAD_ratioSOIp1, "ZDCm_HAD_ratioSOIp1[ZDCm_HAD_n]/F");
  t1->Branch("ZDCm_RPD_n", &ZDCm_RPD_n );
  t1->Branch("ZDCm_RPD_Channel", ZDCm_RPD_Channel, "ZDCm_RPD_Channel[ZDCm_EM_n]/I");
  t1->Branch("ZDCm_RPD_Energy", ZDCm_RPD_Energy, "ZDCm_RPD_Energy[ZDCm_RPD_n]/F");
  t1->Branch("ZDCm_RPD_Time", ZDCm_RPD_Time, "ZDCm_RPD_Time[ZDCm_RPD_n]/F");
  t1->Branch("ZDCm_RPD_TDCtime", ZDCm_RPD_TDCtime, "ZDCm_RPD_TDCtime[ZDCm_RPD_n]/F");
  t1->Branch("ZDCm_RPD_ChargeWeightedTime", ZDCm_RPD_ChargeWeightedTime, "ZDCm_RPD_ChargeWeightedTime[ZDCm_RPD_n]/F");
  t1->Branch("ZDCm_RPD_EnergySOIp1", ZDCm_RPD_EnergySOIp1, "ZDCm_RPD_EnergySOIp1[ZDCm_RPD_n]/F");
  t1->Branch("ZDCm_RPD_ratioSOIp1", ZDCm_RPD_ratioSOIp1, "ZDCm_RPD_ratioSOIp1[ZDCm_RPD_n]/F");
  
  
    t1->Branch("zdcdigi_n", &zdcDigi.n, "zdcdigi_n/I");
    t1->Branch("zdcdigi_zside", zdcDigi.zside, "zdcdigi_zside[zdcdigi_n]/I");
    t1->Branch("zdcdigi_section", zdcDigi.section, "zdcdigi_section[zdcdigi_n]/I");
    t1->Branch("zdcdigi_channel", zdcDigi.channel, "zdcdigi_channel[zdcdigi_n]/I");

    for (int i = 0; i < 6; i++) {
      TString adcTsSt("zdcdigi_adcTs"), chargefCTsSt("zdcdigi_chargefCTs"), tdcTsSt("zdcdigi_tdcTs");
      adcTsSt += i;
      chargefCTsSt += i;
      tdcTsSt += i;

      t1->Branch(adcTsSt, zdcDigi.adc[i], adcTsSt + "[zdcdigi_n]/I");
      t1->Branch(chargefCTsSt, zdcDigi.chargefC[i], chargefCTsSt + "[zdcdigi_n]/F");
      t1->Branch(tdcTsSt, zdcDigi.tdc[i], tdcTsSt + "[zdcdigi_n]/I");
    }
}

// ------------ method called once each job just after ending the event loop  ------------
void MNZDCAnalyzerWithDigis::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MNZDCAnalyzerWithDigis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MNZDCAnalyzerWithDigis);