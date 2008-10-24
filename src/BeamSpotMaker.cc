//-*- C++ -*-
//
// Package:    NtupleMaker
// Class:      BeamSpotMaker
// 
/**\class BeamSpotMaker BeamSpotMaker.cc CMS2/NtupleMakerMaker/src/BeamSpotMaker.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  Puneeth Kalavase
//         Created:  Fri Jun  6 11:07:38 CDT 2008
// $Id: BeamSpotMaker.cc,v 1.1 2008/10/21 17:42:00 kalavase Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CMS2/NtupleMaker/interface/BeamSpotMaker.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "Math/Point3D.h"

typedef math::XYZPoint Point;
using namespace reco;
using namespace edm;
using namespace std;

//
// constructors and destructor
//

BeamSpotMaker::BeamSpotMaker(const edm::ParameterSet& iConfig) {

  
  produces<Point>  ("evtbs"           ).setBranchAlias("evt_bs"              );
  produces<float>  ("evtbsxErr"       ).setBranchAlias("evt_bs_xErr"         );
  produces<float>  ("evtbsyErr"       ).setBranchAlias("evt_bs_yErr"         );
  produces<float>  ("evtbszErr"       ).setBranchAlias("evt_bs_zErr"         );
  produces<float>  ("evtbssigmaZ"     ).setBranchAlias("evt_bs_sigmaZ"       );
  produces<float>  ("evtbssigmaZErr"  ).setBranchAlias("evt_bs_sigmaZErr"    );
  produces<float>  ("evtbsdxdz"       ).setBranchAlias("evt_bs_dxdz"         );
  produces<float>  ("evtbsdxdzErr"    ).setBranchAlias("evt_bs_dxdzErr"      );
  produces<float>  ("evtbsdydz"       ).setBranchAlias("evt_bs_dxdz"         );
  produces<float>  ("evtbsdydzErr"    ).setBranchAlias("evt_bs_dxdzErr"      );
  produces<float>  ("evtbswidthErr"   ).setBranchAlias("evt_bs_widthErr"     );
  
  beamSpotInputTag = iConfig.getParameter<InputTag>("beamSpotInputTag");
  
}


BeamSpotMaker::~BeamSpotMaker() {}

void  BeamSpotMaker::beginJob(const edm::EventSetup&) {
}

void BeamSpotMaker::endJob() {
}


// ------------ method called to produce the data  ------------
void BeamSpotMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  auto_ptr<Point>   evt_bs            (new Point);
  auto_ptr<float>   evt_bs_xErr       (new float);
  auto_ptr<float>   evt_bs_yErr       (new float);
  auto_ptr<float>   evt_bs_zErr       (new float);
  auto_ptr<float>   evt_bs_sigmaZ     (new float);
  auto_ptr<float>   evt_bs_sigmaZErr  (new float);
  auto_ptr<float>   evt_bs_dxdz       (new float);
  auto_ptr<float>   evt_bs_dxdzErr    (new float);
  auto_ptr<float>   evt_bs_dydz       (new float);
  auto_ptr<float>   evt_bs_dydzErr    (new float);
  auto_ptr<float>   evt_bs_widthErr   (new float);
  
  
  Handle<BeamSpot> beamSpotH;
  iEvent.getByLabel(beamSpotInputTag, beamSpotH);
  bool haveBeamSpot = true;
  if(!beamSpotH.isValid() )
    haveBeamSpot = false;
  
  *evt_bs            = haveBeamSpot ? beamSpotH->position()       : Point(0,0,0);
  *evt_bs_xErr       = haveBeamSpot ? beamSpotH->x0Error()        : 0.0;
  *evt_bs_yErr       = haveBeamSpot ? beamSpotH->y0Error()        : 0.0;
  *evt_bs_zErr       = haveBeamSpot ? beamSpotH->z0Error()        : 0.0;
  *evt_bs_sigmaZ     = haveBeamSpot ? beamSpotH->sigmaZ()         : 0.0;
  *evt_bs_sigmaZErr  = haveBeamSpot ? beamSpotH->sigmaZ0Error()   : 0.0;
  *evt_bs_dxdz       = haveBeamSpot ? beamSpotH->dxdz()           : 0.0;
  *evt_bs_dxdzErr    = haveBeamSpot ? beamSpotH->dxdzError()      : 0.0;
  *evt_bs_dydz       = haveBeamSpot ? beamSpotH->dydz()           : 0.0;	
  *evt_bs_dydzErr    = haveBeamSpot ? beamSpotH->dydzError()      : 0.0;
  *evt_bs_widthErr   = haveBeamSpot ? beamSpotH->BeamWidthError() : 0.0;
  
  iEvent.put(evt_bs            ,"evtbs"      );
  if(haveBeamSpot) {
    iEvent.put(evt_bs_xErr       ,"evtbsxErr"  );
    iEvent.put(evt_bs_yErr       ,"evtbsyErr");
    iEvent.put(evt_bs_zErr       ,"evtbszErr");
    iEvent.put(evt_bs_sigmaZ     ,"evtbssigmaZ");
    iEvent.put(evt_bs_sigmaZErr  ,"evtbssigmaZErr");
    iEvent.put(evt_bs_dxdz       ,"evtbsdxdz");
    iEvent.put(evt_bs_dxdzErr    ,"evtbsdxdzErr");
    iEvent.put(evt_bs_dydz       ,"evtbsdydz");
    iEvent.put(evt_bs_dydzErr    ,"evtbsdydzErr");
    iEvent.put(evt_bs_widthErr   ,"evtbswidthErr");
  }
  
}


//define this as a plug-in
DEFINE_FWK_MODULE(BeamSpotMaker);