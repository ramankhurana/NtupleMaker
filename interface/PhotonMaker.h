// -*- C++ -*-
//
// Package:    NtupleMaker
// Class:      NtupleMaker
// 
/**\class NtupleMaker NtupleMaker.cc CMS3/NtupleMaker/src/NtupleMaker.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  pts/4
//         Created:  Fri Jun  6 11:07:38 CDT 2008
// $Id: PhotonMaker.h,v 1.6 2010/04/24 03:58:59 warren Exp $
//
//
#ifndef NTUPLEMAKER_PHOTONMAKER_H
#define NTUPLEMAKER_PHOTONMAKER_H

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

//
// class decleration
//

class PhotonMaker : public edm::EDProducer {
public:
     explicit PhotonMaker (const edm::ParameterSet&);
     ~PhotonMaker();
     
private:
     virtual void beginJob() ;
     virtual void produce(edm::Event&, const edm::EventSetup&);
     virtual void endJob() ;

     // ----------member data ---------------------------
     edm::InputTag photonsInputTag_;
  //   edm::InputTag cms2scsseeddetidInputTag_; 
     edm::InputTag ecalRecHitsInputTag_EE_;
     edm::InputTag ecalRecHitsInputTag_EB_; 
     edm::EDGetTokenT<EcalRecHitCollection>  ecalRecHitsInputTag_EE_Token_;
     edm::EDGetTokenT<EcalRecHitCollection>  ecalRecHitsInputTag_EB_Token_;
     float minEt_;
     noZS::EcalClusterLazyTools* clusterTools_;
     
	std::string aliasprefix_;
};

#endif

