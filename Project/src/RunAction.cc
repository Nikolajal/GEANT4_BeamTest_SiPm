/// \file   RunAction.cc
/// \brief  Implementation of the RunAction class

#include "RunAction.hh"
#include "SiPMAnalysis.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{
    
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    // The choice of analysis technology is done via selectin of a namespace
    // in B4Analysis.hh
    auto analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    // Create directories
    analysisManager->SetHistoDirectoryName("histograms");
    analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

    // Creating ntuple
    //
    /*
    analysisManager->CreateNtuple("Run", "Edep and TrackL and Pos");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->CreateNtupleDColumn("Egap");
    analysisManager->CreateNtupleDColumn("Labs");
    analysisManager->CreateNtupleDColumn("Lgap");
    analysisManager->CreateNtupleDColumn("Xabs");
    analysisManager->CreateNtupleDColumn("Xgap");
    analysisManager->CreateNtupleDColumn("Yabs");
    analysisManager->CreateNtupleDColumn("Ygap");
    analysisManager->CreateNtupleDColumn("Zabs");
    analysisManager->CreateNtupleDColumn("Zgap");
    analysisManager->FinishNtuple();
     */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction( const G4Run* /*run*/)
{
    //inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "SiPMAnalysisOutput";
    analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  auto analysisManager = G4AnalysisManager::Instance();
    
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
