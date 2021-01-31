#include "RunAction.hh"
#include "RunMessenger.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunMessenger::RunMessenger    ( RunAction* fRun )
    : G4UImessenger(),  fRunAction(fRun)
{
    //  Project GUI Commands
    fDir_SiPmProject            = new G4UIdirectory("/SiPmRun/");
    fDir_SiPmProject            ->SetGuidance("UI commands of this Project");
    
    //  Detector GUI Configuration
    fDir_RunAction              = new G4UIdirectory("/SiPmRun/Run/");
    fDir_RunAction              ->SetGuidance("Run Action Configuration");
    
    // -- // Absorber Material
    fCmd_Outputfile_Name        = new G4UIcmdWithAString("/SiPmRun/Run/filename",this);
    fCmd_Outputfile_Name        ->SetGuidance("Select filename for output");
    fCmd_Outputfile_Name        ->SetParameterName("choice",false);
    fCmd_Outputfile_Name        ->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunMessenger::~RunMessenger()
{
    // Delete Directories
    delete  fDir_SiPmProject;
    delete  fDir_RunAction;
    
    // Delete Absorber
    delete  fCmd_Outputfile_Name;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunMessenger::SetNewValue(    G4UIcommand* command,   G4String fInputValue   )
{
    if ( command == fCmd_Outputfile_Name )    {
        fRunAction    ->  fSetFileName( fInputValue );
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
