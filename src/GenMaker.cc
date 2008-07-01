//-*- C++ -*-
//
// Package:    NtupleMaker
// Class:      GenMaker
// 
/**\class GenMaker GenMaker.cc CMS2/NtupleMaker/src/GenMaker.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  Puneeth Kalavase
//         Created:  Fri Jun  6 11:07:38 CDT 2008
// $Id: GenMaker.cc,v 1.1 2008/06/25 01:39:08 kalavase Exp $
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

#include "CMS2/NtupleMaker/interface/GenMaker.h"
#include "CMS2/NtupleMaker/interface/MCUtilities.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

typedef math::XYZTLorentzVector LorentzVector;
using namespace reco;
using namespace edm;
using namespace std;

//
// constructors and destructor
//

GenMaker::GenMaker(const edm::ParameterSet& iConfig) {

  produces<vector<int> >            ("genpsid"          ).setBranchAlias("genps_id"          );
  produces<vector<int> >            ("genpsidmother"    ).setBranchAlias("genps_id_mother"   );
  produces<vector<LorentzVector> >  ("genpsp4"          ).setBranchAlias("genps_p4"          );
  produces<vector<LorentzVector> >  ("genpsprodvtx"     ).setBranchAlias("genps_prod_vtx"    );
  

  genParticlesInputTag = iConfig.getParameter<InputTag>("genParticlesInputTag");

}


GenMaker::~GenMaker() {}

void  GenMaker::beginJob(const edm::EventSetup&) {
}

void GenMaker::endJob() {
}


// ------------ method called to produce the data  ------------
void GenMaker::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  

  auto_ptr<vector<int> >            genps_id          (new vector<int>             );
  auto_ptr<vector<int> >            genps_id_mother   (new vector<int>             );
  auto_ptr<vector<LorentzVector> >  genps_p4          (new vector<LorentzVector>   );
  auto_ptr<vector<LorentzVector> >  genps_prod_vtx    (new vector<LorentzVector>   );

   // get MC particle collection
  edm::Handle<reco::GenParticleCollection> genpsHandle;
  iEvent.getByLabel(genParticlesInputTag, genpsHandle);
  const vector<GenParticle>* genps_coll = genpsHandle.product();


  for(vector<GenParticle>::const_iterator genps_it = genps_coll->begin();
      genps_it != genps_coll->end(); genps_it++) {
    
    //look 
    if(genps_it->status() !=3) continue;

    genps_id        ->push_back(genps_it->pdgId()                         );
    genps_id_mother ->push_back(MCUtilities::motherID(*genps_it)->pdgId() );
    
    LorentzVector genp4(genps_it->p4().px(), 
			genps_it->p4().py(),
			genps_it->p4().pz(),
			genps_it->p4().e()                                );
    
    
    genps_p4        ->push_back( LorentzVector(genps_it->p4().px(), 
					       genps_it->p4().py(),
					       genps_it->p4().pz(),
					       genps_it->p4().e() 
					       )
				 );

    genps_prod_vtx  ->push_back( LorentzVector(genps_it->vx(),
					       genps_it->vy(),
					       genps_it->vz(),
					       0.0         
					       ) 
				 );
    
  }

  
  iEvent.put(genps_id           ,"genpsid"         );
  iEvent.put(genps_id_mother    ,"genpsidmother"   );
  iEvent.put(genps_p4           ,"genpsp4"         );
  iEvent.put(genps_prod_vtx     ,"genpsprodvtx"    );

}

//define this as a plug-in
DEFINE_FWK_MODULE(GenMaker);





  