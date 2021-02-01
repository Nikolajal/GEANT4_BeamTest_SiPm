/// \file   SensitiveDetector.cc
/// \brief  Implementation of the SensitiveDetector class

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "DetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "RunAction.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Analysis.hh"

                        SensitiveDetector::SensitiveDetector    (const G4String& fDetectorName, const G4String& hitsCollectionName, G4int nofCells)
 : G4VSensitiveDetector(fDetectorName),
   fHitsCollection(nullptr)     {
       
    collectionName.insert(hitsCollectionName);
}

                        SensitiveDetector::~SensitiveDetector   ( )   {

}

void                    SensitiveDetector::Initialize           ( G4HCofThisEvent* fCurrentHitsCollection )   {
    
    // Generate the new HitCollection
    fHitsCollection             =   new DetectorHitsCollection ( SensitiveDetectorName, collectionName[0] );
    auto hHitsCollectionID      =   G4SDManager::GetSDMpointer()->GetCollectionID( collectionName[0] );
    fCurrentHitsCollection      ->  AddHitsCollection( hHitsCollectionID, fHitsCollection );
    fHitsCollection             ->  insert( new DetectorHit() );
}

G4bool                  SensitiveDetector::ProcessHits          ( G4Step* fCurrentStep, G4TouchableHistory* )   {

    // Recovering Hit Information
    //
    // >-> Track
    //
    G4Track            *fCurrentTrack   =   fCurrentStep->GetTrack();                       // Pointer to current Track
    //
    // >-> Step
    //
    G4StepPoint        *fPrePoint       =   fCurrentStep->GetPreStepPoint();                // Pointer to Point before Step
    G4StepPoint        *fPstPoint       =   fCurrentStep->GetPostStepPoint();               // Pointer to Point after Step
    //G4double            fStepLength     =   fCurrentStep->GetStepLength();                  // Step Length
    G4double            fEnergyDeposit  =   fCurrentStep->GetTotalEnergyDeposit();          // Particle Energy Deposit
    G4double            fNIEDeposit     =   fCurrentStep->GetNonIonizingEnergyDeposit();    // Particle Energy Deposit
    G4bool              fIsFirstStep    =   fCurrentStep->IsFirstStepInVolume();            // is First Step in Volume
    //G4bool              fIsLastStep     =   fCurrentStep->IsLastStepInVolume();             // is Last Step in Volume
    //

    // Recovering Step Point Information
    //
    // >-> Global properties
    //
    //G4double            fMass           =   fPrePoint->GetMass();                           // Particle Mass
    //G4double            fCharge         =   fPrePoint->GetCharge();                         // Particle Mass
    //const G4VTouchable *fPreTouchable   =   fPrePoint->GetTouchable();                      // Starting Touchables
    //const G4VTouchable *fPstTouchable   =   fPstPoint->GetTouchable();                      // Final Touchables
    //
    // >-> Kinematics
    //
    //G4double            fPreEnergy      =   fPrePoint->GetTotalEnergy();                    // Particle Total energy at start
    //G4double            fPstEnergy      =   fPstPoint->GetTotalEnergy();                    // Particle Total energy at end
    //G4double            fPreKinetic     =   fPrePoint->GetKineticEnergy();                  // Particle Total energy at start
    //G4double            fPstKinetic     =   fPstPoint->GetKineticEnergy();                  // Particle Total energy at end
    G4ThreeVector       fPrePosition    =   fPrePoint->GetPosition();                       // Start position of the Step
    G4ThreeVector       fPstPosition    =   fPstPoint->GetPosition();                       // End position of the Step
    //G4ThreeVector       fPreMomentum    =   fPrePoint->GetMomentum();                       // Total momentum of the track at start
    //G4ThreeVector       fPstMomentum    =   fPstPoint->GetMomentum();                       // Total momentum of the track at end
    //G4ThreeVector       fPreDirection   =   fPrePoint->GetMomentumDirection();              // Direction of momentum  (should be an unit vector) at start
    //G4ThreeVector       fPstDirection   =   fPstPoint->GetMomentumDirection();              // Direction of momentum  (should be an unit vector) at end
    //G4double            fPreVelocity    =   fPrePoint->GetVelocity();                       // Particle Velocity at start
    //G4double            fPstVelocity    =   fPstPoint->GetVelocity();                       // Particle Velocity at end
    //G4double            fPreBeta        =   fPrePoint->GetBeta();                           // Particle Beta at start
    //G4double            fPstBeta        =   fPstPoint->GetBeta();                           // Particle Beta at end
    //G4double            fPreGamma       =   fPrePoint->GetGamma();                          // Particle Gamma at start
    //G4double            fPstGamma       =   fPstPoint->GetGamma();                          // Particle Gamma at end
    //G4double            fPreMagMom      =   fPrePoint->GetMagneticMoment();                 // Particle Magnetic Momentum at start
    //G4double            fPstMagMom      =   fPstPoint->GetMagneticMoment();                 // Particle Magnetic Momentum at end
    //
    // >-> Timing
    //
    //G4double            fPreLocalTime   =   fPrePoint->GetLocalTime();                      // Time since the track is created 
    //G4double            fPreGlobalTime  =   fPrePoint->GetGlobalTime();                     // Time since the event in which the track belongs is created
    //G4double            fPreProperTime  =   fPrePoint->GetProperTime();                     // Proper time of the particle
    //
    // >-> Volume
    //
    //G4VPhysicalVolume  *fPrePhysVol     =   fPrePoint->GetPhysicalVolume();
    //G4VPhysicalVolume  *fPstPhysVol     =   fPstPoint->GetPhysicalVolume();
    //G4Material         *fPreMaterial    =   fPrePoint->GetMaterial();
    //G4Material         *fPstMaterial    =   fPstPoint->GetMaterial();
    
    // Recovering Step Point Information
    //
    // >-> Global properties
    //
    const G4ParticleDefinition   *fParticle   =   fCurrentTrack->GetParticleDefinition();

    // Implementation
    //
    // >-> Check the information needed is worth saving
    //
    if ( fEnergyDeposit == 0. )    return false;
    //
    // >-> 
    //
    
    auto fCurrent_DetectorHit = (*fHitsCollection)[0];
  
    if ( !fCurrent_DetectorHit )
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hit ";
        G4Exception("B4cCalorimeterSD::ProcessHits()","MyCode0004", FatalException, msg);
    }
    
    auto fEnergyPositon = (fPrePosition+fPstPosition)/2.;
    fCurrent_DetectorHit->Add(fEnergyDeposit, fEnergyPositon );

    //Starting the Analysis Manager
    auto analysisManager = G4AnalysisManager::Instance();
    auto runManager = G4RunManager::GetRunManager();

    auto fRunAction             =   (RunAction*)(runManager->GetUserRunAction());
    auto fMapOfEDepHistograms   =   fRunAction->fGetEDepMap();
    auto fMapOfCntrHistograms   =   fRunAction->fGetCntrMap();
    auto fCollectionIndex       =   fRunAction->fGetIndex();

    // Find particle in map
    auto    fIteratorEDep   =   fMapOfEDepHistograms.find(fParticle->GetParticleName());
    if  ( fIteratorEDep != fMapOfEDepHistograms.end() )  {
        analysisManager->FillH2(fIterator->second,(1./fEnergyDeposit)*fEnergyPositon.getX(),(1./fEnergyDeposit)*fEnergyPositon.getY());
    }   else    {
        analysisManager->CreateH2(fParticle->GetParticleName(),fParticle->GetParticleName(), 28*50, -16., 12., 14*50, -9., 5.);
        analysisManager->FillH2(fCollectionIndex,fEnergyPositon.getX(),fEnergyPositon.getY());
        fMapOfEDepHistograms.emplace(fParticle->GetParticleName(),fCollectionIndex);
        fCollectionIndex++;
        fRunAction->fSetEDepMap(fMapOfEDepHistograms);
        fRunAction->fSetIndex(fCollectionIndex);
    }
    
    auto    fIteratorCntr   =   fMapOfCntrHistograms.find(fParticle->GetParticleName());
    if  ( fIteratorCntr != fMapOfCntrHistograms.end() )  {
        if ( fIsFirstStep ) analysisManager->FillH2(fIterator->second,(1./fEnergyDeposit)*fEnergyPositon.getX(),(1./fEnergyDeposit)*fEnergyPositon.getY());
    }   else    {
        analysisManager->CreateH2(fParticle->GetParticleName(),fParticle->GetParticleName(), 28*50, -16., 12., 14*50, -9., 5.);
        if ( fIsFirstStep ) analysisManager->FillH2(fCollectionIndex,fEnergyPositon.getX(),fEnergyPositon.getY());
        fMapOfCntrHistograms.emplace(fParticle->GetParticleName(),fCollectionIndex);
        fCollectionIndex++;
        fRunAction->fSetMap(fMapOfCntrHistograms);
        fRunAction->fSetIndex(fCollectionIndex);
    }

    return true;
}

void                    SensitiveDetector::EndOfEvent           ( G4HCofThisEvent* )    {
    
}
