/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunMessenger.hh"
#include "Analysis.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),  fFileName("SiPMAnalysisOutput") { 
  // Start messenger
  fRunMessenger = new RunMessenger(this);

  // inform the runManager to print for each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
 
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // inform the runManager to save random number seed
  //analysisManager->SetNtupleMerging(true);
  
  // Generate the Output histograms
  analysisManager->CreateH2("SiPMTest","SiPMTest hit map of dose (total)", 28*50, -16., 12., 14*50, -9., 5.); 

  // Generate the Output tree
  /*
  analysisManager->CreateNtuple("SiPMTest","run");
  analysisManager->CreateNtupleDColumn("EDep");
  analysisManager->CreateNtupleDColumn("Xcoord");
  analysisManager->CreateNtupleDColumn("Ycoord");
  analysisManager->CreateNtupleDColumn("Zcoord");
  analysisManager->CreateNtupleIColumn("SIPMRow");
  analysisManager->CreateNtupleIColumn("SIPMClm");
  analysisManager->FinishNtuple();*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction() {
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile(fFileName);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* fCurrent_Run)  {
  // Checking there is at least one event 
  //if ( fCurrent_Run->GetNumberOfEvent() == 0) return;

  // Recovering Analysis Manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Closing Output file
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double edep)
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......