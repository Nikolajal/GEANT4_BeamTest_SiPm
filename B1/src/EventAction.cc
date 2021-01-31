/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(),
  fRunAction(0)  {

  } 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)  {    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction( const G4Event* fCurrent_Event )  {   

    //Setting up name of the detector to recover informations
    char* fName = new char[256];

    //Starting the Analysis Manager
    auto analysisManager = G4AnalysisManager::Instance();

    for ( int iClm = 0; iClm < 8; ++iClm )   {
        for ( int iRow = 0; iRow < 4; ++iRow )   {
        
            std::sprintf(fName,"SiPMHitsCollection_%i_%i",iClm,iRow);
            G4int   fCurrent_SD_ID  =   G4SDManager::GetSDMpointer()->GetCollectionID(fName);
            DetectorHitsCollection *fCurrent_SD_HC =   GetHitsCollection( fCurrent_SD_ID, fCurrent_Event );
            
            if ( !fCurrent_SD_HC ) {
                G4ExceptionDescription msg;
                msg << "The material passed is not available, the default will be used" << G4endl;
                G4Exception("DetectorConstruction::fSetAbsorberMat(G4String fMaterialChoice)","W_absorber_material", JustWarning, msg);
            }

            const DetectorConstruction* fDetector    = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
            G4double fDetectorMass = fDetector->GetSiPMLogicalVolume(iClm, iRow)->GetMass()*GeV;
            
            auto    fTotalEntries_  =   ((*fCurrent_SD_HC)[0])->GetEntr();
            if ( fTotalEntries_ == 0 ) continue;
            auto    fEnergyDeposit  =   ((*fCurrent_SD_HC)[0])->GetEdep();
            auto    fEnergyPositon  =   ((*fCurrent_SD_HC)[0])->GetEPos();
            analysisManager->FillH2(0,(1./fEnergyDeposit)*fEnergyPositon.getX(),(1./fEnergyDeposit)*fEnergyPositon.getY(),fEnergyDeposit/fDetectorMass);
            /*
            analysisManager->FillNtupleDColumn(0,   fEnergyDeposit/fDetectorMass);
            analysisManager->FillNtupleDColumn(1,   (1./fDetectorMass)*fEnergyPositon.getX() ); 
            analysisManager->FillNtupleDColumn(2,   (1./fDetectorMass)*fEnergyPositon.getY() );
            analysisManager->FillNtupleDColumn(3,   (1./fDetectorMass)*fEnergyPositon.getZ() );
            analysisManager->FillNtupleIColumn(4,   iRow );
            analysisManager->FillNtupleIColumn(5,   iClm );
            analysisManager->AddNtupleRow();
            */
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHitsCollection * EventAction::GetHitsCollection ( G4int fHCID, const G4Event* fCurrent_Event )  {
    DetectorHitsCollection *fResult =   static_cast<DetectorHitsCollection*>(fCurrent_Event->GetHCofThisEvent()->GetHC(fHCID));
    if ( !fResult ) {
        G4ExceptionDescription msg;
        msg << "The material passed is not available, the default will be used" << G4endl;
        G4Exception("DetectorConstruction::fSetAbsorberMat(G4String fMaterialChoice)","W_absorber_material", JustWarning, msg);
        return nullptr;
    }
    return fResult;
}