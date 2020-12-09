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
   fAbsHCID(-1),
   fGapHCID(-1)
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

void EventAction::BeginOfEventAction(const G4Event* event)
{

}

void EventAction::EndOfEventAction(const G4Event* event)
{  
    if ( fAbsHCID == -1 )
    {
        fAbsHCID    = G4SDManager::GetSDMpointer()->GetCollectionID("AbsorberHitsCollection");
        fGapHCID    = G4SDManager::GetSDMpointer()->GetCollectionID("GapHitsCollection");
    }
    auto absoHC     = GetHitsCollection(fAbsHCID, event);
    auto gapHC      = GetHitsCollection(fGapHCID, event);

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
    
    analysisManager->AddNtupleRow();
}  
