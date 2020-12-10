#include "SiPMDetectorConstruction.hh"
#include "EventAction.hh"
#include "SiPMSD.hh"
#include "SiPMHit.hh"
#include "SiPMAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

EventAction::EventAction()
 : G4UserEventAction(),
   fCollectionHitsID(nullptr)
{
    
}

EventAction::~EventAction()
{
    
}

SiPMHitsCollection* EventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
    auto hitsCollection = static_cast<SiPMHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
  
    if ( ! hitsCollection )
    {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("B4cEventAction::GetHitsCollection()","MyCode0003", FatalException, msg);
    }
    return hitsCollection;
}

void EventAction::BeginOfEventAction    ( const G4Event* event )
{
    
}

void EventAction::EndOfEventAction      ( const G4Event* fCurrent_Event )
{
/*
    G4int fSiPMCellGridNumberY = 4;
    char* fName = new char[256];
    if ( !fCollectionHitsID )
    {
        fCollectionHitsID   =   new G4int [fSiPMCellGridNumberY];
        for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {
            
            std::sprintf(fName,"SiPMHitsCollection_%i",iRow);
            fCollectionHitsID[iRow] = G4SDManager::GetSDMpointer()->GetCollectionID(fName);
            if ( !fCollectionHitsID[iRow] )
            {
                G4ExceptionDescription msg;
                msg << "Could not fetch collectionshit";
                G4Exception("B4DetectorConstruction::DefineMaterials()","MyCode0001", FatalException, msg);
            }
        }
    }
    
    SiPMHitsCollection    **fCollectionHits     = new SiPMHitsCollection *[fSiPMCellGridNumberY];
    for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {
        
        fCollectionHits[iRow] = GetHitsCollection(fCollectionHitsID[iRow], fCurrent_Event);
    }
    /*
    auto absoHit    = (*absoHC) [absoHC ->entries()-1];
    auto gapHit     = (*gapHC)  [gapHC  ->entries()-1];
    
    auto analysisManager = G4AnalysisManager::Instance();
  
    analysisManager->FillNtupleDColumn(0, absoHit->GetEdep());
    analysisManager->FillNtupleDColumn(1, gapHit->GetEdep());
    analysisManager->FillNtupleDColumn(2, absoHit->GetTrackLength());
    analysisManager->FillNtupleDColumn(3, gapHit->GetTrackLength());
    analysisManager->FillNtupleDColumn(4, absoHit->GetPoint_dE_Vector().x());
    analysisManager->FillNtupleDColumn(5, gapHit->GetPoint_dE_Vector().x());
    analysisManager->FillNtupleDColumn(6, absoHit->GetPoint_dE_Vector().y());
    analysisManager->FillNtupleDColumn(7, gapHit->GetPoint_dE_Vector().y());
    analysisManager->FillNtupleDColumn(8, absoHit->GetPoint_dE_Vector().z());
    analysisManager->FillNtupleDColumn(9, gapHit->GetPoint_dE_Vector().z());
    
    
    analysisManager->AddNtupleRow(); */
}  
