/// \file   SiPMSD.cc
/// \brief  Implementation of the SiPMSD class

#include "SiPMSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

SiPMSD::SiPMSD              (const G4String& name, const G4String& hitsCollectionName,G4int nofCells)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr),
   fNofCells(nofCells)  {
       
    collectionName.insert(hitsCollectionName);
}

SiPMSD::~SiPMSD()   {

}

void SiPMSD::Initialize( G4HCofThisEvent* hce)   {
    /*
    fHitsCollection = new B4cCalorHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection( hcID, fHitsCollection );
    for (G4int i=0; i<fNofCells+1; i++ )
    {
        fHitsCollection->insert(new B4cCalorHit());
    }*/
}

G4bool SiPMSD::ProcessHits(G4Step* step, G4TouchableHistory*)   {
    /*
    auto edep = step->GetTotalEnergyDeposit();
    
    G4double stepLength = 0.;
    if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. )
    {
        stepLength = step->GetStepLength();
    }
    
    auto pos = step->GetPreStepPoint();
    
    if ( edep==0. && stepLength == 0. ) return false;
    
    auto touchable = (step->GetPreStepPoint()->GetTouchable());
    auto layerNumber = touchable->GetReplicaNumber(1);
    auto hit = (*fHitsCollection)[layerNumber];
  
    if ( ! hit )
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hit " << layerNumber;
        G4Exception("B4cCalorimeterSD::ProcessHits()","MyCode0004", FatalException, msg);
    }
  
    auto hitTotal = (*fHitsCollection)[fHitsCollection->entries()-1];
    hit->Add(edep, stepLength,pos);
    hitTotal->Add(edep, stepLength,pos);
     */
    return true;
}

void SiPMSD::EndOfEvent ( G4HCofThisEvent* )    {
    
}
